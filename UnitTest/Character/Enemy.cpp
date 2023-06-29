#include "stdafx.h"
#include "Enemy.h"

#include "Agent.h"
#include "Utilities/EnemyAI/EnemyAI.h"

Enemy::Enemy(Vector3 position, Vector3 size)
  : Character(position, size)
{
  movement = new Movement(this);
  movement->SetXSpeedMax(4.0f);

  hpBar = new ProgressBar(position, { 30, 5, 0 }, 0.0f, Values::Red ,UI::FillType::LEFT_TO_RIGHT);

  detectionArea = new BoundingBox
  (position + Vector3(0, size.y / 2, 0), { 564, 256, 0 }, 0.0f, Color(0.5f, 1.0f, 0.5f, 0.1f));
  
  attackableArea = new BoundingBox
  (position + Vector3(0, size.y / 2, 0), { 192, 128, 0 }, 0.0f, Color(1.0f, 0.5f, 0.5f, 0.1f));

  enemyAI = new EnemyAI(this);

  // 기본 감지 범위 = 576, 256
}

Enemy::~Enemy()
{
  SAFE_DELETE(enemyAI);
  SAFE_DELETE(attackableArea);
  SAFE_DELETE(detectionArea);

  SAFE_DELETE(hpBar);
  SAFE_DELETE(movement);
}

void Enemy::Update()
{

  if (currState == State::DEAD)
  {
    timerAfterDead += Time::Get()->WorldDelta(); // timer에 게임 내 속도 반영된 시간 추가

    // 죽은 후 2초가 지났다면 그래픽의 페이드아웃 효과 시작
    if (timerAfterDead > 2.0) graphic->FadeOut(1.0f, ObjectGraphic::Type::ANIMATION);

    // 죽은 후 3초가 지났다면 삭제되길 기다림
    if (timerAfterDead > 3.0) isWaitingDelete = true;
  }

  else if (isActived)// 살아 있는 상태
  {
    if (hp <= 0.0f) Die(); // 체력이 0 이하라면 사망

    detectionArea->Update(position + Vector3(0, size.y / 2, 0));
    attackableArea->Update(position + Vector3(0, size.y / 2, 0));

    enemyAI->Update();
    
    switch (currState)
    {
    //case Enemy::State::READY:
    //  if (findTarget() || GameManager::Get()->GetPlayerCurrentRoom() == currentRoom)
    //  {
    //    target = (Character*)GameManager::Get()->GetPlayer();
    //    
    //  }
    //  break;
    case Enemy::State::READY:
      if (movement->GetIsFalling())
      {
        // State를 Falling으로 바꿈
      }
      
      if (std::abs(movement->GetXSpeedOrigin() > 1))
      {
        // 달리는 애니메이션 재생
      }

      // 달리는 중도 아니고 떨어지는 상태도 아님 = 가만히 서 있는 상태
      else
      {
        graphic->SetCurrentAnimation(L"idle");
      }

      

      break;
    //case Enemy::State::ATTACK:
    //  break;
    //case Enemy::State::RUN:
    //  break;
    case Enemy::State::HIT:
      movement->SlowDown();

      if (graphic->IsAnimationFinish(ObjectGraphic::Slot::NORMAL))
        currState = prevState;
      break;
    default:
      break;
    }
  }

  __super::Update(); // 부모클래스(캐릭터) 업데이트

  if (isActived)
  {
    hpBar->Update(); // 체력 상태 바 업데이트
    movement->Update(); // 이동 컴포넌트 업데이트

    // 체력 상태 바의 위치를 설정
    Vector3 hpBarPosition = position;
    hpBarPosition.y += size.y;
    hpBar->SetPosition(hpBarPosition);
  }
}

void Enemy::Render()
{
  detectionArea->Render();
  attackableArea->Render();

  if (isActived)
  {
    __super::Render();
    movement->Render();
    hpBar->Render();
  }
}

void Enemy::Damaged(float damage)
{

  prevState = currState;
  currState = State::HIT;

  graphic->SetCurrentAnimation(L"hit"); // 피격 애니메이션 호출
  __super::Damaged(damage); // Character의 Damaged 호출 ( 체력에 대미지 반영 )

  hpBar->UpdateProgressBar(hp / hpMax); // 체력 상태 바 업데이트
}

//void Enemy::Healed(float heal)
//{
//}

void Enemy::Die()
{
  isDead = true;

  movement->Stop();
  graphic->SetCurrentAnimation(L"die");
  currState = State::DEAD;
  timerAfterDead = 0.0;
}

bool Enemy::DetectPlayer()
{
  return BoundingBox::AABB(detectionArea, 
    GameManager::Get()->GetPlayer()->GetCollision()->GetBase());
}

bool Enemy::CanAttack(GameObject* object)
{
  return BoundingBox::AABB(attackableArea, object->GetCollision()->GetBase());
}

void Enemy::Scream()
{
  currState = State::SCREAM;
}

void Enemy::Attack(GameObject* target)
{
  movement->SlowDown();
}
