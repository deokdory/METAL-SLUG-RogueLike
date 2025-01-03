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
      timerAfterDead += Time::Get()->WorldDelta(); // timer�� ���� �� �ӵ� �ݿ��� �ð� �߰�

      // ��� �ִϸ��̼� �Ϸ� �� 1�ʰ� �����ٸ� �׷����� ���̵�ƿ� ȿ�� ����
      if (timerAfterDead > 1.0) graphic->FadeOut(1.0f, ObjectGraphic::Type::ANIMATION);

      // ���� �� 2�ʰ� �����ٸ� �����Ǳ� ��ٸ�
      if (timerAfterDead > 2.0) isWaitingDelete = true;
    }
  }

  else if (isActived)// ��� �ִ� ����
  {
    if (hp <= 0.0f) Die(); // ü���� 0 ���϶�� ���

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

  __super::Update(); // �θ�Ŭ����(ĳ����) ������Ʈ

  if (isActived)
  {
    hpBar->Update(); // ü�� ���� �� ������Ʈ
    movement->Update(); // �̵� ������Ʈ ������Ʈ

    // ü�� ���� ���� ��ġ�� ����
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

    __super::Damaged(damage); // Character�� Damaged ȣ�� ( ü�¿� ����� �ݿ� )
  }
  hpBar->UpdateProgressBar(hp / maxHP); // ü�� ���� �� ������Ʈ
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

  // �⺻ ���� ���� = 576, 256
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