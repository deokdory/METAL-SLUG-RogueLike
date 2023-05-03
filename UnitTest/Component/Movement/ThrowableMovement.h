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

protected:
  virtual void collisionCheck() override;
  float bounce = 0.0f;
};