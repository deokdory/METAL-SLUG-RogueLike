#pragma once

#include "Game/GameObject.h"
#include "Level/Level.h"

class IMovement {
 public:
  IMovement(GameObject* object);
  
  virtual void update();

  void moveLeft();
  void moveRight();
  void jump();

  void SetLevel(Level* level) { this->level = level; }

 protected:
  GameObject* object = nullptr;
  Level* level = nullptr;

  float ySpeed = 0.0f;
  float gravity = 20.0f;
  float jumpPower = 20.f;

  float xSpeed = 0.f;
  float accel = 1.f;
};