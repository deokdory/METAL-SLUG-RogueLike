#pragma once

#include "Character.h"
#include "Component/Movement/IPlayerMovement.h"

class PlaybleCharacter : public Character {
 public:
  PlaybleCharacter(Vector3 position, Vector3 size);
  ~PlaybleCharacter();

  virtual void update();
  virtual void render();

  IPlayerMovement* GetMovement() { return movement; }

 private:
  IPlayerMovement* movement = nullptr;
};