#pragma once
#include "Bullet/Bullet.h"



class Gun {
  enum class FireMode {
    SEMI_AUTO, BURST, AUTO
  };

public:
  Gun(float rpm, float vertRecoil, float horiRecoil, float bulletSpeed, float magazine, float magazineMax, float ammo, float ammoMax);
  ~Gun();

  void Fire(Vector3 position, Vector3 axis);
  void Reload();
  void SupplyAmmo(UINT ammo);

  bool mgzIsEmpty() { return magazine == 0; }

protected:
  void SetBullet(Bullet* bullet) { this->bullet = bullet; }
  void Recoil();

  float rpm; // 연사 속도
  float vertRecoil; // 수직 반동
  float horiRecoil; // 좌우 반동
  float bulletSpeed; // 탄속

  UINT magazine; // 현재 탄창 내 잔여 탄약
  UINT magazineMax; // 장탄

  float ammo; // 현재 보유 중인 탄약 수
  float ammoMax; // 보유 가능한 최대 탄약 수

  Bullet* bullet; // 탄 종류
};