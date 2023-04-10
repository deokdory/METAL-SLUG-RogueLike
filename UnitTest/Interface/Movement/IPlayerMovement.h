#pragma once
#include "IMovement.h"

class IPlayerMovement : public IMovement {
 public:
  IPlayerMovement(GameObject* object);

  virtual void update();
};
