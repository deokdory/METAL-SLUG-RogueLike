#pragma once
#include "Game/GameObject.h"

class Bullet : public GameObject {
public:
  // FRIEND OR ENEMY
  enum class Side {
    PLAYER = 0, ENEMY
  };

  Bullet(GameObject* fired, Side side, float speed, float damage, std::wstring texturePath);

  ~Bullet();

  virtual void Update();
  virtual void Render();

  virtual void hit(GameObject* object);

  Bullet* NewBullet(Vector3 position, Vector3 axis);

protected:
  Bullet(Vector3 position, Vector3 axis);
  GameObject* fired;

  Side side;

  Vector3 axis = Values::ZeroVec3;

  float damage;
  float speed;

  bool bHit = false;
};