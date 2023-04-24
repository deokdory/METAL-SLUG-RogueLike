#pragma once
#include "Bullet/Bullet.h"

class Gun {
  enum class FireMode {
    SEMI_AUTO, BURST, AUTO
  };

public:

  virtual ~Gun();

  void Update(Vector3 position, Vector3 axis);
  void Render();
  void GUI();

  bool magazineIsEmpty() { return magazine == 0; }

  void PullTrigger();
  void ReleaseTrigger();

  void Reload();
  void SupplyAmmo(UINT ammo);

  void SwitchMode();

  static Gun* InitHMG(GameObject* owner);

protected:
  Gun(GameObject* owner, float rpm, float vertRecoil, float horiRecoil, 
    float bulletSpeed, float bulletDamage, UINT magazine, UINT magazineMax, UINT ammo, UINT ammoMax);

  void Fire(Vector3 position, Vector3 axis);
  void SetBullet(Bullet* bullet) { this->bullet = bullet; }
  void Recoil();

  float rpm; // 연사 속도
  float vertRecoil; // 수직 반동
  float horiRecoil; // 좌우 반동
  float bulletSpeed; // 탄속

  UINT magazine; // 현재 탄창 내 잔여 탄약
  UINT magazineMax; // 장탄

  UINT ammo; // 현재 보유 중인 탄약 수
  UINT ammoMax; // 보유 가능한 최대 탄약 수

  FireMode mode = FireMode::AUTO;
  Bullet* bullet = nullptr; // 탄 종류

  double lastFire = -1.0;

  bool isTriggered = false;
  bool isTriggeredPrev = false;

  //bool isBursting = false;

  UINT burstCount = 0;
};