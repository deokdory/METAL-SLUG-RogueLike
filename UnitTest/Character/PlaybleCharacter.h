#pragma once

#include "Character.h"
#include "Interface/Movement/IPlayerMovement.h"

class PlaybleCharacter : public Character {
 public:
  PlaybleCharacter(Vector3 position, Vector3 size);
  ~PlaybleCharacter();

 private:
  IPlayerMovement* movement = nullptr;
};