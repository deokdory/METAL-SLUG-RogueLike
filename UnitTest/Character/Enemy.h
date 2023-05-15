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

  ProgressBar* hpBar = nullptr; // 체력 상태 바

  Movement* movement; // 이동 컴포넌트

  double hitAnimTimer = 0.0; // 피격 애니메이션 시간 체크 용도
  bool isHit = false; // 피격되고 애니메이션 진행 중인지

  double timerAfterDead = 0.0; // 죽고 난 뒤 시간 체크 (3초 후 삭제)
};