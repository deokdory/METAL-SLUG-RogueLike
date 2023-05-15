#include "stdafx.h"
#include "Movement.h"

MovementSpeedBox::MovementSpeedBox(GameObject* object)
  : object(object)
{
  anchorPoint = object->GetAnchorPoint();

  auto objectSize = object->GetSize();

  Vector3 left, right, top, bottom;
  left = right = top = bottom = object->GetPosition();

  left.x -= objectSize.x / 2;
  right.x += objectSize.x / 2;

  if (anchorPoint == AnchorPoint::CENTER)
  {
    top.y += objectSize.y / 2;
    bottom.y -= objectSize.y / 2;
  }

  if (anchorPoint == AnchorPoint::MID_BOT)
  {
    top.y += objectSize.y;
  }

  speedBoxL = new BoundingBox(left, Values::ZeroVec3, 0, Color(0, 1, 0, 0.25f));
  speedBoxR = new BoundingBox(right, Values::ZeroVec3, 0, Color(0, 1, 0, 0.25f));
  speedBoxT = new BoundingBox(top, Values::ZeroVec3, 0, Color(0, 1, 0, 0.25f));
  speedBoxB = new BoundingBox(bottom, Values::ZeroVec3, 0, Color(0, 1, 0, 0.25f));

  if (anchorPoint == AnchorPoint::MID_BOT)
  {
    speedBoxL->SetAnchorPoint(AnchorPoint::RIGHT_BOT);
    speedBoxR->SetAnchorPoint(AnchorPoint::LEFT_BOT);
  }
  else
  {
    speedBoxL->SetAnchorPoint(AnchorPoint::RIGHT_MID);
    speedBoxR->SetAnchorPoint(AnchorPoint::LEFT_MID);
  }
  speedBoxT->SetAnchorPoint(AnchorPoint::MID_BOT);
  speedBoxB->SetAnchorPoint(AnchorPoint::MID_TOP);



}

MovementSpeedBox::~MovementSpeedBox()
{
  SAFE_DELETE(speedBoxB);
  SAFE_DELETE(speedBoxT);
  SAFE_DELETE(speedBoxR);
  SAFE_DELETE(speedBoxL);
}

void MovementSpeedBox::Update(float xSpeed, float ySpeed)
{
  auto objectSize = object->GetSize();

  Vector3 leftPos, rightPos, topPos, bottomPos;
  leftPos = rightPos = topPos = bottomPos = object->GetPosition();

  leftPos.x -= objectSize.x / 2;
  rightPos.x += objectSize.x / 2;

  if (anchorPoint == AnchorPoint::CENTER)
  {
    topPos.y += objectSize.y / 2;
    bottomPos.y -= objectSize.y / 2;
  }

  if (anchorPoint == AnchorPoint::MID_BOT)
  {
    topPos.y += objectSize.y;
  }

  Vector3 leftSize, rightSize, topSize, bottomSize;
  leftSize = rightSize = topSize = bottomSize = objectSize;

  leftSize.y = rightSize.y = objectSize.y - 1;
  topSize.x = bottomSize.x = objectSize.x - 1;

  if (ySpeed > 0.1f) {
    topSize.y = ySpeed;
    bottomSize.y = 0;
  }
  else if (ySpeed < -0.1f) {
    topSize.y = 0;
    bottomSize.y = -ySpeed;
  }
  else
  {
    topSize.y = bottomSize.y = 0;
  }
  
  if (xSpeed > 0.1f) {
    leftSize.x = 0;
    rightSize.x = xSpeed;
  }
  else if ( xSpeed < -0.1f) {
    leftSize.x = -xSpeed;
    rightSize.x = 0;
  }
  else
  {
    leftSize.x = rightSize.x = 0;
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

BoundingBox* MovementSpeedBox::GetBox(Slot slot)
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
  float globalSpeed = Time::Get()->GetGlobalSpeed();

  // 가속도 관련
  UpdateAccel();

  // 낙하 
  Falling();

  xSpeed = xSpeedOrigin * globalSpeed;
  ySpeed = ySpeedOrigin * globalSpeed;

  speedBox->Update(xSpeed, ySpeed);
  collisionCheck();

  Vector3 move = {xSpeed, ySpeed, 0 };
  object->Move(move);
}

void Movement::Render()
{
  speedBox->Render();
}

void Movement::GUI()
{
  std::string speedStr = "X SPD " + std::to_string(xSpeed) + ", Y SPD " + std::to_string(ySpeed);
  std::string accelStr = "Accel " + std::to_string(accel);

  ImGui::Begin("Movement");
  {
    ImGui::Text(speedStr.c_str());
    ImGui::Text(accelStr.c_str());
  }
  ImGui::End();
}
void Movement::Falling()
{
  auto globalSpeed = Time::Get()->GetGlobalSpeed();
  auto globalGravity = GameManager::Get()->GetGlobalGravity();

  if (isFalling) {
    if (ySpeed > fallingSpeedMax) ySpeedOrigin -= ((globalGravity + gravityOffset) * globalSpeed);
  }
  else
  {
    ySpeedOrigin = -0.1f;
  }
}

void Movement::MoveLeft()
{
  if (xSpeedOrigin > -xSpeedMax) {
    if (xSpeedOrigin > 0) SlowDown();
    xSpeedOrigin -= accel;
  }
  else
    xSpeedOrigin = -xSpeedMax;
}

void Movement::MoveRight()
{
  if (xSpeedOrigin < xSpeedMax) {
    if (xSpeedOrigin < 0) SlowDown();
    xSpeedOrigin += accel;
  }
  else
    xSpeedOrigin = xSpeedMax;
}

void Movement::SlowDown()
{
  if (xSpeedOrigin > 0.5f) xSpeedOrigin -= accel * 2;
  else if (xSpeedOrigin < -0.5f) xSpeedOrigin += accel * 2;
  else xSpeedOrigin = 0.f;
}

void Movement::Jump()
{
  if (isFalling == false)
  {
    ySpeedOrigin = jumpPower;
    isFalling = true;
  }
}

void Movement::UpdateAccel()
{
  accel = accelOrigin * Time::Get()->GetGlobalSpeed();
}

void Movement::collisionCheck()
{
  isFalling = true;

  auto& terrains = GameManager::Get()->GetCurrentLevel()->GetTerrains();

  auto* bottom = object->GetCollision()->GetBottom();
  auto* top = object->GetCollision()->GetTop();
  auto* base = object->GetCollision()->GetBase();

  auto* bottomSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::BOTTOM);
  auto* topSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::TOP);
  auto* leftSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::LEFT);
  auto* rightSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::RIGHT);

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
          //std::cout << std::fixed << "촥 " << ySpeed << std::endl;
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
