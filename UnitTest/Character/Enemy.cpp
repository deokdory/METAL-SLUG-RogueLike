#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(Vector3 position, Vector3 size)
  : Character(position, size)
{
  movement = new Movement(this);
  hpBar = new ProgressBar(position, { 30, 5, 0 }, 0.0f, Values::Red ,UI::FillType::LEFT_TO_RIGHT);
}

Enemy::~Enemy()
{
  SAFE_DELETE(movement);
}

void Enemy::Update()
{
  if (isDead)
  {
    timerAfterDead += Time::Get()->WorldDelta();

    if (timerAfterDead > 2.0)
    {
      graphic->FadeOut(1.0f, ObjectGraphic::Type::ANIMATION);
    }

    if (timerAfterDead > 3.0) isWaitingDelete = true;
  }
  else
  {
    if (hp <= 0.0f) Die();

    if (isHit)
    {
      if (hitAnimTimer > 0.22222222)
      {
        graphic->SetCurrentAnimation(L"idle");
      }
      else hitAnimTimer += Time::Get()->WorldDelta();
    }
    else
    {
      //movement->MoveLeft();
    }
  }
  hpBar->Update();
  __super::Update();
  movement->Update();

  Vector3 hpBarPosition = position;
  hpBarPosition.y += size.y / 2;

  hpBar->SetPosition(hpBarPosition);
  hpBar->UpdateProgressBar(hp / hpMax);


}

void Enemy::Render()
{
  __super::Render();
  movement->Render();
  hpBar->Render();
}

void Enemy::Damaged(float damage)
{
  isHit = true;
  hitAnimTimer = 0.0;

  graphic->SetCurrentAnimation(L"hit");
  __super::Damaged(damage);
}

void Enemy::Healed(float heal)
{
}

void Enemy::Die()
{
  graphic->SetCurrentAnimation(L"die");
  isDead = true;
}
