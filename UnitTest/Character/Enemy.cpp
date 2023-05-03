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
  SAFE_DELETE(hpBar);
  SAFE_DELETE(movement);
}

void Enemy::Update()
{
  if (isDead) // 죽은 상태
  {
    timerAfterDead += Time::Get()->WorldDelta(); // timer에 게임 내 속도 반영된 시간 추가

    // 죽은 후 2초가 지났다면 그래픽의 페이드아웃 효과 시작
    if (timerAfterDead > 2.0) graphic->FadeOut(1.0f, ObjectGraphic::Type::ANIMATION);

    // 죽은 후 3초가 지났다면 삭제되길 기다림
    if (timerAfterDead > 3.0) isWaitingDelete = true;
  }
  else // 살아 있는 상태
  {
    if (hp <= 0.0f) Die(); // 체력이 0 이하라면 사망

    if (isHit) // 피격 후 애니메이션 재생 중
    {
      if (hitAnimTimer > 0.22222222) // 피격 애니메이션 시간 초과 임시 구현
      {
        graphic->SetCurrentAnimation(L"idle"); 
        isHit = false;
      }
      else hitAnimTimer += Time::Get()->WorldDelta(); // 피격 애니메이션 시간 계산 임시 구현
    }
    else
    {
      //movement->MoveLeft();
    }
  }

  hpBar->Update(); // 체력 상태 바 업데이트
  __super::Update(); // 부모클래스(게임 오브젝트) 업데이트
  movement->Update(); // 이동 컴포넌트 업데이트

  // 체력 상태 바의 위치를 설정
  Vector3 hpBarPosition = position;
  hpBarPosition.y += size.y / 2;
  hpBar->SetPosition(hpBarPosition);
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

  graphic->SetCurrentAnimation(L"hit"); // 피격 애니메이션 호출
  __super::Damaged(damage); // Character의 Damaged 호출 ( 체력에 대미지 반영 )

  hpBar->UpdateProgressBar(hp / hpMax); // 체력 상태 바 업데이트
}

void Enemy::Healed(float heal)
{
}

void Enemy::Die()
{
  graphic->SetCurrentAnimation(L"die");
  isDead = true;
}
