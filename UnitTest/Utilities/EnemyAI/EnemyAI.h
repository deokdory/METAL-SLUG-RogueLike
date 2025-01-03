#pragma once
class EnemyAI
{
public:
  EnemyAI(class Enemy* enemy);

  virtual void Update();
  virtual void GUI();

protected:
  class Enemy* enemy; // 조종할 객체
  class Character* target = nullptr;  // 최종 목표 오브젝트
  class GameObject* currDest = nullptr;  // 최종 목표로 이동하기 위한 현재의 목표 오브젝트

  Direction currDirection = Direction::NONE;

  Room* spawnedRoom = nullptr;

  double delay = 0.0;
};