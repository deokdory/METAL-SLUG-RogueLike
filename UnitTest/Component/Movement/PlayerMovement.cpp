#include "stdafx.h"
#include "PlayerMovement.h"

#include "Game/GameObject.h"

#include "Level/Level.h"

PlayerMovement::PlayerMovement(GameObject* object)
  : Movement(object)
{
}

PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::JumpBegin()
{
  auto currTime = Time::Get()->Running();
  // 땅에 있다면 점프
  if (isFalling == false) {
    jumpStarted = currTime;  // 점프키 누르는 길이 측정 시작
    isJumping = true;     // 점프키를 누르고 있음
    ySpeed = jumpPower;     // 점프 ( 최소 점프 단위 )
    isFalling = true;
  }
}

void PlayerMovement::Jumping()
{
  auto currTime = Time::Get()->Running();
  // 공중에 있고 아직 스페이스바를 누르고 있음
  if (isFalling) {
    // 스페이스바를 누르고 있는 시간이 0.2초 이내라면
    if (currTime - jumpStarted <= 0.2) {
      ySpeed = jumpPower;  // 점프 위력 유지
    }
  }
}

void PlayerMovement::JumpEnding()
{
  if (isJumping)
  {
    isJumping = false;
  }
}
