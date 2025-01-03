#include "stdafx.h"
#include "EnemyState.h"

#include "Character/Enemy.h"
#include "Character/Agent.h"

void EnemyState::movementBasic(Enemy& enemy)
{
  auto* movement = enemy.GetMovement();
  auto* graphic = enemy.GetGraphic();

  std::wstring currentAnimationName = graphic->GetCurrentAnimationName();

  if (movement->GetIsFalling())
  {
    if (currentAnimationName != L"fall" && currentAnimationName != L"fallReverse")
      graphic->SetCurrentAnimation(L"fall");
    else if (currentAnimationName == L"fall" && graphic->GetIsAnimationFinish())
      graphic->SetCurrentAnimation(L"fallReverse");
  }
  else
  {
    // ���������� �޸��� ��
    if (movement->GetXSpeedOrigin() > 1.0f)
    {
      enemy.SetIsFliped(false);
      graphic->SetCurrentAnimation(L"run");
    }
    // �������� �޸��� ��
    else if (movement->GetXSpeedOrigin() < -1.0f)
    {
      enemy.SetIsFliped(true);
      graphic->SetCurrentAnimation(L"run");
    }
    // ������ �� �ִ� ����
    else
    {
      graphic->SetCurrentAnimation(L"idle");
    }
  }
}

EnemyState::State ES_Spawned::Update(Enemy& enemy)
{
  if (enemy.DetectPlayer())
    return State::SCREAM;

  return State::NONE;
}

void ES_Spawned::Enter(Enemy& enemy)
{
  enemy.GetGraphic()->SetCurrentAnimation(L"idle");
}

EnemyState::State ES_Scream::Update(Enemy& enemy)
{
  if (enemy.GetGraphic()->GetIsAnimationFinish())
    return State::COMBAT;

  return State::NONE;
}

void ES_Scream::Enter(Enemy& enemy)
{
  enemy.Look((GameObject*)GameManager::Get()->GetPlayer());
  enemy.GetGraphic()->SetCurrentAnimation(L"scream");
}

EnemyState::State ES_StandBy::Update(Enemy& enemy)
{
  if (enemy.DetectPlayer())
    return State::COMBAT;

  enemy.GetMovement()->SlowDown();

  return State::NONE;
}

void ES_StandBy::Enter(Enemy& enemy)
{
  // �޸��� �ӵ� �ʱ�ȭ
  enemy.Look(GameManager::Get()->GetPlayer());
  enemy.GetGraphic()->SetCurrentAnimation(L"idle");
  enemy.GetMovement()->SetXSpeedMax(5.0f);
}

EnemyState::State ES_Combat::Update(Enemy& enemy)
{
  auto* player = GameManager::Get()->GetPlayer();

  // ���� ������ ��� �÷��̾ �� �ۿ� �ְų� �ڽ��� �� �ۿ� ���� �� ����
  if (((GameManager::Get()->GetPlayerCurrentRoom() != enemy.GetSpawnedRoom()
    && !enemy.CanChasing((GameObject*)GameManager::Get()->GetPlayer())) ||
    enemy.GetCurrentRoom() != enemy.GetSpawnedRoom()))
  {
    return State::RETURN;
  }

  if (enemy.CanAttack((GameObject*)player))
    return State::ATTACK;

  movementBasic(enemy);

  return State::NONE;
}

void ES_Combat::Enter(Enemy& enemy)
{
  enemy.Look(GameManager::Get()->GetPlayer());
  enemy.GetMovement()->SetXSpeedMax(5.0f);
  enemy.GetGraphic()->SetCurrentAnimation(L"idle");
}

