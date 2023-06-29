#include "stdafx.h"
#include "EnemyAI.h"

#include "Character/Enemy.h"
#include "Character/Agent.h"

EnemyAI::EnemyAI(Enemy* enemy)
  : enemy(enemy)
{
  
}

void EnemyAI::Update()
{
  Enemy::State state = enemy->GetState();
  auto movement = enemy->GetMovement();

  switch (state)
  {
  case Enemy::State::SPAWNED:
    if (enemy->DetectPlayer())
    {
      target = GameManager::Get()->GetPlayer();
      enemy->Scream();

      enemy->SetState(Enemy::State::READY);
    }
    break;
  case Enemy::State::READY:
  case Enemy::State::MOVE:
    if (target)
    {
      if (enemy->CanAttack(target))
      {
        enemy->Attack(target);
        break;
      }
    
      // аб©Л
      if (target->GetPosition().x > enemy->GetPosition().x)
        movement->MoveRight();
      else
        movement->MoveLeft();

      if (target->GetPosition().y > enemy->GetPosition().y)
      {
        movement->SetIsDirectingUp(true);
        movement->SetIsDirectingDown(false);
      }

      else if (target->GetPosition().y < enemy->GetPosition().y)
      {
        movement->SetIsDirectingUp(false);
        movement->SetIsDirectingDown(true);
      }
    }
    break;
  case Enemy::State::ATTACK:
    break;
  case Enemy::State::RUNAWAY:
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
