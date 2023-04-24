#pragma once
#include "Character/Agent.h"

class AgentMovementState 
{
public:
  virtual void HandleInput() = 0;
  virtual void Update() = 0;
  virtual void Enter() = 0;
};

class AgentOnGroundState : public AgentMovementState
{
  virtual void HandleInput(GameObject& object);
  virtual void Update(GameObject& object);
  virtual void Enter(GameObject& object);
};

class AgentSlidingState : public AgentOnGroundState
{
  virtual void HandleInput(GameObject& object);
  virtual void Update(GameObject& object);
  virtual void Enter(GameObject& object);
};

class AgentFallingState : public AgentMovementState
{
  virtual void HandleInput(GameObject& object);
  virtual void Update(GameObject& object);
  virtual void Enter(GameObject& object);
};

class AgentCrouchingState : public AgentOnGroundState
{
  virtual void HandleInput(GameObject& object);
  virtual void Update(GameObject& object);
  virtual void Enter(GameObject& object);
};