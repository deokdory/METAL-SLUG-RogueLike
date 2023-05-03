#pragma once
#include "Character/Character.h"
#include "Game/UI/ProgressBar.h"

class Enemy : public Character
{
public:
  Enemy(Vector3 position, Vector3 size);
  virtual ~Enemy();

  virtual void Update();
  virtual void Render();

  virtual void Damaged(float damage) override;
  virtual void Healed(float heal) override;

  virtual void Die();
protected:

  ProgressBar* hpBar = nullptr;

  Movement* movement;
  double timerAfterDead = 0.0;

  double hitAnimTimer = 0.0;
  bool isHit = false;

  
};