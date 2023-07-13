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
  topSize.x = bottomSize.x = objectSize.x / 2;

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

  UpdateAccel();

  // 낙하 
  Falling();

  xSpeed = xSpeedOrigin * globalSpeed;
  ySpeed = ySpeedOrigin * globalSpeed;

  speedBox->Update(xSpeed, ySpeed);

  terrainCollisionCheck();
  interaction();
}

void Movement::Render()
{
  speedBox->Render();
}

void Movement::GUI()
{
  std::string speedStr = "X SPD " + std::to_string(xSpeed) + ", Y SPD " + std::to_string(ySpeed);
  std::string accelStr = "Accel " + std::to_string(accel);
  std::string standOnStr = "Stand On ";
  if (standOn)
  {
    switch (standOn->GetTerrainType())
    {
    case Terrain::Type::STAIR:
      standOnStr += "stair";
      break;
    default:
      standOnStr += "normal footholder";
      break;
    }
  }
  else
  {
    standOnStr += "nothing";
  }

  ImGui::Begin("Movement");
  {
    ImGui::Text(speedStr.c_str());
    ImGui::Text(accelStr.c_str());
    ImGui::Text(standOnStr.c_str());
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
    ySpeedOrigin = jumpPower;
    isFalling = true;
    standOn = nullptr;
}

void Movement::DropDown()
{
  if (standOn)
  {
    if (standOn->GetCanDropDown())
    {
      standOn = nullptr;
      isDropping = true;
    }
  }
}

void Movement::Stop()
{
  xSpeed = xSpeedOrigin = 0.0f;
}

void Movement::UpdateAccel()
{
  accel = accelOrigin * Time::Get()->GetGlobalSpeed();
}

void Movement::terrainCollisionCheck()
{
  Room* currentRoom = object->GetCurrentRoom();

  nearestFootholder = nullptr;
  nearestTerrainR = nullptr;
  nearestTerrainL = nullptr;

  nearestStair = nullptr;

  nearestPositionX = 0.0f;
  nearestPositionY = 0.0f;

  if (currentRoom)
  {
    terrainCollisionCheck(currentRoom->GetTerrains(Room::Layer::BACKGROUND));
    terrainCollisionCheck(currentRoom->GetTerrains(Room::Layer::MIDDLEGROUND));
    terrainCollisionCheck(currentRoom->GetTerrains(Room::Layer::FOREGROUND));
    terrainCollisionCheck(currentRoom->GetTerrains(Room::Layer::STAIRS));
  }
}

void Movement::terrainCollisionCheck(std::vector<Terrain*>& terrains)
{
  auto* bottomSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::BOTTOM);
  auto* topSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::TOP);
  auto* leftSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::LEFT);
  auto* rightSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::RIGHT);

  auto objPos = object->GetPosition();
  auto objSize = object->GetSize();

  Vector3 terrPos;
  Vector3 terrSize;

  BoundingBox* footholder, * terrBottom, * terrBase;

  Terrain::Type currentTerrType;

  if (terrains.empty() == false)
  {
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
          case Terrain::Type::STAIR:
            nearestStair = terr;

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

      {
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
      }

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
    }
  }
}

void Movement::interaction()
{
  isFalling = true;
  standOn = nullptr;

  auto* objectBox = object->GetCollision()->GetBase();

  auto* bottomSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::BOTTOM);
  auto* topSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::TOP);
  auto* leftSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::LEFT);
  auto* rightSpeedBox = speedBox->GetBox(MovementSpeedBox::Slot::RIGHT);

  Vector3 objectPosition = object->GetPosition();

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

  objectPosition.x += xSpeed; // 발판에 고정시키기 전 xSpeed 반영

  float footholderTop = 0.0f;

  if (nearestFootholder)
  {
    if (lastStanded == nullptr) standOn = nearestFootholder;
    else if (isDropping == false) standOn = nearestFootholder;
    else if (lastStanded->GetPosition().y != nearestFootholder->GetPosition().y) 
      standOn = nearestFootholder;

    if (nearestStair)
    {
      BoundingBox* stairFootholder = nearestStair->GetCollision()->GetFootholder();
      footholderTop = nearestStair->GetFootholderTop(objectPosition);

      if (isDirectingDown)
      {
        if (stairFootholder->GetPosition().y - footholderTop < TILESIZE) 
          standOn = nearestStair;
      }

      if (isDirectingUp)
      {
        if (stairFootholder->GetPosition().y - footholderTop > TILESIZE) 
          standOn = nearestStair;
      }
    }
  }
  else
  {
    if (lastStanded == nearestStair && isDropping) standOn = nullptr;
    else standOn = nearestStair;
  }

  // 발판에 충돌 중일 때
  if (standOn != nullptr)
  {
    ySpeedOrigin = 0;
    isFalling = isDropping = false;

    lastStanded = standOn;
    objectPosition.y = standOn->GetFootholderTop(objectPosition);
  }

  // 발판에 충돌 중이 아닐 때
  else
  {
    objectPosition.y += ySpeed;
  }
  object->SetPositionForce(objectPosition);
}
