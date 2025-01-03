#pragma once
#include "Utilities/Movements/Movement.h"

class Character : public GameObject {
 public:
  Character(Vector3 position, Vector3 size);
  virtual ~Character();

  virtual void Update();
  virtual void Render();

  float GetHP() { return hp; }
  float GetMaxHP() { return maxHP; }
  bool GetIsDead() { return isDead; }

  virtual void Damaged(float damage);
  virtual void Healed(float heal);

protected:

  float hp;
  float maxHP = 20.0f;

  bool isDead = false;
};