EnemyState::State ES_CombatKnife::Update(Enemy& enemy)
{
  // ���� ���� ���� ���� �˻� �� ��ȯ
  State superState = ES_Combat::Update(enemy);
  if (superState != State::NONE)
    return superState;

  auto* player = GameManager::Get()->GetPlayer();

  auto* movement = enemy.GetMovement();
  int currentPlayerFloor = GameManager::Get()->GetPlayerLastStandedFloor();

  Vector3 playerPosition = player->GetPosition();
  Vector3 enemyPosition = enemy.GetPosition();

  int currentFloor = -1;
  if (movement->GetLastStanded())
    currentFloor = movement->GetLastStanded()->GetFloor();

  // �� ĳ���Ͱ� �÷��̾�� ���� ���ǿ� ���� ��
  if (currentPlayerFloor <= currentFloor)
  {
    if (playerPosition.y > enemyPosition.y)
      movement->SetIsDirectingUp(true);
    else
      movement->SetIsDirectingUp(false);

    movement->SetIsDirectingDown(false);

    if (playerPosition.x > enemyPosition.x)
      movement->MoveRight();
    else
      movement->MoveLeft();

    if (currentPlayerFloor < currentFloor &&
      DXMath::GetDistance(playerPosition, enemyPosition).x < 258.f)
    {
      movement->DropDown();
    }
  }

  // ĳ���Ͱ� �÷��̾�� ���� ���ǿ� ���� ��
  else
  {
    movement->SetIsDirectingDown(false);

    // ���� ����� ã��
    auto& stairs = enemy.GetCurrentRoom()->GetTerrains(Room::Layer::STAIRS); // ��� ���� ���޹ޱ�
    Terrain* stairTemp = nullptr;
    Stair* stair = nullptr;

    if (movement->GetLastStanded()->GetTerrainType() == Terrain::Type::STAIR)
    {
      stair = dynamic_cast<Stair*>(movement->GetLastStanded());
      switch (stair->GetStairType())
      {
      case Stair::Type::NORMAL_UP:
      case Stair::Type::LONG_UP:
        movement->SetIsDirectingUp(true);
        movement->MoveRight();
        return EnemyState::NONE;
        break;

      case Stair::Type::NORMAL_DOWN:
      case Stair::Type::LONG_DOWN:
        movement->SetIsDirectingUp(true);
        movement->MoveLeft();
        return EnemyState::NONE;
        break;
      }
    }

    if (!stairs.empty())
    {
      for (auto s : stairs)
      {
        if (s->GetFloor() == currentFloor)
        {
          if (stair == nullptr)
            stair = dynamic_cast<Stair*>(s);
          else
          {
            Stair* currStair = dynamic_cast<Stair*>(s);
            // �÷��̾�� �� ����� ����� ��ǥ�� ����
            if (DXMath::GetDistance(stair->GetEntrance(), playerPosition).x + DXMath::GetDistance(stair->GetEntrance(), enemyPosition).x >
              DXMath::GetDistance(currStair->GetEntrance(), playerPosition).x + DXMath::GetDistance(currStair->GetEntrance(), enemyPosition).x)
              stair = currStair;

          }
        }
      }

      if (stair)
      {
        Vector3 stairPosition = stair->GetPosition();

        // �� ĳ���Ͱ� ��� ������ �ʸӿ� ��ġ�ߴ��� �˻� �� �̵�
        switch (stair->GetStairType())
        {
        case Stair::Type::NORMAL_UP:
        case Stair::Type::LONG_UP:
        {
          if (enemyPosition.x > stairPosition.x - (stair->GetSize().x / 4))
          {
            movement->SetIsDirectingUp(false);
            movement->MoveLeft();
          }
          else
          {
            movement->SetIsDirectingUp(true);
            movement->MoveRight();
          }
        }
        break;
        case Stair::Type::NORMAL_DOWN:
        case Stair::Type::LONG_DOWN:
        {
          if (enemyPosition.x < stairPosition.x + (stair->GetSize().x / 4))
          {
            movement->SetIsDirectingUp(false);
            movement->MoveRight();
          }
          else
          {
            movement->SetIsDirectingUp(true);
            movement->MoveLeft();
          }
        }
        break;
        default:
          break;
        }
      }
    }
  }
  return State::NONE;
}

void ES_CombatKnife::Enter(Enemy& enemy)
{
  ES_Combat::Enter(enemy);
}

