#include "stdafx.h"
#include "Enemy.h"

#include "Agent.h"
//#include "Utilities/EnemyAI/EnemyAI.h"
#include "Utilities/EnemyState/EnemyState.h"

Enemy::Enemy(Vector3 position, Vector3 size)
  : Character(position, size)
{
}

Enemy::Enemy(Vector3 position, Vector3 size, Room* spawnedRoom)
  : Character(position, size), spawnedRoom(spawnedRoom)
{
}

Enemy::~Enemy()
{
  //SAFE_DELETE(enemyAI);

  SAFE_DELETE(chasingArea);
  SAFE_DELETE(attackableArea);
  SAFE_DELETE(detectionArea);

  SAFE_DELETE(hpBar);
  SAFE_DELETE(movement);
}

void Enemy::Update()
{
  if (isDead)
  {
    if (graphic->GetIsAnimationFinish())
    {
      timerAfterDead += Time::Get()->WorldDelta(); // timer에 게임 내 속도 반영된 시간 추가

      // 사망 애니메이션 완료 후 1초가 지났다면 그래픽의 페이드아웃 효과 시작
      if (timerAfterDead > 1.0) graphic->FadeOut(1.0f, ObjectGraphic::Type::ANIMATION);

      // 죽은 후 2초가 지났다면 삭제되길 기다림
      if (timerAfterDead > 2.0) isWaitingDelete = true;
    }
  }

  else if (isActived)// 살아 있는 상태
  {
    if (hp <= 0.0f) Die(); // 체력이 0 이하라면 사망

    detectionArea->Update(position + Vector3(0, size.y / 2, 0));
    attackableArea->Update(position + Vector3(0, size.y / 2, 0));
    chasingArea->Update(position + Vector3(0, size.y / 2, 0));

    if (delay <= 0.0)
    {
      EnemyState::State returnState = currStateComp->Update(*this);

      if (returnState != EnemyState::NONE)
      {
        currStateComp = stateComps[returnState];
        currStateComp->Enter(*this);
      }
    }
    else
      delay -= Time::Get()->WorldDelta();
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
  chasingArea->Render();
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
  if (isDead) return;

  if (currState != EnemyState::RETURN && currState != EnemyState::ATTACK)
  {
    currStateComp = stateComps[EnemyState::HIT];
    currStateComp->Enter(*this);

    __super::Damaged(damage); // Character의 Damaged 호출 ( 체력에 대미지 반영 )
  }
  hpBar->UpdateProgressBar(hp / maxHP); // 체력 상태 바 업데이트
}

void Enemy::Die()
{
  isDead = true;

  movement->Stop();
  graphic->SetCurrentAnimation(L"die");
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

bool Enemy::CanChasing(GameObject* object)
{
  return BoundingBox::AABB(chasingArea, object->GetCollision()->GetBase());
}

void Enemy::Look(Direction direction)
{
  switch (direction)
  {
  case Direction::LEFT:
    isFliped = true;
    break;
  case Direction::RIGHT:
    isFliped = false;
    break;
  default:
    break;
  }
}

void Enemy::Look(GameObject* object)
{
  if (object->GetPosition().x > position.x)
    isFliped = false;
  else
    isFliped = true;
}

void Enemy::init(Vector2 attackRange)
{
  movement = new Movement(this);
  movement->SetXSpeedMax(6.0f);

  hpBar = new ProgressBar(position, { 30, 5, 0 }, 0.0f, Values::Red, UI::FillType::LEFT_TO_RIGHT);

  detectionArea = new BoundingBox
  (position + Vector3(0, size.y / 2, 0), { 564, 256, 0 }, 0.0f, Color(0.5f, 1.0f, 0.5f, 0.1f));

  attackableArea = new BoundingBox
  (position + Vector3(0, size.y / 2, 0), { attackRange.x, attackRange.y, 0 }, 0.0f, Color(1.0f, 0.5f, 0.5f, 0.1f));

  chasingArea = new BoundingBox
  (position + Vector3(0, size.y / 2, 0), { 960, 512, 0 }, 0.0f, Color(1.0f, 1.0f, 1.0f, 0.1f));
  
  //enemyAI = new EnemyAI(this);
  spawnedPosition = this->position;

  // 기본 감지 범위 = 576, 256
}

void Enemy::initStates()
{
  stateComps[EnemyState::NONE] = &EnemyStates::es_none;
  stateComps[EnemyState::SPAWNED] = &EnemyStates::es_spawned;
  stateComps[EnemyState::SCREAM] = &EnemyStates::es_scream;
  stateComps[EnemyState::STANDBY] = &EnemyStates::es_standBy;
  stateComps[EnemyState::COMBAT] = &EnemyStates::es_combat;
  stateComps[EnemyState::ATTACK] = &EnemyStates::es_attack;
  stateComps[EnemyState::RETURN] = &EnemyStates::es_return;
  stateComps[EnemyState::HIT] = &EnemyStates::es_hit;

  currStateComp = stateComps[EnemyState::SPAWNED];
}