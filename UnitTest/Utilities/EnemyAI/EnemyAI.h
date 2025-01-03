#pragma once
class EnemyAI
{
public:
  EnemyAI(class Enemy* enemy);

  virtual void Update();
  virtual void GUI();

protected:
  class Enemy* enemy; // ������ ��ü
  class Character* target = nullptr;  // ���� ��ǥ ������Ʈ
  class GameObject* currDest = nullptr;  // ���� ��ǥ�� �̵��ϱ� ���� ������ ��ǥ ������Ʈ

  Direction currDirection = Direction::NONE;

  Room* spawnedRoom = nullptr;

  double delay = 0.0;
};