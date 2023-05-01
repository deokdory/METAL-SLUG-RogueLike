#pragma once
#include "Character/Character.h"
class Enemy : public Character
{
public:
  Enemy(Vector3 position, Vector3 size);
  virtual ~Enemy();

  virtual void Update();
  virtual void Render();

  virtual void Die();
protected:
  Movement* movement;
  bool isDead = false;

  double timerAfterDead = 0.0;
};