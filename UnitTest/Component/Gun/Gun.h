#pragma once
#include "Bullet/Bullet.h"

class Gun {

  // 발사 모드
  enum class FireMode {
    SEMI_AUTO, BURST, AUTO
  };

public:
  virtual ~Gun();

  void Update(Vector3 position, Vector3 axis);
  void Render();
  void GUI();

  bool magazineIsEmpty() { return magazine == 0; } // 탄창이 비었는지
  bool magazineIsFull() { return magazine == magazineMax; } // 탄창이 꽉 찼는지

  void PullTrigger(); // 방아쇠 당기기
  void ReleaseTrigger(); // 방아쇠 놓기

  void ReloadBegin(); // 장전 시작
  void Reload(); // 장전 시간이 흐른 뒤 실제 장전

  void SupplyAmmo(UINT ammo); // 총알의 총 개수 보급 
                              // ( 총알의 총 개수는 특별한 총에서만 제한할 예정이라 아직 구현하지 않았다.)

  void SwitchMode(); // 발사 모드 전환 (연사 -> 단발 -> 점사)

  static Gun* InitHMG(GameObject* owner); // 헤비머신건을 생성 후 반환하는 정적 메소드
  
  bool GetIsReloading() { return isReloading; } // 장전 중인지

protected:
  Gun(GameObject* owner, float rpm, float vertRecoil, float horiRecoil, 
    float bulletSpeed, float bulletDamage, UINT magazine, UINT magazineMax, UINT ammo, UINT ammoMax);

  void fire(Vector3 position, Vector3 axis); // 총 발사
  void setBullet(Bullet* bullet); // 총알 설정
  void recoil(); // 반동 ( 아직 구현하지 않음 )

  float rpm; // 연사 속도
  float vertRecoil; // 수직 반동
  float horiRecoil; // 좌우 반동
  float bulletSpeed; // 탄속
  float spray = 10.f;

  double rpmProgress = 0.0;

  UINT magazine; // 현재 탄창 내 잔여 탄약
  UINT magazineMax; // 장탄

  UINT ammo; // 현재 보유 중인 탄약 수
  UINT ammoMax; // 보유 가능한 최대 탄약 수

  FireMode mode = FireMode::AUTO; // 발사 모드
  Bullet* bullet = nullptr; // 탄 종류
  Bullet* prevBullet = nullptr;

  std::vector<Bullet*> bullets;

  bool isReloading = false; // 장전 중인지
  float reloadSpeed = 1.0f; // 장전 속도
  float reloadProgress = 0.0f; // 장전 속도 계산용

  bool isTriggered = false; // 방아쇠 당겼는지
  bool isTriggeredPrev = false; // 그 전에 방아쇠를 당기고 있었는지

  UINT burstCount = 0; // 점사 회수 카운트
};