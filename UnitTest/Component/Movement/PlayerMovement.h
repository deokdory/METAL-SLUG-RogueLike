#pragma once
#include "Component/Movement/Movement.h"
#include "Character/Agent.h"

class PlayerMovement : public Movement
{
public:
  PlayerMovement(class GameObject* object);
  ~PlayerMovement();

  void JumpBegin();
  void Jumping();
  void JumpEnding();

private:
  double jumpStarted = 0; // 점프키를 처음 누른 시간
  bool isJumping = false; // 점프키를 누르고 있고 아직 점프시간이 남아있음
};