#include "stdafx.h"
#include "PlayerMovement.h"

PlayerMovement::PlayerMovement(GameObject* object)
  : Movement(object)
{
  jumpPower = 6.f;
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
  __super::UpdateAccel();
  if (isSliding) accel /= 8;
}

void PlayerMovement::Jumping()
{
  ySpeedOrigin = jumpPower;  // 점프 위력 유지
}
