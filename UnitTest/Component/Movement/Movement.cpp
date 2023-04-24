#include "stdafx.h"
#include "Movement.h"

#include "Game/GameObject.h"

#include "Level/Level.h"
#include "Component/Collision/Collision.h"

MovementSpeedBox::MovementSpeedBox(GameObject* object)
  : object(object)
{
  auto objectSize = object->GetSize();

  Vector3 left, right, top, bottom;
  left = right = top = bottom = object->GetPosition();

  left.x -= objectSize.x / 2;
  right.x += objectSize.x / 2;
  top.y += objectSize.y / 2;
  bottom.y -= objectSize.y / 2;

  speedBoxL = new BoundingBox(left, Values::ZeroVec3, 0, Color(0, 1, 0, 0.25f));
  speedBoxR = new BoundingBox(right, Values::ZeroVec3, 0, Color(0, 1, 0, 0.25f));
  speedBoxT = new BoundingBox(top, Values::ZeroVec3, 0, Color(0, 1, 0, 0.25f));
  speedBoxB = new BoundingBox(bottom, Values::ZeroVec3, 0, Color(0, 1, 0, 0.25f));

  speedBoxL->SetAnchorPoint(5);
  speedBoxR->SetAnchorPoint(4);
  speedBoxT->SetAnchorPoint(7);
  speedBoxB->SetAnchorPoint(2);
}

MovementSpeedBox::~MovementSpeedBox()
{
  SAFE_DELETE(speedBoxL);
  SAFE_DELETE(speedBoxR);
  SAFE_DELETE(speedBoxT);
  SAFE_DELETE(speedBoxB);
}

void MovementSpeedBox::Update(float xSpeed, float ySpeed)
{
  auto objectSize = object->GetSize();

  Vector3 leftPos, rightPos, topPos, bottomPos;
  leftPos = rightPos = topPos = bottomPos = object->GetPosition();

  topPos.y += objectSize.y / 2;
  leftPos.x -= objectSize.x / 2;
  rightPos.x += objectSize.x / 2;
  bottomPos.y -= objectSize.y / 2;

  Vector3 leftSize, rightSize, topSize, bottomSize;
  leftSize = rightSize = topSize = bottomSize = objectSize;
  leftSize.y = rightSize.y = objectSize.y;
  topSize.x = bottomSize.x = objectSize.x;

  if (ySpeed > 0) {
    topSize.y = ySpeed;
    bottomSize.y = 0;
  }
  else {
    topSize.y = 0;
    bottomSize.y = -ySpeed;
  }

  if (xSpeed > 0) {
    leftSize.x = 0;
    rightSize.x = xSpeed;
  }
  else {
    leftSize.x = -xSpeed;
    rightSize.x = 0;
  }

  speedBoxT->Update(topPos, topSize, 0);
  speedBoxB->Update(bottomPos, bottomSize, 0);
  speedBoxL->Update(leftPos, leftSize, 0);
  speedBoxR->Update(rightPos, rightSize, 0);
}

void MovementSpeedBox::Render()
{
  speedBoxL->Render();
  speedBoxR->Render();
  speedBoxT->Render();
  speedBoxB->Render();
}

const BoundingBox* MovementSpeedBox::GetBox(Slot slot)
{
  switch (slot)
  {
  case MovementSpeedBox::Slot::LEFT: return speedBoxL;
  case MovementSpeedBox::Slot::RIGHT: return speedBoxR;
  case MovementSpeedBox::Slot::TOP: return speedBoxT;
  case MovementSpeedBox::Slot::BOTTOM: return speedBoxB;
  default: return nullptr;
  }
}

Movement::Movement(GameObject* object)
  : object(object)
{
  speedBox = new MovementSpeedBox(object);
}

Movement::~Movement()
{
  SAFE_DELETE(speedBox);
}

void Movement::Update()
{
  float globalSpeed = GameManager::Get()->GetGlobalSpeed();
  // 가속도 관련
  {
    accel = accelOrigin * globalSpeed;
  }
  // 낙하 
  {
    auto globalGravity = GameManager::Get()->GetGlobalGravity();
    if (isFalling)
      if (ySpeed > fallingSpeedMax) ySpeed -= (globalGravity + gravityOffset);
  }
  speedBox->Update(xSpeed, ySpeed);
  collisionCheck();

  Vector3 move = { xSpeed, ySpeed, 0 };
  object->Move(move);
}

void Movement::Render()
{
  speedBox->Render();
}

void Movement::GUI()
{
}

void Movement::MoveLeft()
{
  if (xSpeed > -xSpeedMax) {
    if (xSpeed > 0) SlowDown();
    xSpeed -= accel;
  }
  else
    xSpeed = -xSpeedMax;
}

void Movement::MoveRight()
{
  if (xSpeed < xSpeedMax) {
    if (xSpeed < 0) SlowDown();
    xSpeed += accel;
  }
  else
    xSpeed = xSpeedMax;
}

void Movement::SlowDown()
{
  if (xSpeed > 0.5f) xSpeed -= accel * 2;
  else if (xSpeed < -0.5f) xSpeed += accel * 2;
  else xSpeed = 0.f;
}

void Movement::Jump()
{
  if (isFalling == false)
  {
    ySpeed = jumpPower;
    isFalling = true;
  }
}

void Movement::collisionCheck()
{
  isFalling = true;

  auto& terrains = GameManager::Get()->GetCurrentLevel()->GetTerrains();

  auto bottom = object->GetCollision()->GetBottom();
  auto top = object->GetCollision()->GetTop();
  auto base = object->GetCollision()->GetBase();

  auto objPos = object->GetPosition();
  auto objSize = object->GetSize();

  Vector3 terrPos;
  Vector3 terrSize;

  BoundingBox* terrTop, * terrBottom, * terrBase;
  for (auto terr : terrains) {
    terrTop = terr->GetCollision()->GetTop();
    terrBase = terr->GetCollision()->GetBase();
    terrBottom = terr->GetCollision()->GetBottom();

    terrPos = terr->GetPosition();
    terrSize = terr->GetSize();

    if (ySpeed <= 0) {
      if (BoundingBox::AABB(bottom, terrTop)) {
        isFalling = false;
        ySpeed = 0;

        float depth = (terrPos.y + terrSize.y / 2) - (objPos.y - objSize.y / 2);
        if (depth > 0) {
          object->Move({ 0, depth, 0 });
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
