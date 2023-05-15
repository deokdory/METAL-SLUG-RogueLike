#pragma once
#include "Character.h"

#include "Utilities/Movements/PlayerMovement.h"
#include "Utilities/Input/Input.h"

class Agent : public Character {
public:
  enum class MovementState { ONGROUND, FALLING, FALLING_MOVE, SLIDING };
  enum class CombatState { AIMING_RIFLE, RELOADING, AIMING_THROWABLE, MELEE };

  Agent(Vector3 position, Vector3 size);
  ~Agent();

  void HandleInput();

  virtual void Update();
  virtual void Render();
  virtual void GUI();

  void SetMovementState(MovementState movementState) { this->movementState = movementState; }
  MovementState GetMovementState() { return movementState; }

  void SetCombatState(CombatState combatState) { this->combatState = combatState; }
  CombatState GetCombatState() { return combatState; }

  PlayerMovement* GetMovement() { return movement; }
  PlayerCombat* GetCombat() { return combat; }

  void SetAgentLookAtAxis(Vector3 axis) { this->agentLookAtAxis = axis; }
  Vector3 GetAgentLookAtAxis() { return agentLookAtAxis; }

private:
  Vector3 agentLookAtAxis = Values::ZeroVec3;

  Input* input = nullptr;

  PlayerMovement* movement = nullptr;
  MovementState movementState = MovementState::ONGROUND;

  PlayerCombat* combat = nullptr;
  CombatState combatState = CombatState::AIMING_RIFLE;
};