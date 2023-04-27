#pragma once

class AgentCombat
{
public:
  AgentCombat(class Agent* agent);
  ~AgentCombat();

  virtual void Update();
  virtual void GUI();

protected:
  class Agent* agent;
};