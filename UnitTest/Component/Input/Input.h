#pragma once
#include "Component/Movement/PlayerMovement.h"
#include "Geometries/TextureRect.h"
#include "Component/Combat/PlayerCombat.h"

class Input
{
public:
  Input();
  ~Input();

  virtual void Update(class Agent& agent);
  virtual void Render(class Agent& agent);
  virtual void GUI();

protected:
  Vector3 mouseWorldPos = Values::ZeroVec3;

  bool isPressJumping = false;
  double jumpProgress = false;

  bool isPressSliding = false;
  //PlayerCombat* combat = nullptr;

  bool isChangingGlobalSpeed = false;

  TextureRect* crosshair = nullptr;
};