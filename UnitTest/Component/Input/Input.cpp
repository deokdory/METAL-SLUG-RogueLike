#include "stdafx.h"
#include "Input.h"

#include "Character/Agent.h"
#include "Component/Combat/Throwable/Throwable.h"
#include "Component/Movement/ThrowableMovement.h"

Input::Input()
{
  crosshair = new TextureRect(Values::ZeroVec3, Vector3(72, 72, 0), 0, TexturePath + L"crosshair003.png");
  grenadeCursor = new TextureRect(Values::ZeroVec3, Vector3(20, 22, 0), 0, TexturePath + L"grenade_cursor.png");
  throwLine.assign(10, nullptr);

  for (int i = 0; i < 10; i++)
  {
    throwLine[i] = new TextureRect({}, { 72, 72, 0 }, 0, TexturePath + L"crosshair001.png");
  }
}

Input::~Input()
{
  SAFE_DELETE(crosshair);
}

void Input::Update(Agent& agent)
{
  double globalSpeed = Time::Get()->GetGlobalSpeed();
  auto graphic = agent.GetGraphic();
 
  auto movement = agent.GetMovement();

  float xSpeed = movement->GetXSpeedOrigin();
  float ySpeed = movement->GetYSpeedOrigin();

  auto combat = agent.GetCombat();

  // Global Speed Test
  if (Keyboard::Get()->Down(VK_F4)) Time::Get()->SetGlobalSpeed(0.25f);
  if (Keyboard::Get()->Down(VK_F5)) Time::Get()->SetGlobalSpeed(1.00f);

  // Mouse And SetAxis

  Vector3 agentPosition = agent.GetPosition();
  Vector3 mousePos = Mouse::Get()->GetPosition();

  mouseWorldPos = mousePos + Camera::Get()->GetPosition();
  mouseWorldPos.z = 0.f;

  auto agentLookAtAxis = mouseWorldPos - agentPosition;
  D3DXVec3Normalize(&agentLookAtAxis, &agentLookAtAxis);

  crosshair->SetPosition(mouseWorldPos);
  grenadeCursor->SetPosition(mouseWorldPos);

  crosshair->Update();
  grenadeCursor->Update();

  agent.SetAgentLookAtAxis(agentLookAtAxis);

  // Movement
  {
    auto movementState = agent.GetMovementState();

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
        if (xSpeed < 0.5f)
        {
          graphic->SetCurrentAnimation(L"idle", ObjectGraphic::Slot::LOWER);
        }
      }

      // 슬라이딩
      if (std::abs(xSpeed) > 2 && Keyboard::Get()->Press(VK_LSHIFT) && isPressSliding == false)
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
        if (xSpeed < 0.5f)
          if (Keyboard::Get()->Press('D'))
            movement->MoveRight();

        if (xSpeed > 0.5f)
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
      //isChangingGlobalSpeed = true;
      //Time::Get()->SetGlobalSpeed(1.0);
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

    if (Keyboard::Get()->Down('G') || Mouse::Get()->Down(1) || throwingTime >= throwingTimeMax)
    {
      if (isPressThrowing == false)
      {
        agent.SetCombatState(Agent::CombatState::AIMING_RIFLE);
        break;
      }
    }

    if (Mouse::Get()->Down(0))
    {
      isChangingGlobalSpeed = true;
      throwingTime = 0.0;

      isPressThrowing = true;
      throwProgress = 0.0;
      throwingTime = 0.0;

      float strength = strengthMin + throwProgress * 5;
      updateThrowLine(agent, agentPosition, agentLookAtAxis, strength);
    }

    if (Mouse::Get()->Press(0))
    {
      float strength = strengthMin + throwProgress * 5;
      updateThrowLine(agent, agentPosition, agentLookAtAxis, strength);

      if (isPressThrowing)
      {
        throwingTime += Time::Get()->WorldOriginDelta();
        throwProgress += Time::Get()->WorldOriginDelta();
        if (throwProgress > 2.0) throwProgress = 2.0;
      }
    }

    if (Mouse::Get()->Up(0) || throwingTime >= 3.0)
    {
      if (isPressThrowing)
      {
        float strength = strengthMin + throwProgress * 5;

        graphic->SetCurrentAnimation(L"throw_rifle");
        combat->ThrowGrenade(agentPosition, agentLookAtAxis, strength);

        isPressThrowing = false;
        throwProgress = 0.0;
        throwingTime = 0.0;

        isChangingGlobalSpeed = true;
        agent.SetCombatState(Agent::CombatState::AIMING_RIFLE);
      }
    }
    break;
  case Agent::CombatState::MELEE:
    break;
  default:
    break;
  }
  }
}

void Input::Render(Agent& agent)
{
  auto combatState = agent.GetCombatState();

  switch (combatState)
  {
  case Agent::CombatState::AIMING_RIFLE:
  case Agent::CombatState::RELOADING:
  case Agent::CombatState::MELEE:
    crosshair->Render();
    break;
  case Agent::CombatState::AIMING_THROWABLE:
    if (isPressThrowing)
      for (TextureRect* dot : throwLine) dot->Render();
    else grenadeCursor->Render();
    break;
  default:
    break;
  }


}

void Input::GUI()
{
  std::string throwStr = "strength : " + std::to_string(throwProgress);
  
  ImVec4 gray = ImVec4(0.76f, 0.77f, 0.8f, 1.0f);
  ImVec4 red = ImVec4(1, 0, 0, 1);

  ImVec4 color;

  ImGui::Begin("Combat");
  {
    if (throwProgress >= 1.5) color = red;
    else color = gray;

    ImGui::TextColored(color, throwStr.c_str());
  }
  ImGui::End();
}

void Input::updateThrowLine(Agent& agent, Vector3 position, Vector3 axis, float strength)
{
  float gravity = 
    GameManager::Get()->GetGlobalGravity() + 
    agent.GetCombat()->GetThrowable()->GetMovement()->GetGravityOffset();

  float fallingSpeedMax = 
    agent.GetCombat()->GetThrowable()->GetMovement()->GetFallingSpeedMax();

  UINT MS_PER_UPDATE = 60;
  //double spacing = ((double)MS_PER_UPDATE / 10) * (strength / 7.5f);

  Vector3 speed = axis * strength;
  Vector3 tempPosition = position;

  for (int i = 0; i < 10; i++)
  {
    for (int i = 0; i < MS_PER_UPDATE / 10; i++)
    {
      tempPosition.x += speed.x;
      tempPosition.y += speed.y;

      speed.y -= gravity;
      if (speed.y < fallingSpeedMax) speed.y = fallingSpeedMax;
    }

    float size = 72.f - (72.f / 10) * i;

    throwLine[i]->SetPosition(tempPosition);
    throwLine[i]->SetSize({ size, size, 0 });
    throwLine[i]->Update();
  }
}
