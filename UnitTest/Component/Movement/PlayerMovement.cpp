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
  // 가속도 관련
    if (isFalling) isSliding = false;
    __super::Update();
}

void PlayerMovement::UpdateAccel()
{
  accel = accelOrigin * Time::Get()->GetGlobalSpeed();
  if (isSliding) accel /= 8;
}

void PlayerMovement::Jump()
{
    ySpeedOrigin = jumpPower;     // 점프 ( 최소 점프 단위 )
    isFalling = true;
}

void PlayerMovement::Jumping()
{
  ySpeedOrigin = jumpPower;  // 점프 위력 유지
}
