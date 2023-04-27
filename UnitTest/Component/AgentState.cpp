#include "AgentState.h"
#include "stdafx.h"
#include "AgentState.h"

#include "Character/Agent.h"

void AgentOnGroundState::HandleInput(Agent& agent)
{
  if (Keyboard::Get()->Press('A') && !Keyboard::Get()->Press('D')) {
    agent.GetGraphic()->SetCurrentAnimation(L"run", ObjectGraphic::Slot::LOWER);
    agent.GetMovement()->MoveLeft();
  }
  else if (Keyboard::Get()->Press('D') && !Keyboard::Get()->Press('A')) {
    agent.GetGraphic()->SetCurrentAnimation(L"run", ObjectGraphic::Slot::LOWER);
    agent.GetMovement()->MoveRight();
  }
  else {
    agent.GetMovement()->SlowDown();
    if (agent.GetMovement()->GetXSpeed() < 0.5f);
        agent.GetGraphic()->SetCurrentAnimation(L"idle", ObjectGraphic::Slot::LOWER);
  }
}

void AgentOnGroundState::Update(Agent& agent)
{
  if (agent.GetMovement()->GetIsFalling())
  {
    fallingState.Enter(agent);
    //agent.SetMovementState(&AgentMovementStates.fallingState);
  }
}

void AgentOnGroundState::Enter(Agent& agent)
{
}

void AgentCrouchingState::HandleInput(Agent& agent)
{
}

void AgentCrouchingState::Update(Agent& agent)
{
}

void AgentCrouchingState::Enter(Agent& agent)
{
}

void AgentSlidingState::HandleInput(Agent& agent)
{
}

void AgentSlidingState::Update(Agent& agent)
{
}

void AgentSlidingState::Enter(Agent& agent)
{
}

void AgentFallingState::HandleInput(Agent& agent)
{
  if (Keyboard::Get()->Press('A') && !Keyboard::Get()->Press('D'))
  {
    agent.GetMovement()->MoveLeft();
  }
  else if (Keyboard::Get()->Press('D') && !Keyboard::Get()->Press('A')) 
  {
    agent.GetMovement()->MoveRight();
  }
  else
  {
    agent.GetMovement()->SlowDown();
  }
}

void AgentFallingState::Update(Agent& agent)
{
  if (agent.GetMovement()->GetIsFalling() == false)
  {
    onGroundState.Enter(agent);
    //agent.SetMovementState(&AgentMovementStates.onGroundState);
  }

  if (agent.GetMovement()->GetYSpeed() < 0)
  {
    agent.GetGraphic()->SetCurrentAnimation(L"jumpEnd_stand", ObjectGraphic::Slot::LOWER);
  }
}

void AgentFallingState::Enter(Agent& agent)
{
  if (abs(agent.GetMovement()->GetXSpeed()) > 2)
  {
    fallingMovingState.Enter(agent);
    //agent.SetMovementState(&AgentMovementStates.fallingMovingState);
  }
  else
  {
    agent.GetGraphic()->SetCurrentAnimation(L"jumpBegin_stand", ObjectGraphic::Slot::LOWER);
  }
}

void AgentFallingMovingState::HandleInput(Agent& agent)
{
  __super::HandleInput(agent);
}

void AgentFallingMovingState::Update(Agent& agent)
{
  if (agent.GetMovement()->GetIsFalling() == false)
  {
    onGroundState.Enter(agent);
    //agent.SetMovementState(&AgentMovementStates.onGroundState);
  }

  if (agent.GetMovement()->GetYSpeed() < 0)
  {
    agent.GetGraphic()->SetCurrentAnimation(L"jumpEnd_run", ObjectGraphic::Slot::LOWER);
  }
}

void AgentFallingMovingState::Enter(Agent& agent)
{
  agent.GetGraphic()->SetCurrentAnimation(L"jumpBegin_run", ObjectGraphic::Slot::LOWER);
}

void AgentMovementStates::HandleInput(Agent& agent)
{
  movementState->HandleInput(agent);
}
void AgentMovementStates::Update(Agent& agent)
{
  movementState->Update(agent);
}
void AgentMovementStates::Enter(Agent& agent)
{
  movementState->Enter(agent);
}