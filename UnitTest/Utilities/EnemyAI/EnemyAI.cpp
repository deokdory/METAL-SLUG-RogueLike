#include "stdafx.h"
#include "EnemyAI.h"

#include "Character/Enemy.h"
#include "Character/Agent.h"

EnemyAI::EnemyAI(Enemy* enemy)
  : enemy(enemy)
{
  spawnedRoom = enemy->GetSpawnedRoom();
}

void EnemyAI::Update()
{
  // AI�� �ʿ��� Enemy�� ���� �̸� ��������
  Enemy::State state = enemy->GetState();
  Movement* movement = enemy->GetMovement();
  Room* currentRoom = enemy->GetCurrentRoom();
  Vector3 position = enemy->GetPosition();

  int currentFloor = -1;

  if (enemy->GetMovement()->GetLastStanded())
    currentFloor = enemy->GetMovement()->GetLastStanded()->GetFloor();

  // AI�� �ʿ��� Player�� ���� �̸� ��������
  int currentPlayerFloor = GameManager::Get()->GetPlayerLastStandedFloor();

  //if (delay > 0.0)
  //{
  //  delay -= Time::Get()->WorldDelta();
  //  return;
  //}

  switch (state)
  {
  case Enemy::State::SPAWNED:
    if (enemy->DetectPlayer())
    {
      target = GameManager::Get()->GetPlayer();
      enemy->Look(target);
      enemy->Scream();
    }
    break;
  case Enemy::State::STANDBY:
    if (target)
    {
      enemy->SetState(Enemy::State::DETECT);
      break;
    }

    if (enemy->DetectPlayer())
    {
      target = GameManager::Get()->GetPlayer();
      enemy->Look(target);
      delay = 0.5;
      enemy->SetState(Enemy::State::DETECT);
    }
    break;
  case Enemy::State::DETECT:
    if (delay > 0.0)
    {
      delay -= Time::Get()->WorldDelta();
      break;
    }
    
    // �÷��̾ �ν��� ����
    if (target)
    {
      Vector3 targetPosition = target->GetPosition();

      // ���� ������ ��� �÷��̾ �� �ۿ� �ְų� �ڽ��� �� �ۿ� ���� �� ����
      if ((GameManager::Get()->GetPlayerCurrentRoom() != spawnedRoom 
        && !enemy->CanChasing(target)) || (currentRoom != spawnedRoom))
      {
        target = nullptr;
        enemy->Return();

        break;
      }

      if (enemy->CanAttack(target))
      {
        enemy->Look(target);
        enemy->Attack(target);
        break;
      }
    
      
  case Enemy::State::ATTACK:
    delay = 2.0;
    break;
  case Enemy::State::RETURN:
    break;
  case Enemy::State::HIT:
    break;
  case Enemy::State::DEAD:
    break;
  default:
    break;
  }
}

void EnemyAI::GUI()
{
}
