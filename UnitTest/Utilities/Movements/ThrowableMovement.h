#pragma once
#include "Movement.h"

class ThrowableMovement : public Movement
{
public:
  ThrowableMovement(class GameObject* object, float xSpeed, float ySpeed);
  ~ThrowableMovement();

  virtual void Update() override;
  virtual void Render() override;
  virtual void GUI() override;

  virtual void Falling() override;

protected:
  virtual void collisionCheck() override;
  Vector3 bounce = Values::ZeroVec3;
};