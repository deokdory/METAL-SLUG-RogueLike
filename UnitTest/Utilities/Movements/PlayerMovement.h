#pragma once
#include "Movement.h"

class PlayerMovement : public Movement
{
public:
  PlayerMovement(class GameObject* object);
  ~PlayerMovement();

  virtual void Update() override;

  void Jumping();

  void Slide() { isSliding = true; }
  void SlideEnd() { isSliding = false; }

  virtual void UpdateAccel();

  void SetIsJumping(bool isJumping) { this->isJumping = isJumping; }
  bool GetIsJumping() { return isJumping; }

private:
  bool isJumping = false;
  bool isSliding = false;
};