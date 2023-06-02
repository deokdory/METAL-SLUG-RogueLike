#include "stdafx.h"
#include "Movement.h"

MovementSpeedBox::MovementSpeedBox(GameObject* object)
  : object(object)
{
  anchorPoint = object->GetAnchorPoint();

  auto objectSize = object->GetSize();

  Vector3 left, right, footholder, bottom;
  left = right = footholder = bottom = object->GetPosition();

  left.x -= objectSize.x / 2;
  right.x += objectSize.x / 2;

  if (anchorPoint == AnchorPoint::CENTER)
  {
    footholder.y += objectSize.y / 2;
    bottom.y -= objectSize.y / 2;
  }

  if (anchorPoint == AnchorPoint::MID_BOT)
  {
    footholder.y += objectSize.y;
  }

  speedBoxL = new BoundingBox(left, Values::ZeroVec3, 0, Color(0, 1, 0, 0.25f));
  speedBoxR = new BoundingBox(right, Values::ZeroVec3, 0, Color(0, 1, 0, 0.25f));
  speedBoxT = new BoundingBox(footholder, Values::ZeroVec3, 0, Color(0, 1, 0, 0.25f));
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

  leftPos.x += -objectSize.x / 2 + 1;
  rightPos.x += objectSize.x / 2 - 1;

  if (anchorPoint == AnchorPoint::CENTER)
  {
    topPos.y += objectSize.y / 2 - 1;
    bottomPos.y += -objectSize.y / 2 + 1;
  }

  if (anchorPoint == AnchorPoint::MID_BOT)
  {
    topPos.y += objectSize.y - 1;
  }

  Vector3 leftSize, rightSize, topSize, bottomSize;
  leftSize = rightSize = topSize = bottomSize = objectSize;

  leftSize.y = rightSize.y = objectSize.y;
  topSize.x = bottomSize.x = objectSize.x;

  if (ySpeed > 1.0f) {
    topSize.y = ySpeed;
    bottomSize.y = 1.0f;
  }
  else if (ySpeed < -1.0f) {
    topSize.y = 1.0f;
    bottomSize.y = -ySpeed;
  }
  else
  {
    topSize.y = bottomSize.y = 1.0f;
  }
  
  if (xSpeed > 1.0f) {
    leftSize.x = 1.0f;
    rightSize.x = xSpeed;
  }
  else if ( xSpeed < -1.0f) {
    leftSize.x = -xSpeed;
    rightSize.x = 1.0f;
  }
  else
  {
    leftSize.x = rightSize.x = 1.0f;
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

  terrainCollisionCheck();
  interaction();

  if (isFalling) standOn = nullptr;

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
    ySpeedOrigin = 0.0f;
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
    standOn = nullptr;
  }
}

void Movement::UpdateAccel()
{
  accel = accelOrigin * Time::Get()->GetGlobalSpeed();
}

