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

  bool isFalling = false;

  float ySpeed = 0.0f;
  float gravity = 0.3f;
  float jumpPower = 7.f;

  float fallingSpeedMax = -12.f;

  float xSpeedMax = 6.f;
  float xSpeed = 0.f;

  float accelOrigin = .25f;
  float accel = 0.f;
};