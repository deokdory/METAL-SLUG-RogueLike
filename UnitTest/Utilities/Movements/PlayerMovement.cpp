#include "stdafx.h"
#include "PlayerMovement.h"

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

void PlayerMovement::Jumping()
{
  ySpeedOrigin = jumpPower;  // 점프 위력 유지
}
