#pragma once
#include "Game/GameObject.h"
#include "Interface/Movement/IMovement.h"

class Character : public GameObject {
 public:
  Character(Vector3 position, Vector3 size);
  virtual ~Character();

  virtual void update();
  virtual void render();
};