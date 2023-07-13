#pragma once
#include "Character/Character.h"
#include "Game/UI/ProgressBar.h"

class Enemy : public Character
{
public:
  enum class State
  { SPAWNED, SCREAM, STANDBY, DETECT, ATTACK, RETURN, HIT, DEAD };

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

  void SetState(State state) { this->state = state; }
  State GetState() { return state; }

  Movement* GetMovement() { return movement; }

  Room* GetSpawnedRoom() { return spawnedRoom; }
  
  void Look(Direction direction);
  void Look(GameObject* object);

  void Scream();
  void Return();
  void StandBy();

  void Attack(GameObject* target);

  void HPRecover();
protected:
  void init();

  Room* spawnedRoom = nullptr;
  Vector3 spawnedPosition = Values::ZeroVec3;

  State state = State::SPAWNED;

  ProgressBar* hpBar = nullptr; // 체력 상태 바

  Movement* movement; // 이동 컴포넌트

  double timerAfterDead = 0.0; // 죽고 난 뒤 시간 체크 (3초 후 삭제)

  BoundingBox* detectionArea = nullptr;
  BoundingBox* attackableArea = nullptr;
  BoundingBox* chasingArea = nullptr;

  class EnemyAI* enemyAI = nullptr;

  double hpRegenTimer = 0.0; // hp 1초에 한 번씩 차게 하기 위해
  bool attacking = false; // 칼을 뽑고 있는지!

};

// 칼 공격하는 모덴군
class ENM_SoldierKnife : public Enemy
{
  ENM_SoldierKnife(Vector3 position, Vector3 size, Room* spawnedRoom);
  ~ENM_SoldierKnife();

  void Update() override;

};

// 바주카 쏘는 모덴군
class ENM_SoldierBZK : public Enemy
{

};