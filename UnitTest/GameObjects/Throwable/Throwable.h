#pragma once

class Throwable : public GameObject
{
public:
  enum class Side { PLAYER, ENEMY };

  Throwable(GameObject* thrown, Side side, float damage, float range, std::wstring texturePath);
  ~Throwable();

  virtual void Update();
  virtual void Render();

  virtual bool hit(GameObject* object); // �浹���� �� �浹�� ������Ʈ�� ���ڷ� ����

  virtual Throwable* NewThrowable(Vector3 position, Vector3 axis, float strength); // �ڽ��� �������� ������ �� ��ġ�� ����, ������ ���⸦ �����Ͽ� ��ȯ

  static Throwable* InitGrenade(GameObject* object); // �⺻ ����ź ������

  class ThrowableMovement* GetMovement() { return movement; }

  GameObject* GetThrown() { return this->thrown; }

protected:
  // ������ ���� ���� ������
  Throwable(GameObject* thrown, Side side, float strength, float damage, float range, std::wstring texturePath, Vector3 position, Vector3 axis);

  void bomb();

  GameObject* thrown; // ���� ��ü
  Side side; // �Ʊ� | ����

  Vector3 axis = Values::ZeroVec3; // ���ư� ����

  double sinceThrown = 0.0;

  float damage; // �����
  float strength = 0; // ������ ����
  float range; // ���� ���� (���� ���� ����)

  bool isBombed = false; // �����°�
  bool isFirstHit = false;

  std::wstring texturePath = L""; // �ڽ��� �ؽ��� ���� ���

  class ThrowableMovement* movement = nullptr;
};