#pragma once

#include "Character.h"
#include "Component/Movement/IPlayerMovement.h"

class Agent : public Character {
 public:
  Agent(Vector3 position, Vector3 size);
  ~Agent();

  virtual void update();
  virtual void render();

  IPlayerMovement* GetMovement() { return movement; }

 private:
  IPlayerMovement* movement = nullptr;
};