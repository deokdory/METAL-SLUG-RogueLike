#pragma once

#include "Character.h"

class Agent : public Character {
 public:
   enum class State {
     GROUND = 0, FALLING, SLIDING, MELEE_ATTACK
   };

  Agent(Vector3 position, Vector3 size);
  ~Agent();

  virtual void Update();
  virtual void Render();

  class AgentInput* GetMovement() { return movement; }
  State GetState() { return state; }

  State SetState(State state) { this->state = state; }

 private:
  class AgentInput* movement = nullptr;
  State state = State::GROUND;
};