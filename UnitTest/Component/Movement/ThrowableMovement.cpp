#include "stdafx.h"
#include "ThrowableMovement.h"

ThrowableMovement::ThrowableMovement(GameObject* object , float xSpeed, float ySpeed)
  : Movement(object)
{
  isFalling = true;

  this->accelOrigin = 0.1f;

  this->xSpeedOrigin = xSpeed;
  this->ySpeedOrigin = ySpeed;
}

ThrowableMovement::~ThrowableMovement()
{
}

void ThrowableMovement::Update()
{
  __super::Update();
}

void ThrowableMovement::Render()
{
  __super::Render();
}

void ThrowableMovement::GUI()
{

}

void ThrowableMovement::Falling()
{
  auto globalSpeed = Time::Get()->GetGlobalSpeed();
  auto globalGravity = GameManager::Get()->GetGlobalGravity();

  if (bounce.y != 0.0f)
    ySpeedOrigin = bounce.y;

  if (bounce.x != 0.0f)
    xSpeedOrigin = bounce.x;

  if (isFalling) {
    if (ySpeed > fallingSpeedMax) ySpeedOrigin -= ((globalGravity + gravityOffset) * globalSpeed);
  }
  bounce = Values::ZeroVec3;
}

void ThrowableMovement::collisionCheck()
{
  isFalling = true;

  auto& terrains = GameManager::Get()->GetCurrentLevel()->GetTerrains();
  auto& objects = GameManager::Get()->GetCurrentLevel()->GetObjects();

  auto* bottom = object->GetCollision()->GetBottom();
  auto* top = object->GetCollision()->GetTop();
  auto* base = object->GetCollision()->GetBase();

  auto* bottomSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::BOTTOM);
  auto* rightSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::RIGHT);
  auto* leftSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::LEFT);
  auto* topSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::TOP);

  auto objPos = object->GetPosition();
  auto objSize = object->GetSize();

  Vector3 terrPos = Values::ZeroVec3;
  Vector3 terrSize = Values::ZeroVec3;

  BoundingBox* terrTop, * terrBottom, * terrBase;

  BoundingBox* nearestY = nullptr;
  BoundingBox* nearestX = nullptr;

  for (auto terr : terrains) {

    terrTop = terr->GetCollision()->GetTop();
    terrBase = terr->GetCollision()->GetBase();
    terrBottom = terr->GetCollision()->GetBottom();

    terrPos = terr->GetPosition();
    terrSize = terr->GetSize();

    if (ySpeed < 0) {
      if (BoundingBox::AABB(bottomSpeedBox, terrTop))
      {
        isFalling = false;
        bounce.y = (std::abs(ySpeed) / Time::Get()->GetGlobalSpeed()) * 0.5f;

        if (nearestY == nullptr || terrTop->GetRect()->LT.y > nearestY->GetRect()->LT.y)
        {
          nearestY = terrTop;
          float depth = std::abs(bottomSpeedBox->GetRect()->RB.y - terrTop->GetRect()->LT.y);

          ySpeed += depth;
          SlowDown();
        }
      }
    }

    if (ySpeed > 0)
    {
      if (BoundingBox::AABB(topSpeedBox, terrBottom))
      {
        ySpeedOrigin = 0;
        if (nearestY == nullptr || terrBottom->GetRect()->LB.y < nearestY->GetRect()->LB.y)
        {
          nearestY = terrBottom;
          float depth = std::abs(topSpeedBox->GetRect()->LT.y - terrBottom->GetRect()->LB.y);

          ySpeed -= depth;
          SlowDown();
        }
      }
    }

    //if (ySpeed >= 0) {
    //  if (BoundingBox::AABB(top, terrBottom)) {
    //    ySpeed = 0;
    //  }
    //}


    if (xSpeed > 0)
    {
      if (BoundingBox::AABB(rightSpeedBox, terrBase) == true) 
      {
        bounce.x = ( -xSpeed / Time::Get()->GetGlobalSpeed()) * 0.5;

        if (nearestX == nullptr || terrBase->GetRect()->LB.x < nearestX->GetRect()->LB.x)
        {
          nearestX = terrBase;
          float depth = rightSpeedBox->GetRect()->RB.x - terrBase->GetRect()->LB.x;

          xSpeed -= depth;
        }
      }
    }

    if (xSpeed < 0)
    {
      if (BoundingBox::AABB(leftSpeedBox, terrBase) == true)
      {
        bounce.x = ( -xSpeed / Time::Get()->GetGlobalSpeed()) * 0.5;

        if (nearestX == nullptr || terrBase->GetRect()->RB.x > nearestX->GetRect()->RB.x)
        {
          nearestX = terrBase;
          float depth = terrBase->GetRect()->RB.x - leftSpeedBox->GetRect()->LB.x;

          xSpeed += depth;
        }
      }
    }
  }
}
