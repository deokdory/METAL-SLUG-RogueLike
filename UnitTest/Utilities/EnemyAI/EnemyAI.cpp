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

  // AI에 필요한 Enemy의 정보 미리 가져오기
  Enemy::State state = enemy->GetState();
  Movement* movement = enemy->GetMovement();
  Room* currentRoom = enemy->GetCurrentRoom();
  Vector3 position = enemy->GetPosition();

  int currentFloor = -1;

  if (enemy->GetMovement()->GetLastStanded())
    currentFloor = enemy->GetMovement()->GetLastStanded()->GetFloor();

  // AI에 필요한 Player의 정보 미리 가져오기
  int currentPlayerFloor = GameManager::Get()->GetLastStandedTerrainFloor();

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
    
    // 플레이어를 인식한 상태
    if (target)
    {
      Vector3 targetPosition = target->GetPosition();

      // 추적 범위를 벗어난 플레이어가 방 밖에 있거나 자신이 방 밖에 있을 때 복귀
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
    
      // 플레이어보다 높은 발판에 있을 때
      if (currentPlayerFloor <= currentFloor)
      {
        movement->SetIsDirectingUp(false);
        movement->SetIsDirectingDown(false);

        currDest = nullptr;

        if (target->GetPosition().x > enemy->GetPosition().x)
          movement->MoveRight();
        else
          movement->MoveLeft();

        if (currentPlayerFloor < currentFloor && DXMath::GetDistance(targetPosition, position).x < 192.f)
        {
          movement->DropDown();
        }
      }

      // 플레이어보다 낮은 발판에 있을 때
      else
      {
        movement->SetIsDirectingUp(true);
        movement->SetIsDirectingDown(false);

        // 이미 오를 계단을 정했을 때 계단 방향으로 이동
        if (currDest)
        {
          if (currDirection == Direction::RIGHT)
            movement->MoveRight();
          else
            movement->MoveLeft();
        }

        // 오를 계단을 찾기
        else
        {
          auto& stairs = currentRoom->GetTerrains(Room::Layer::STAIRS);

          if (!stairs.empty())
          {
            for (auto stair : stairs)
            {
              if (stair->GetFloor() == currentFloor)
              {
                if (currDest == nullptr)
                  currDest = stair;
                else
                  // 플레이어와 더 가까운 계단을 목표로 설정
                  if (DXMath::GetDistance(currDest->GetPosition(), targetPosition).x >
                    DXMath::GetDistance(stair->GetPosition(), targetPosition).x)
                    currDest = stair;
              }
            }

            // 계단의 방향에 따라 이동방향을 결정
            if (currDest)
            {
              if (currDest->GetPosition().x > position.x)
                currDirection = Direction::RIGHT;
              else
                currDirection = Direction::LEFT;
            }
          }
        }
      }

      //if (targetPosition.y > position.y)
      //{
      //  movement->SetIsDirectingUp(true);
      //  movement->SetIsDirectingDown(false);
      //}
      //
      //else if (targetPosition.y < position.y)
      //{
      //  movement->SetIsDirectingUp(false);
      //  movement->SetIsDirectingDown(true);
      //}
    }
    else
    {
      if (enemy->DetectPlayer())
        target = GameManager::Get()->GetPlayer();
    }
    break;
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
