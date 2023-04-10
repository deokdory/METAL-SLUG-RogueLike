#pragma once
#include "Game/GameObject.h"

class Character : public GameObject {
 public:
  Character(Vector3 position, Vector3 size);
  virtual ~Character();

  void update();
  void render();

  void moveLeft();
  void moveRight();
  void jump();

  void falling();

 protected:
  float ySpeed = 0.0f;
  bool isFalling = false;
};