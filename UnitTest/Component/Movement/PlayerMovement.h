#pragma once
#include "Component/Movement/Movement.h"

class PlayerMovement : public Movement
{
public:
  PlayerMovement(class GameObject* object);
  ~PlayerMovement();

  virtual void Update() override;

  virtual void Jump() override;

  void Jumping();

  void Slide() { isSliding = true; }
  void SlideEnd() { isSliding = false; }

  virtual void UpdateAccel();

  void SetIsJumping(bool isJumping) { this->isJumping = isJumping; }
  bool GetIsJumping() { return isJumping; }

private:
  virtual void collisionCheck();
  bool isJumping = false;
  bool isSliding = false;
};