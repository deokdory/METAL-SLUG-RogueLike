#pragma once
#include "Game/GameObject.h"

class Throwable : public GameObject
{
public:
  enum class Side { PLAYER, ENEMY };

  Throwable(GameObject* thrown, Side side, float damage, float range, std::wstring texturePath);
  ~Throwable();

  virtual void Update();
  virtual void Render();

  virtual bool hit(GameObject* object); // 충돌했을 때 충돌한 오브젝트를 인자로 받음

  virtual Throwable* NewThrowable(Vector3 position, Vector3 axis, float strength); // 자신의 복제본을 생성한 뒤 위치와 방향, 던지는 세기를 설정하여 반환

  static Throwable* InitGrenade(GameObject* object); // 기본 수류탄 생성자

  class ThrowableMovement* GetMovement() { return movement; }

protected:
  // 복제본 생성 위한 생성자
  Throwable(GameObject* thrown, Side side, float strength, float damage, float range, std::wstring texturePath, Vector3 position, Vector3 axis);

  void bomb();

  GameObject* thrown; // 던진 객체
  Side side; // 아군 | 적군

  Vector3 axis = Values::ZeroVec3; // 날아갈 방향

  double sinceThrown = 0.0;

  float damage; // 대미지
  float strength = 0; // 던지는 세기
  float range; // 폭발 범위 (차후 구현 예정)

  bool isBombed = false; // 터졌는가
  bool isFirstHit = false;

  std::wstring texturePath = L""; // 자신의 텍스쳐 파일 경로

  class ThrowableMovement* movement = nullptr;
};