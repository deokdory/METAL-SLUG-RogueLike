#pragma once
#include "Game/GameObject.h"

class Bullet : public GameObject {
public:
  // 아군이 쏜 총알인지 적군이 쏜 총알인지
  enum class Side {
    PLAYER = 0, ENEMY
  };
  
  Bullet(GameObject* fired, Side side, float speed, float damage, std::wstring texturePath);
  ~Bullet();

  virtual void Update();
  virtual void Render();

  virtual void hit(GameObject* object); // 충돌했을 때 충돌한 오브젝트를 인자로 받음

  Bullet* NewBullet(Vector3 position, Vector3 axis); // 자신의 복제본을 생성한 뒤 위치와 방향을 설정하여 반환

  void SetExpired(bool expired) { this->expired = expired; }

protected:
  // 복제본 생성 위한 생성자
  Bullet(GameObject* fired, Side side, float speed, float damage, std::wstring texturePath, Vector3 position, Vector3 axis); 
  
  bool collisionCheck();

  GameObject* fired; // 쏜 캐릭터
  Side side;  // 아군 | 적군

  Vector3 axis = Values::ZeroVec3; // 날아갈 방향

  float damage; // 대미지
  float speed; // 탄속

  bool isHit = false; // 충돌했는가

  double flyingTime = 0.0;

  bool expired = false; // 총을 발사한 객체가 총알을 교체함 = 역할을 다 하고 사라져야 함

  std::wstring texturePath = L""; // 자신의 텍스쳐 파일 경로
};