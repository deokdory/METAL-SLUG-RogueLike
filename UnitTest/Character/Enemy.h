#pragma once
#include "Character/Character.h"
#include "Game/UI/ProgressBar.h"

class Enemy : public Character
{
public:
  enum class Type
  { SOLDIER_KNIFE, SOLDIER_BZK };

  Enemy(Vector3 position, Vector3 size);
  Enemy(Vector3 position, Vector3 size, Room* spawnedRoom);
  virtual ~Enemy();

  virtual void Update();
  virtual void Render();

  virtual void Damaged(float damage) override;
  //virtual void Healed(float heal) override;

  virtual void Die();

  bool DetectPlayer();
  bool CanAttack(GameObject* object);
  bool CanChasing(GameObject* object);

  Movement* GetMovement() { return movement; }
  Room* GetSpawnedRoom() { return spawnedRoom; }
  Vector3 GetSpawnedPosition() { return spawnedPosition; }
  Type GetEnemyType() { return enemyType; }

  void Look(Direction direction);
  void Look(GameObject* object);

  void SetDelay(double delay) { this->delay = delay; }

protected:

  void init(Vector2 attackRange);
  virtual void initStates();

  Enemy::Type enemyType;

  Room* spawnedRoom = nullptr;
  Vector3 spawnedPosition = Values::ZeroVec3;

  UINT currState = 0;
  class EnemyState* currStateComp = nullptr;
  std::array<class EnemyState*, 8> stateComps;

  ProgressBar* hpBar = nullptr; // ü�� ���� ��

  Movement* movement; // �̵� ������Ʈ

  double timerAfterDead = 0.0; // �װ� �� �� �ð� üũ (3�� �� ����)

  BoundingBox* detectionArea = nullptr;
  BoundingBox* attackableArea = nullptr;
  BoundingBox* chasingArea = nullptr;

  //class EnemyAI* enemyAI = nullptr;

  double hpRegenTimer = 0.0; // hp 1�ʿ� �� ���� ���� �ϱ� ����
  //bool attacking = false; // Į�� �̰� �ִ���!
  bool isDead = false;

  double delay = 0.0; // ��� �ð�
};

// Į �����ϴ� �𵧱�
class ENM_SoldierKnife : public Enemy
{
public:
  ENM_SoldierKnife(Vector3 position, Vector3 size, Room* spawnedRoom);
  virtual ~ENM_SoldierKnife();

protected:
  virtual void initStates() override;
};

// ����ī ��� �𵧱�
class ENM_SoldierBZK : public Enemy
{
public:
  ENM_SoldierBZK(Vector3 position, Vector3 size, Room* spawnedRoom);
  virtual ~ENM_SoldierBZK();

protected:
  virtual void initStates() override;
};