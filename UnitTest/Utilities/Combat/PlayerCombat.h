#pragma once
#include "Utilities/Gun/Gun.h"
#include "GameObjects/Throwable/Throwable.h"

class PlayerCombat
{
public:
  PlayerCombat(class GameObject& agent);
  ~PlayerCombat();

  void Update(class Agent& agent);
  void Render();
  void GUI();

  void ThrowGrenade(Vector3 position, Vector3 axis, float strength); // ����ź ������s

  bool GetIsThrowing() { return isThrowing; } // ������ ��� ��� ������
  bool IsLeftGrenade() { return grenadeCount != 0; } // ����ź�� ���Ҵ���

  Gun* GetRifle() { return rifle; } // �ܺο��� �� ������Ʈ�� �����ϱ� ����
  Throwable* GetThrowable() { return throwable; }

protected:
  Gun* rifle; // �� ������Ʈ
  Throwable* throwable;

  UINT grenadeCount = 99;

  double throwProgress = 0.0; // ������ ��� ���ӽð� ������
  double throwSpeed = 0.5; // ������ ��� ���ӽð�
  bool isThrowing = false; // ������ ��� ��� ������
};