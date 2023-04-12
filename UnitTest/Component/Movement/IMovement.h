#pragma once

#include "Game/GameObject.h"
#include "Level/Level.h"

class IMovement {
 public:
  IMovement(GameObject* object);
  
  virtual void update();

  void moveLeft();
  void moveRight();
  void SlowDown();
  void Stop();

  virtual void jump();
  virtual void render();

  void SetLevel(Level* level) { this->level = level; }

  void CollisionCheck();

 protected:
  GameObject* object = nullptr;
  Level* level = nullptr;

  double delta = 0.0;

  bool isFalling = false;

  float ySpeed = 0.0f;
  float gravity = 40.0f;
  float jumpPower = 600.0f;

  float fallingSpeedMax = -800.0f;

  float xSpeedMax = 400.0f;
  float xSpeed = 0.f;

  float accelOrigin = 25.f;
  float accel = 0.f;
};