void Movement::terrainCollisionCheck()
{
  nearestFootholder = nullptr;
  nearestTerrainR = nullptr;
  nearestTerrainL = nullptr;

  nearestStair = nullptr;

  auto& terrains = GameManager::Get()->GetCurrentLevel()->GetTerrains();

  auto* base = object->GetCollision()->GetBase();

  auto* bottomSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::BOTTOM);
  auto* topSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::TOP);
  auto* leftSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::LEFT);
  auto* rightSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::RIGHT);

  auto objPos = object->GetPosition();
  auto objSize = object->GetSize();

  Vector3 terrPos;
  Vector3 terrSize;

  BoundingBox* footholder, * terrBottom, * terrBase;
  float nearestPositionX = 0.0f;
  float nearestPositionY = 0.0f;

  Terrain::Type currentTerrType;

  for (auto terr : terrains) {
    footholder = terr->GetCollision()->GetFootholder();
    terrBase = terr->GetCollision()->GetBase();
    //terrBottom = terr->GetCollision()->GetBottom();

    terrPos = terr->GetPosition();
    terrSize = terr->GetSize();

    currentTerrType = terr->GetTerrainType();

    if (ySpeed <= 0.0f)
    {
      if (BoundingBox::OBB(bottomSpeedBox, footholder))
      {
        switch (currentTerrType)
        {
        case Terrain::Type::STAIR_UP:
        case Terrain::Type::STAIR_DOWN:
          nearestStair = terr;
        //{
        //  RectEdge stairRect = *footholder->GetRect();
        //  RectEdge bottomSpeedBoxRect = *bottomSpeedBox->GetRect();
        //
        //  float heightOnStair = 0.0f;
        //
        //  float length = 0.0f;
        //  if (currentTerrType == Terrain::Type::STAIR_UP)
        //  {
        //    length = stairRect.RT.x - bottomSpeedBoxRect.RB.x;
        //    if (length < 0) length = 0;
        //
        //    heightOnStair = stairRect.RT.y - length - 1;
        //  }
        //  else
        //  {
        //    length = bottomSpeedBoxRect.LB.x - stairRect.LT.x;
        //    if (length < 0) length = 0;
        //
        //    heightOnStair = stairRect.LT.y - length - 1;
        //  }
        //  if (bottomSpeedBoxRect.LT.y > heightOnStair) nearestStair = terr;
        //}
          break;
        default:
          if (nearestFootholder == nullptr || footholder->GetRect()->LT.y > nearestPositionY)
          {
            nearestPositionY = footholder->GetRect()->LT.y;
            nearestFootholder = terr;
          }
          break;
        }
      }
    }
    
    //if (ySpeed > 0) {
    //  if (BoundingBox::AABB(topSpeedBox, terrBottom))
    //  {
    //    
    //    if (nearestY == nullptr || terrBottom->GetRect()->LB.y < nearestY->GetRect()->LB.y)
    //    {
    //      nearestY = terrBottom;
    //
    //      float depth = std::abs(topSpeedBox->GetRect()->LT.y - nearestY->GetRect()->LB.y);
    //      ySpeed -= depth;
    //    }
    //  }
    //}

    if (xSpeed > 0)
    {
      if (BoundingBox::OBB(rightSpeedBox, terrBase) == true)
      {
        if (nearestTerrainR == nullptr || terrBase->GetRect()->LB.x < nearestPositionX)
        {
          nearestPositionX = terrBase->GetRect()->LB.x;
          nearestTerrainR = terr;
        }
      }
    }

    if (xSpeed < 0)
    {
      if (BoundingBox::OBB(leftSpeedBox, terrBase) == true)
      {
        if (nearestTerrainL == nullptr || terrBase->GetRect()->RB.x > nearestPositionX)
        {
          nearestPositionX = terrBase->GetRect()->LB.x;
          nearestTerrainL = terr;
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

void Movement::interaction()
{
  isFalling = true;

  auto* objectBox = object->GetCollision()->GetBase();

  auto* bottomSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::BOTTOM);
  auto* topSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::TOP);
  auto* leftSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::LEFT);
  auto* rightSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::RIGHT);

  Vector3 forcePosition = Values::ZeroVec3;

  if (standOn != nullptr)
  {
    if (standOn == nearestStair)
    {
      isFalling = false;
      ySpeedOrigin = 0.0f;

      if (xSpeed)
      {
        switch (standOn->GetTerrainType())
        {
        case Terrain::Type::STAIR_UP:
        {
          xSpeed = ySpeed = xSpeed * 0.5f;
          break;
        }
        case Terrain::Type::STAIR_DOWN:
        {
          ySpeed = -xSpeed * 0.5f;
          xSpeed = xSpeed * 0.5f;
          break;
        }
        default:
          break;
        }
      }
    }
    else if (standOn == nearestFootholder)
    {

    }
  }
  else
  {
    // 발판에 충돌을 안했다면 계단은 충돌했는지
    if (nearestFootholder == nullptr) nearestFootholder = nearestStair;
    if (nearestStair != nullptr && (isDirectingDown || isDirectingUp)) nearestFootholder = nearestStair;

    // 계단 혹은 발판에 충돌함
    if (nearestFootholder != nullptr)
    {
      //isFalling = false;

      float depth = 0.0f;
      auto terrainType = nearestFootholder->GetTerrainType();

      // 계단(경사로)
      if (terrainType == Terrain::Type::STAIR_DOWN || terrainType == Terrain::Type::STAIR_UP)
      {
        float rotation = 0.0f;
        Vector3 objectBoxEdge = Values::ZeroVec3;
        Vector3 stairBeginPoint = Values::ZeroVec3; // 아래쪽 계단 시작점의 발판 상단 끝
        RectEdge stairRect = *nearestFootholder->GetCollision()->GetFootholder()->GetRect();
        float length = 0.0f;

        if (terrainType == Terrain::Type::STAIR_UP)
        {
          rotation = 45;
          objectBoxEdge = objectBox->GetRect()->RB;
          stairBeginPoint = stairRect.RT;

          // 계단 상단 끝부분에 닿아있을 때 X값 제한
          if (objectBoxEdge.x > stairBeginPoint.x)
          {
            length = 0;
          }
          // 그 외 상황
          else
          {
            length = stairBeginPoint.x - objectBoxEdge.x;
          }
        }
        else
        {
          rotation = -45;
          objectBoxEdge = objectBox->GetRect()->LB;
          stairBeginPoint = stairRect.RT;

          if (objectBoxEdge.x < stairRect.LT.x)
          {
            length = 0;
          }
          else
          {
            length = objectBoxEdge.x - stairBeginPoint.x;
          }
          //if (length > bottomSpeedBox->GetRect()->LT.y)
          //{
          //  isFalling = true;
          //}

        }
        isFalling = false;
        depth = length - (stairBeginPoint.y - bottomSpeedBox->GetRect()->RB.y);

        std::cout << "ySpeed : " << ySpeed << "|| depth : " << depth << std::endl;

        ySpeed = -depth;
        ySpeedOrigin = 0.0f;

        lastStanded = standOn = nearestFootholder;
      }

      // 계단이 아님
      else
      {
        isFalling = false;

        float footholderEdge = nearestFootholder->GetCollision()->GetFootholder()->GetRect()->RT.y;
        depth = std::abs(bottomSpeedBox->GetRect()->RB.y - footholderEdge);

        ySpeed += depth;
        ySpeedOrigin = 0;

        lastStanded = standOn = nearestFootholder;
      }
    }
  }
  // 왼쪽 지형에 부딪힘
  if (nearestTerrainL != nullptr)
  {
    float terrainEdge = nearestTerrainL->GetCollision()->GetBase()->GetRect()->RB.x;
    float depth = terrainEdge - leftSpeedBox->GetRect()->LB.x;

    xSpeed += depth;
    xSpeedOrigin = 0;
  }

  // 오른쪽 지형에 부딪힘
  if (nearestTerrainR != nullptr)
  {
    float terrainEdge = nearestTerrainR->GetCollision()->GetBase()->GetRect()->LB.x;
    float depth = rightSpeedBox->GetRect()->RB.x - terrainEdge;

    xSpeed -= depth;
    xSpeedOrigin = 0;
  }

}