EnemyState::State ES_CombatBZK::Update(Enemy& enemy)
{
  // ���� ���� ���� ���� �˻� �� ��ȯ
  State superState = ES_Combat::Update(enemy);
  if (superState != State::NONE)
    return superState;
  return State::NONE;
}

void ES_CombatBZK::Enter(Enemy& enemy)
{
  ES_Combat::Enter(enemy);
}

EnemyState::State ES_Attack::Update(Enemy& enemy)
{
  enemy.GetMovement()->SlowDown();
  return State::NONE;
}

void ES_Attack::Enter(Enemy& enemy)
{
}

EnemyState::State ES_AttackKnife::Update(Enemy& enemy)
{

  // ���� ���� ���� ���� �˻� �� ��ȯ
  State superState = ES_Attack::Update(enemy);
  if (superState != State::NONE)
    return superState;

  ObjectGraphic* graphic = enemy.GetGraphic();
  std::wstring currentAnimationName = graphic->GetCurrentAnimationName();

  if (graphic->GetIsAnimationFinish())
    if (currentAnimationName == L"knife1" || currentAnimationName == L"knife2")
      graphic->SetCurrentAnimation(L"knifeReverse");
    else
    {
      enemy.SetDelay(1.0);
      return State::COMBAT;
    }

  return State::NONE;
}

void ES_AttackKnife::Enter(Enemy& enemy)
{
  ES_Attack::Enter(enemy);

  enemy.Look(GameManager::Get()->GetPlayer());
  enemy.GetGraphic()->SetCurrentAnimation(L"knife1");
}

EnemyState::State ES_AttackBZK::Update(Enemy& enemy)
{
  // ���� ���� ���� ���� �˻� �� ��ȯ
  State superState = ES_Attack::Update(enemy);
  if (superState != State::NONE)
    return superState;
  return State::NONE;
}

void ES_AttackBZK::Enter(Enemy& enemy)
{
  ES_Attack::Enter(enemy);
}

EnemyState::State ES_Return::Update(Enemy& enemy)
{
  auto* movement = enemy.GetMovement();

  auto* currentRoom = enemy.GetCurrentRoom();
  auto* spawnedRoom = enemy.GetSpawnedRoom();

  Vector3 spawnedPosition = enemy.GetSpawnedPosition();
  Vector3 position = enemy.GetPosition();

  if (currentRoom)
  {
    if (currentRoom->GetRoomType() == Room::Type::PASSAGE)
    {
      movement->SetIsDirectingUp();
      movement->SetIsDirectingDown();
    }

    movementBasic(enemy);

    if (spawnedPosition.x + movement->GetXSpeed() < position.x)
      movement->MoveLeft();
    else if (spawnedPosition.x - movement->GetXSpeed() > position.x)
      movement->MoveRight();
    else
      return EnemyState::STANDBY;
  }

  

  movementBasic(enemy);

  return State::NONE;
}

void ES_Return::Enter(Enemy& enemy)
{
  enemy.GetMovement()->SetXSpeedMax(6.0f);
}

EnemyState::State ES_Hit::Update(Enemy& enemy)
{
  if (enemy.GetGraphic()->GetIsAnimationFinish())
    return State::COMBAT;

  enemy.GetMovement()->SlowDown();

  return State::NONE;
}

void ES_Hit::Enter(Enemy& enemy)
{
  enemy.GetGraphic()->SetCurrentAnimation(L"hit");
}

EnemyState EnemyStates::es_none;
ES_Spawned EnemyStates::es_spawned;
ES_Scream EnemyStates::es_scream;
ES_StandBy EnemyStates::es_standBy;
ES_Combat EnemyStates::es_combat;
ES_CombatKnife EnemyStates::es_combatKnife;
ES_CombatBZK EnemyStates::es_combatBZK;
ES_Attack EnemyStates::es_attack;
ES_AttackKnife EnemyStates::es_attackKnife;
ES_AttackBZK EnemyStates::es_attackBZK;
ES_Return EnemyStates::es_return;
ES_Hit EnemyStates::es_hit;
