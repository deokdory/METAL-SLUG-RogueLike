#pragma once
#include "Game/GameObject.h"

class Character : public GameObject {
 public:
  Character(Vector3 position, Vector3 size);
  virtual ~Character();

  virtual void Update();
  virtual void Render();

  virtual void Damaged(float damage);
  virtual void Healed(float heal);

  bool GetIsDead() { return isDead; }

protected:
  float hp;
  float hpMax = 20.0f;

  bool isDead = false;
};