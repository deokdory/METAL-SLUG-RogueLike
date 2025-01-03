#pragma once
#include "GameObjects/Bullet/Bullet.h"

class Gun {

  // �߻� ���
  enum class FireMode {
    SEMI_AUTO, BURST, AUTO
  };

public:
  virtual ~Gun();

  void Update(Vector3 position, Vector3 axis);
  void Render();
  void GUI();

  bool magazineIsEmpty() { return magazine == 0; } // źâ�� �������
  bool magazineIsFull() { return magazine == magazineMax; } // źâ�� �� á����

  void PullTrigger(); // ��Ƽ� ����
  void ReleaseTrigger(); // ��Ƽ� ����

  void ReloadBegin(); // ���� ����
  void Reload(); // ���� �ð��� �帥 �� ���� ����

  void SupplyAmmo(UINT ammo); // �Ѿ��� �� ���� ���� 
                              // ( �Ѿ��� �� ������ Ư���� �ѿ����� ������ �����̶� ���� �������� �ʾҴ�.)

  void SwitchMode(); // �߻� ��� ��ȯ (���� -> �ܹ� -> ����)

  static Gun* InitHMG(GameObject* owner); // ���ӽŰ��� ���� �� ��ȯ�ϴ� ���� �޼ҵ�
  
  bool GetIsReloading() { return isReloading; } // ���� ������

protected:
  Gun(GameObject* owner, float rpm, float vertRecoil, float horiRecoil, 
    float bulletSpeed, float bulletDamage, UINT magazine, UINT magazineMax, UINT ammo, UINT ammoMax);

  void fire(Vector3 position, Vector3 axis); // �� �߻�
  void setBullet(Bullet* bullet); // �Ѿ� ����
  void recoil(); // �ݵ� ( ���� �������� ���� )

  float rpm; // ���� �ӵ�
  float vertRecoil; // ���� �ݵ�
  float horiRecoil; // �¿� �ݵ�
  float bulletSpeed; // ź��
  float spray = 10.f;

  double rpmProgress = 0.0;

  UINT magazine; // ���� źâ �� �ܿ� ź��
  UINT magazineMax; // ��ź

  UINT ammo; // ���� ���� ���� ź�� ��
  UINT ammoMax; // ���� ������ �ִ� ź�� ��

  FireMode mode = FireMode::AUTO; // �߻� ���
  Bullet* bullet = nullptr; // ź ����
  Bullet* prevBullet = nullptr;

  std::vector<Bullet*> bullets;

  bool isReloading = false; // ���� ������
  float reloadSpeed = 1.0f; // ���� �ӵ�
  float reloadProgress = 0.0f; // ���� �ӵ� ����

  bool isTriggered = false; // ��Ƽ� ������
  bool isTriggeredPrev = false; // �� ���� ��Ƽ踦 ���� �־�����

  UINT burstCount = 0; // ���� ȸ�� ī��Ʈ
};