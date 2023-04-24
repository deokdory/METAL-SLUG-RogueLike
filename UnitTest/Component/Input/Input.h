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
  Vector3 mouseWorldPos = Values::ZeroVec3;
  //PlayerCombat* combat = nullptr;
};