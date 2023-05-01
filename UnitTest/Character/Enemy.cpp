#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(Vector3 position, Vector3 size)
  : Character(position, size)
{
  movement = new Movement(this);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
  if (isDead)
  {
    timerAfterDead += Time::Get()->WorldDelta();
    if (timerAfterDead > 5.0) isWaitingDelete = true;
  }

  if (hp <= 0) Die();

  __super::Update();
}

void Enemy::Render()
{
  __super::Render();
}

void Enemy::Die()
{
  graphic->SetCurrentAnimation(L"die");
  isDead = true;
}
