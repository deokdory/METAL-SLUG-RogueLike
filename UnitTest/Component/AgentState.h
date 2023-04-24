#pragma once
#include "Character/Agent.h"

class AgentMovementState 
{
public:
  virtual void HandleInput(Agent& agent) = 0;

  virtual void Update(Agent& agent) = 0;
  virtual void GUI(Agent& agent) = 0;

  virtual void Enter(Agent& agent) = 0;

};

class AgentRunning : public AgentMovementState
{
  virtual void HandleInput(Agent& agent);

  virtual void Update(Agent& agent);
  virtual void GUI(Agent& agent);

  virtual void Enter(Agent& agent);
};

class AgentCombatState
{
  virtual void HandleInput(Agent& agent) = 0;

  virtual void Update(Agent& agent) = 0;
  virtual void GUI(Agent& agent) = 0;

  virtual void Enter(Agent& agent) = 0;
  
  bool GetIsMoveable() { return isMoveable; }

protected:
  bool isMoveable = true;
};