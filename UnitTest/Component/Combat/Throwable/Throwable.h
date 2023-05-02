#pragma once
#include "Game/GameObject.h"

class Throwable : public GameObject
{
public:
  enum class Side { PLAYER, ENEMY };

  Throwable(GameObject* thrown, Side side, float gravityOffset, float damage, float range, std::wstring texturePath);
  ~Throwable();

  virtual void Update();
  virtual void Render();

  virtual bool hit(GameObject* object); // 충돌했을 때 충돌한 오브젝트를 인자로 받음

  virtual Throwable* NewThrowable(Vector3 position, Vector3 axis, float strength); // 자신의 복제본을 생성한 뒤 위치와 방향, 던지는 세기를 설정하여 반환

  static Throwable* InitGrenade(GameObject* object); // 기본 수류탄 생성자

  float GetGravityOffset() { return gravityOffset; }
  float GetFallingSpeedMax() { return fallingSpeedMax; }

protected:
  // 복제본 생성 위한 생성자
  Throwable(GameObject* thrown, Side side, float gravityOffset, float strength, float damage, float range, std::wstring texturePath, Vector3 position, Vector3 axis);

  bool collisionCheck();
  void bomb();

  GameObject* thrown; // 던진 객체
  Side side; // 아군 | 적군

  Vector3 axis = Values::ZeroVec3; // 날아갈 방향

  float xSpeed = 0.0f;
  float ySpeed = 0.0f;

  float fallingSpeedMax = -20.f; // 낙하 속도 제한

  double sinceThrown = 0.0;

  float gravityOffset; // 중력 보정값

  float damage; // 대미지
  float strength = 0; // 던지는 세기
  float range; // 폭발 범위 (차후 구현 예정)

  bool isBombed = false; // 터졌는가

  std::wstring texturePath = L""; // 자신의 텍스쳐 파일 경로
};