#include "stdafx.h"
#include "ThrowableMovement.h"

ThrowableMovement::ThrowableMovement(GameObject* object , float xSpeed, float ySpeed)
  : Movement(object)
{
  isFalling = true;

  this->accelOrigin = 0.05f;

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

  if (bounce > 1.0f)
    ySpeedOrigin = bounce;

  if (isFalling) {
    if (ySpeed > fallingSpeedMax) ySpeedOrigin -= ((globalGravity + gravityOffset) * globalSpeed);
  }
  bounce = 0.0f;
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

  auto objPos = object->GetPosition();
  auto objSize = object->GetSize();

  Vector3 terrPos = Values::ZeroVec3;
  Vector3 terrSize = Values::ZeroVec3;

  BoundingBox* terrTop, * terrBottom, * terrBase;

  BoundingBox* nearestBottom = nullptr;

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
        bounce = (std::abs(ySpeed) / Time::Get()->GetGlobalSpeed()) * 0.5f;

        if (nearestBottom == nullptr || terrTop->GetRect()->LT.y > nearestBottom->GetRect()->LT.y)
        {
          nearestBottom = terrTop;

          float depth = bottomSpeedBox->GetRect()->RB.y - terrTop->GetRect()->LT.y;

          ySpeed -= depth;

          SlowDown();
          
        }
      }
    }

    if (ySpeed >= 0) {
      if (BoundingBox::AABB(top, terrBottom)) {
        ySpeed = 0;
      }
    }

    if (BoundingBox::AABB(base, terrBase) == true) {
      if (objPos.x < terrPos.x) {
        float depth = (objPos.x + objSize.x / 2) - (terrPos.x - terrSize.x / 2);
        object->Move({ -depth, 0, 0 });

        if (xSpeed > 0) xSpeed = 0;
      }

      else if (objPos.x > terrPos.x) {
        float depth = (terrPos.x + terrSize.x / 2) - (objPos.x - objSize.x / 2);
        object->Move({ depth, 0, 0 });

        if (xSpeed < 0) xSpeed = 0;
      }
    }
  }
}
