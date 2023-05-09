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

void PlayerMovement::collisionCheck()
{
  isFalling = true;

  auto& terrains = GameManager::Get()->GetCurrentLevel()->GetTerrains();

  auto* bottom = object->GetCollision()->GetBottom();
  auto* top = object->GetCollision()->GetTop();
  auto* base = object->GetCollision()->GetBase();

  auto* bottomSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::BOTTOM);
  auto* topSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::TOP);
  auto* rightSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::RIGHT);
  auto* leftSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::LEFT);

  auto objPos = object->GetPosition();
  auto objSize = object->GetSize();

  Vector3 terrPos;
  Vector3 terrSize;

  BoundingBox* terrTop, * terrBottom, * terrBase;

  BoundingBox* nearestY = nullptr;
  BoundingBox* nearestX = nullptr;

  for (auto terr : terrains) {
    terrTop = terr->GetCollision()->GetTop();
    terrBase = terr->GetCollision()->GetBase();
    terrBottom = terr->GetCollision()->GetBottom();

    terrPos = terr->GetPosition();
    terrSize = terr->GetSize();

    if (ySpeed < 0)
    {
      if (BoundingBox::AABB(bottomSpeedBox, terrTop))
      {
        isFalling = false;
        if (nearestY == nullptr || terrTop->GetRect()->LT.y > nearestY->GetRect()->LT.y)
        {
          nearestY = terrTop;

          float depth = std::abs(bottomSpeedBox->GetRect()->RB.y - nearestY->GetRect()->LT.y);
          ySpeed += depth;
        }
      }
    }
    if (ySpeed > 0) {
      if (BoundingBox::AABB(topSpeedBox, terrBottom))
      {
        if (nearestY == nullptr || terrBottom->GetRect()->LB.y < nearestY->GetRect()->LB.y)
        {
          nearestY = terrBottom;

          float depth = std::abs(topSpeedBox->GetRect()->LT.y - nearestY->GetRect()->LB.y);
          ySpeed -= depth;

          isJumping = false;
          ySpeedOrigin = 0;
        }
      }
    }

    if (xSpeed > 0)
    {
      if (BoundingBox::AABB(rightSpeedBox, terrBase) == true)
      {
        if (nearestX == nullptr || terrBase->GetRect()->LB.x < nearestX->GetRect()->LB.x)
        {
          nearestX = terrBase;
          float depth = rightSpeedBox->GetRect()->RB.x - terrBase->GetRect()->LB.x;

          xSpeed -= depth;
          xSpeedOrigin = 0;
        }
      }
    }

    if (xSpeed < 0)
    {
      if (BoundingBox::AABB(leftSpeedBox, terrBase) == true)
      {
        if (nearestX == nullptr || terrBase->GetRect()->RB.x > nearestX->GetRect()->RB.x)
        {
          nearestX = terrBase;
          float depth = terrBase->GetRect()->RB.x - leftSpeedBox->GetRect()->LB.x;

          xSpeed += depth;
          xSpeedOrigin = 0;
        }
      }
    }

    //if (BoundingBox::AABB(base, terrBase) == true) {
    //
    //  if (objPos.x < terrPos.x) {
    //    float depth = (objPos.x + objSize.x / 2) - (terrPos.x - terrSize.x / 2);
    //    object->Move({ -depth, 0, 0 });
    //    if (xSpeed > 0) xSpeed = 0;
    //  }
    //  else if (objPos.x > terrPos.x) {
    //    float depth = (terrPos.x + terrSize.x / 2) - (objPos.x - objSize.x / 2);
    //    object->Move({ depth, 0, 0 });
    //    if (xSpeed < 0) xSpeed = 0;
    //  }
    //}
  }
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
