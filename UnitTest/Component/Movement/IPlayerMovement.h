#pragma once
#include "IMovement.h"

class IPlayerMovement : public IMovement {
 public:
  IPlayerMovement(GameObject* object);

  void jumpBegin();
  void jumping();
  void jumpEnd();

  virtual void update();

  protected:
  bool isJumping = false;
  double jumpedTime = 0.f;
};
