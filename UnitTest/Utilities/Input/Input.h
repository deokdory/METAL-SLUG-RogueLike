#pragma once
#include "Geometries/TextureRect.h"

#include "Utilities/Movements/PlayerMovement.h"
#include "Utilities/Combat/PlayerCombat.h"

class Input
{
public:
  Input();
  ~Input();

  virtual void Update(class Agent& agent);
  virtual void Render(class Agent& agent);
  virtual void GUI();

  Vector3 GetMouseWorldPosition() { return mouseWorldPos; }

protected:
  void updateThrowLine(class Agent& agent, Vector3 position, Vector3 axis, float strength);

  Vector3 mouseWorldPos = Values::ZeroVec3;

  bool isPressJumping = false;
  double jumpProgress = 0.0;

  bool isPressSliding = false;
  //PlayerCombat* combat = nullptr;

  float strengthMin = 5.0f;
  bool isPressThrowing = false;
  double throwProgress = 0.0;

  double throwingTime = 0.0;
  double throwingTimeMax = 3.0;

  bool isChangingGlobalSpeed = false;

  TextureRect* crosshair = nullptr;
  TextureRect* grenadeCursor = nullptr;
  std::vector<TextureRect*> throwLine;
};