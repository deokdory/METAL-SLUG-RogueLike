#include "stdafx.h"
#include "Agent.h"

#include "Component/Collision/Collision.h"
#include "Component/Graphic/ObjectGraphic.h"


Agent::Agent(Vector3 position, Vector3 size)
  : Character(position, size) 
{
  input = new Input();
  type = Type::PLAYER;

  movement = new PlayerMovement(this);
  combat = new PlayerCombat(*this);
} 

Agent::~Agent() {
  SAFE_DELETE(movement);
  SAFE_DELETE(input);
}

void Agent::HandleInput()
{

}

void Agent::Update()
{
  input->Update(*this);

  float rightAngle = D3DXVec3Dot(&Values::RightVec, &agentLookAtAxis);

  if (rightAngle < 0) isFliped = true;
  else isFliped = false;

  // MovementState
  {
    switch (movementState)
    {
    case Agent::MovementState::SLIDING:
    {
      movement->SlowDown();

      if (std::abs(movement->GetXSpeedOrigin()) < 0.5f)
      {
        movement->SlideEnd();
        movementState = MovementState::ONGROUND;
      }
    }
    case Agent::MovementState::ONGROUND:
    {
      if (movement->GetIsFalling())
      {
        if (isFliped == true)
        {
          if (movement->GetXSpeedOrigin() < -1.f)
          {
            graphic->SetCurrentAnimation(L"jumpBegin_run", ObjectGraphic::Slot::LOWER);
            movementState = MovementState::FALLING_MOVE;
          }
          else
          {
            graphic->SetCurrentAnimation(L"jumpBegin_stand", ObjectGraphic::Slot::LOWER);
            movementState = MovementState::FALLING;
          }
        }
        if (isFliped == false)
        {
          if (movement->GetXSpeedOrigin() > 1.f)
          {
            graphic->SetCurrentAnimation(L"jumpBegin_run", ObjectGraphic::Slot::LOWER);
            movementState = MovementState::FALLING_MOVE;
          }
          else
          {
            graphic->SetCurrentAnimation(L"jumpBegin_stand", ObjectGraphic::Slot::LOWER);
            movementState = MovementState::FALLING;
          }
        }
      }
      break;
    }
    case Agent::MovementState::FALLING:
    {
      if (movement->GetIsFalling() == false)
      {
        if (abs(movement->GetXSpeedOrigin()) > 2)
          graphic->SetCurrentAnimation(L"run", ObjectGraphic::Slot::LOWER);

        movementState = MovementState::ONGROUND;
      }

      if (movement->GetYSpeedOrigin() < 0)
      {
        graphic->SetCurrentAnimation(L"jumpEnd_stand", ObjectGraphic::Slot::LOWER);
      }
      break;
    }
    case Agent::MovementState::FALLING_MOVE:
    {
      if (movement->GetIsFalling() == false)
      {
        if (abs(movement->GetXSpeedOrigin()) > 2)
          graphic->SetCurrentAnimation(L"run", ObjectGraphic::Slot::LOWER);

        movementState = MovementState::ONGROUND;
      }

      if (movement->GetYSpeedOrigin() < 0)
      {
        graphic->SetCurrentAnimation(L"jumpEnd_run", ObjectGraphic::Slot::LOWER);
      }
      break;
    }
    default:
      break;
    }
  }


  // CombatState
  {
    float aimAngle = D3DXVec3Dot(&Values::UpVec, &agentLookAtAxis);

    aimAngle = std::acos(aimAngle);
    aimAngle = D3DXToDegree(aimAngle);

    switch (combatState)
    {
    case Agent::CombatState::AIMING_RIFLE:

      if (combat->GetIsThrowing() == false)
      {
        if (abs(aimAngle) < 10.f)  graphic->SetCurrentFrame(9, ObjectGraphic::Slot::UPPER);
        else if (abs(aimAngle) < 25.f)  graphic->SetCurrentFrame(8, ObjectGraphic::Slot::UPPER);
        else if (abs(aimAngle) < 35.f)  graphic->SetCurrentFrame(7, ObjectGraphic::Slot::UPPER);
        else if (abs(aimAngle) < 55.f)  graphic->SetCurrentFrame(6, ObjectGraphic::Slot::UPPER);
        else if (abs(aimAngle) < 90.f)  graphic->SetCurrentFrame(5, ObjectGraphic::Slot::UPPER);
        else if (abs(aimAngle) < 115.f) graphic->SetCurrentFrame(4, ObjectGraphic::Slot::UPPER);
        else if (abs(aimAngle) < 145.f) graphic->SetCurrentFrame(3, ObjectGraphic::Slot::UPPER);
        else if (abs(aimAngle) < 160.f) graphic->SetCurrentFrame(2, ObjectGraphic::Slot::UPPER);
        else if (abs(aimAngle) < 170.f) graphic->SetCurrentFrame(1, ObjectGraphic::Slot::UPPER);
        else if (abs(aimAngle) < 180.f) graphic->SetCurrentFrame(0, ObjectGraphic::Slot::UPPER);
      }
      break;
    case Agent::CombatState::RELOADING:
      if (combat->GetRifle()->GetIsReloading() == false)
      {
        graphic->SetCurrentAnimation(L"aim_rifle");
        combatState = Agent::CombatState::AIMING_RIFLE;
      }
      break;
    case Agent::CombatState::AIMING_THROWABLE:
      break;
    case Agent::CombatState::MELEE:
      break;
    default:
      break;
    }
  }

  __super::Update();
  movement->Update();
  combat->Update(*this);

  auto mousePos = Mouse::Get()->GetPosition();

  mousePos.x -= (float)WinMaxWidth / 2;
  mousePos.y -= (float)WinMaxHeight / 2;
  mousePos.z = 0.0f;

  Camera::Get()->SetPosition(position + mousePos / 4);
}

void Agent::Render() 
{
  
    __super::Render();
  movement->Render();
  combat->Render();

  input->Render(*this);
}

void Agent::GUI()
{
  std::string movementStateStr = "MovementState : ";
  switch (movementState)
  {
  case Agent::MovementState::ONGROUND:
    movementStateStr += "on ground";
    break;
  case Agent::MovementState::FALLING:
    movementStateStr += "falling";
    break;
  case Agent::MovementState::FALLING_MOVE:
    movementStateStr += "falling(move)";
    break;
  case Agent::MovementState::SLIDING:
    movementStateStr += "sliding";
    break;
  default:
    break;
  }

  std::string combatStateStr = "CombatState : ";
  switch (combatState)
  {
  case Agent::CombatState::AIMING_RIFLE:
    combatStateStr += "aiming(rifle)";
    break;
  case Agent::CombatState::RELOADING:
    combatStateStr += "reloading";
    break;
  case Agent::CombatState::AIMING_THROWABLE:
    combatStateStr += "aiming(throw)";
    break;
  case Agent::CombatState::MELEE:
    combatStateStr += "melee attack";

    break;
  default:
    break;
  }


  ImGui::Begin("State");
  {
    ImGui::Text(movementStateStr.c_str());
    ImGui::Text(combatStateStr.c_str());
  }
  ImGui::End();

  movement->GUI();
  combat->GUI();
  input->GUI();

  __super::GUI();
}
