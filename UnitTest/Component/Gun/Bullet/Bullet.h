#pragma once
#include "Game/GameObject.h"

class Bullet : public GameObject {
public:
  // FRIEND OR ENEMY
  enum class Side {
    PLAYER = 0, ENEMY
  };

  Bullet(GameObject* fired, Side side, Vector3 axis, float speed = 16.0f, float damage = 2.0f);
  ~Bullet();

  virtual void Update();
  virtual void Render();

  virtual void hit(GameObject* object);

private:
  GameObject* fired;

  Side side;

  Vector3 axis;

  float damage;
  float speed;

  bool bHit = false;
};