#include "stdafx.h"
#include "IPlayerMovement.h"

IPlayerMovement::IPlayerMovement(GameObject* object) : IMovement(object) {}

void IPlayerMovement::jumpBegin() {
  auto currTime = Time::Get()->Running();
    // 땅에 있다면 점프
    if (isFalling == false) {
      jumpedTime = currTime;  // 점프키 누르는 길이 측정 시작
      isJumping = true;     // 점프키를 누르고 있음
      ySpeed = jumpPower;     // 점프 ( 최소 점프 단위 )
      isFalling = true;

      //auto move = Vector3(xSpeed, ySpeed, 0) * delta;
      //object->move(move);
    }
  }

void IPlayerMovement::jumping() {
  auto currTime = Time::Get()->Running();
  // 공중에 있고 아직 스페이스바를 누르고 있음
  if (isFalling) {
    // 스페이스바를 누르고 있는 시간이 0.2초 이내라면
    if (currTime - jumpedTime <= 0.2) {
      ySpeed = jumpPower;  // 점프 위력 유지
    }
  }
}

void IPlayerMovement::jumpEnd() { isJumping = false; }

void IPlayerMovement::update() {

  auto& status = object->GetState();

  if (Keyboard::Get()->Press('A') && !Keyboard::Get()->Press('D')) {
    moveLeft();
  } else if (Keyboard::Get()->Press('D') && !Keyboard::Get()->Press('A')) {
    moveRight();
  } else {
    SlowDown();
  }

  if (Keyboard::Get()->Down(VK_SPACE))
    jumpBegin();
  else if (Keyboard::Get()->Press(VK_SPACE))
    jumping();
  else
    jumpEnd();

  __super::update();
}
    




