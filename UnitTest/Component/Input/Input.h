#pragma once
#include "Component/Movement/PlayerMovement.h"

class Input
{
public:
  Input();
  ~Input();

  virtual void Update();
  virtual void Render();
  virtual void GUI();

protected:
  PlayerMovement* movement = nullptr;
  //PlayerCombat* combat = nullptr;

  Vector3 axis = Values::ZeroVec3;
};