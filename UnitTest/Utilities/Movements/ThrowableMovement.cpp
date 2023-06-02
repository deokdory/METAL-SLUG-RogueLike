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

void ThrowableMovement::interaction()
{
  auto* bottomSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::BOTTOM);
  auto* rightSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::RIGHT);
  auto* leftSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::LEFT);
  auto* topSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::TOP);

  if (nearestFootholder)
  {
    auto terrainType = nearestFootholder->GetTerrainType();
    if (terrainType != Terrain::Type::STAIR_UP && terrainType != Terrain::Type::STAIR_DOWN)
    {
      bounce.y = (std::abs(ySpeed) / Time::Get()->GetGlobalSpeed()) * 0.5f;

      float terrainEdge = nearestFootholder->GetCollision()->GetFootholder()->GetRect()->LT.y;
      float depth = std::abs(bottomSpeedBox->GetRect()->RB.y - terrainEdge);

      ySpeed += depth;
      SlowDown();
    }
  }

  if (nearestTerrainR)
  {
    bounce.x = (-xSpeed / Time::Get()->GetGlobalSpeed()) * 0.5;

    float terrainEdge = nearestFootholder->GetCollision()->GetBase()->GetRect()->LB.x;
    float depth = rightSpeedBox->GetRect()->RB.x - terrainEdge;

    xSpeed -= depth;
  }

  if (nearestTerrainL)
  {
    bounce.x = (-xSpeed / Time::Get()->GetGlobalSpeed()) * 0.5;

    float terrainEdge = nearestFootholder->GetCollision()->GetBase()->GetRect()->RB.x;
    float depth = terrainEdge - leftSpeedBox->GetRect()->LB.x;

    xSpeed += depth;
  }
}