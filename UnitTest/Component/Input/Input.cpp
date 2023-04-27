#include "stdafx.h"
#include "Input.h"

#include "Character/Agent.h"

Input::Input()
{
  crosshair = new TextureRect(Values::ZeroVec3, Vector3(72, 72, 0), 0, TexturePath + L"crosshair003.png");
}

Input::~Input()
{
  SAFE_DELETE(crosshair);
}

void Input::Update(Agent& agent)
{

  double globalSpeed = Time::Get()->GetGlobalSpeed();

  // Test
  if (Keyboard::Get()->Down(VK_F4)) Time::Get()->SetGlobalSpeed(0.25f);
  if (Keyboard::Get()->Down(VK_F5)) Time::Get()->SetGlobalSpeed(1.00f);

  // Mouse And SetAxis
  {
    Vector3 position = agent.GetPosition();
    Vector3 mousePos = Mouse::Get()->GetPosition();

    mouseWorldPos = mousePos + Camera::Get()->GetPosition();
    mouseWorldPos.z = 0.f;

    auto agentLookAtAxis = mouseWorldPos - position;
    D3DXVec3Normalize(&agentLookAtAxis, &agentLookAtAxis);

    crosshair->SetPosition(mouseWorldPos);
    crosshair->Update();

    agent.SetAgentLookAtAxis(agentLookAtAxis);
  }

  ObjectGraphic* graphic = agent.GetGraphic();

  // Movement
  {
    auto movementState = agent.GetMovementState();
    auto movement = agent.GetMovement();;

    switch (movementState)
    {
    case Agent::MovementState::ONGROUND:
    {
      graphic->SetVisible(true, ObjectGraphic::Type::ANIMATION, ObjectGraphic::Slot::UPPER);

      // 이동
      if (Keyboard::Get()->Press('A') && !Keyboard::Get()->Press('D')) {
        movement->MoveLeft();
        if (agent.GetIsFliped()) graphic->SetCurrentAnimation(L"run", ObjectGraphic::Slot::LOWER);
        else graphic->SetCurrentAnimation(L"runBack", ObjectGraphic::Slot::LOWER);
      }
      else if (Keyboard::Get()->Press('D') && !Keyboard::Get()->Press('A')) {
        movement->MoveRight();
        if (agent.GetIsFliped()) graphic->SetCurrentAnimation(L"runBack", ObjectGraphic::Slot::LOWER);
        else graphic->SetCurrentAnimation(L"run", ObjectGraphic::Slot::LOWER);
      }
      else {
        movement->SlowDown();
        if (movement->GetXSpeed() < 0.5f)
        {
          graphic->SetCurrentAnimation(L"idle", ObjectGraphic::Slot::LOWER);
        }
      }

      // 슬라이딩
      if (std::abs(movement->GetXSpeed()) > 2 && Keyboard::Get()->Press(VK_LSHIFT) && isPressSliding == false)
      {
        isPressSliding = true;
        movement->Slide();
        agent.SetMovementState(Agent::MovementState::SLIDING);
        graphic->SetCurrentAnimation(L"slide", ObjectGraphic::Slot::LOWER);
        graphic->SetVisible(false, ObjectGraphic::Type::ANIMATION, ObjectGraphic::Slot::UPPER);
      }

      // 점프
      if (Keyboard::Get()->Down(VK_SPACE))
      {
        isPressSliding = false;
        isPressJumping = true;
        movement->Jump();
        jumpProgress = 0.0;
      }

      break;
    }
    case Agent::MovementState::SLIDING:
    {
      // 감속
      {
        if (movement->GetXSpeed() < 0.5f)
          if (Keyboard::Get()->Press('D'))
            movement->MoveRight();

        if (movement->GetXSpeed() > 0.5f)
          if (Keyboard::Get()->Press('A'))
            movement->MoveLeft();
      }

      // 점프
      if (Keyboard::Get()->Down(VK_SPACE))
      {
        isPressSliding = false;
        isPressJumping = true;
        movement->Jump();
        jumpProgress = 0.0;
      }
      break;
    }
    case Agent::MovementState::FALLING:
    case Agent::MovementState::FALLING_MOVE:
    {
      graphic->SetVisible(true, ObjectGraphic::Type::ANIMATION, ObjectGraphic::Slot::UPPER);

      if (isPressJumping)
      {
        if (Keyboard::Get()->Press(VK_SPACE))
        {
          if (jumpProgress < 0.2)
          {
            movement->Jumping();
          }
          jumpProgress += Time::Get()->WorldDelta();
        }
        else
        {
          isPressJumping = false;
        }
      }

      if (Keyboard::Get()->Press('A') && !Keyboard::Get()->Press('D'))
      {
        movement->MoveLeft();
      }
      else if (Keyboard::Get()->Press('D') && !Keyboard::Get()->Press('A'))
      {
        movement->MoveRight();
      }
      else
      {
        movement->SlowDown();
      }
      break;
    }
    default:
      break;
    }
  }

  if (Keyboard::Get()->Press(VK_LSHIFT) == false)
  {
    isPressSliding = false;
  }

  // Combat
  {
  
  auto combat = agent.GetCombat();
  auto rifle = combat->GetRifle();

  switch (agent.GetCombatState())
  {
  case Agent::CombatState::AIMING_RIFLE:
    if (isChangingGlobalSpeed)
    {
      if (globalSpeed < 1.0) Time::Get()->SetGlobalSpeed(globalSpeed + 0.0533333333333333);
      else
      {
        isChangingGlobalSpeed = false;
        Time::Get()->SetGlobalSpeed(1.0);
      }
    }

    if (combat->GetIsThrowing()) break;
    
    graphic->SetCurrentAnimation(L"aim_rifle");
    
    if (Mouse::Get()->Press(0) || Mouse::Get()->Down(0)) rifle->PullTrigger();
    else rifle->ReleaseTrigger();

    if (Keyboard::Get()->Down('B')) rifle->SwitchMode();
    if (Keyboard::Get()->Down('R'))
    {
      if (rifle->magazineIsFull() == false)
      {
        rifle->ReloadBegin();
        graphic->SetCurrentAnimation(L"reload_rifle");
        agent.SetCombatState(Agent::CombatState::RELOADING);
      }
    }

    if (Keyboard::Get()->Down('G'))
    {
      if (combat->IsLeftGrenade())
      {
        isChangingGlobalSpeed = true;
        agent.SetCombatState(Agent::CombatState::AIMING_THROWABLE);
      }
    }
    break;
  case Agent::CombatState::RELOADING:
    if (rifle->GetIsReloading() == false)
    {
      graphic->SetCurrentAnimation(L"aim_rifle");
      agent.SetCombatState(Agent::CombatState::AIMING_RIFLE);
    }
    break;
  case Agent::CombatState::AIMING_THROWABLE:
    if (isChangingGlobalSpeed)
    {
      if (globalSpeed > 0.2) Time::Get()->SetGlobalSpeed(globalSpeed - 0.0533333333333333);
      else
      {
        isChangingGlobalSpeed = false;
        Time::Get()->SetGlobalSpeed(0.2);
      }
    }

    rifle->ReleaseTrigger();

    if (Keyboard::Get()->Press('G') == false)
    {
      isChangingGlobalSpeed = true;
      agent.SetCombatState(Agent::CombatState::AIMING_RIFLE);
      break;
    }

    if (Mouse::Get()->Down(0))
    {
      graphic->SetCurrentAnimation(L"throw_rifle");
      combat->ThrowGrenade();
      isChangingGlobalSpeed = true;
      agent.SetCombatState(Agent::CombatState::AIMING_RIFLE);
      break;
    }
    break;
  case Agent::CombatState::MELEE:
    break;
  default:
    break;
  }
  //rifle->Update(agent.GetPosition(), agent.GetAgentLookAtAxis());
  }
}

void Input::Render(Agent& agent)
{
  crosshair->Render();
}

void Input::GUI()
{
}
