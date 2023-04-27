#pragma once
#include "Component/Gun/Gun.h"

class PlayerCombat
{
public:
  PlayerCombat(class GameObject& agent);
  ~PlayerCombat();

  void Update(class Agent& agent);
  void Render();
  void GUI();

  void ThrowGrenade(); // 수류탄 던지기
  bool GetIsThrowing() { return isThrowing; } // 던지기 모션 재생 중인지
  bool IsLeftGrenade() { return grenadeCount != 0; } // 수류탄이 남았는지

  Gun* GetRifle() { return rifle; } // 외부에서 총 컴포넌트에 접근하기 위함

protected:
  Gun* rifle; // 총 컴포넌트
  
  UINT grenadeCount = 3; // 수류탄 개수

  double throwProgress = 0.0; // 던지기 모션 지속시간 측정용
  double throwSpeed = 0.5; // 던지기 모션 지속시간
  bool isThrowing = false; // 던지기 모션 재생 중인지
};