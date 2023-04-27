#pragma once

class AgentMovementState
{
public:
  AgentMovementState() = default;

  virtual void HandleInput(class Agent& agent) {}
  virtual void Update(class Agent& agent) {}
  virtual void Enter(class Agent& agent) {}

};

class AgentOnGroundState : public AgentMovementState
{
public:

  virtual void HandleInput(class Agent& agent) override;
  virtual void Update(class Agent& agent) override;
  virtual void Enter(class Agent& agent) override;
};

class AgentCrouchingState : public AgentOnGroundState
{
public:
  virtual void HandleInput(class Agent& agent);
  virtual void Update(class Agent& agent);
  virtual void Enter(class Agent& agent);
};

class AgentSlidingState : public AgentCrouchingState
{
public:
  virtual void HandleInput(class Agent& agent);
  virtual void Update(class Agent& agent);
  virtual void Enter(class Agent& agent);
};

class AgentFallingState : public AgentMovementState
{
public:
  virtual void HandleInput(class Agent& agent);
  virtual void Update(class Agent& agent);
  virtual void Enter(class Agent& agent);
};

class AgentFallingMovingState : public AgentFallingState
{
public:
  virtual void HandleInput(class Agent& agent);
  virtual void Update(class Agent& agent);
  virtual void Enter(class Agent& agent);
};

class AgentMovementStates
{
public:
  AgentMovementStates();
  ~AgentMovementStates();

  virtual void HandleInput(class Agent& agent);
  virtual void Update(class Agent& agent);
  virtual void Enter(class Agent& agent);

  AgentMovementState* movementState;

  AgentOnGroundState ongRoundState;
  AgentCrouchingState crouchingState;
  AgentSlidingState slidingState;
  AgentFallingState fallingState;
  AgentFallingMovingState fallingMovingState;
};