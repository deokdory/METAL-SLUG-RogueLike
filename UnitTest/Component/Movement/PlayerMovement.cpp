#include "stdafx.h"
#include "PlayerMovement.h"

#include "Game/GameObject.h"

//#include "Level/Level.h"

PlayerMovement::PlayerMovement(GameObject* object)
  : Movement(object)
{
}

PlayerMovement::~PlayerMovement()
{

}

void PlayerMovement::Update()
{
  float globalSpeed = Time::Get()->GetGlobalSpeed();
  // 낙하 
  {
    auto globalGravity = GameManager::Get()->GetGlobalGravity();
    if (isFalling)
    {
      isSliding = false;
      if (ySpeed > fallingSpeedMax) ySpeed -= ((globalGravity + gravityOffset) * globalSpeed);
    }
  }
  // 가속도 관련
  {
    accel = accelOrigin * globalSpeed;
    if (isSliding) accel /= 8;
  }

  speedBox->Update(xSpeed, ySpeed);
  collisionCheck();

  Vector3 move = { xSpeed, ySpeed, 0 };
  object->Move(move);
}

void PlayerMovement::Jump()
{
    ySpeed = jumpPower;     // 점프 ( 최소 점프 단위 )
    isFalling = true;
}

void PlayerMovement::Jumping()
{
  ySpeed = jumpPower;  // 점프 위력 유지
}
