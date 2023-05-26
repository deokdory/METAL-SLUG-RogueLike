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

void PlayerMovement::collisionCheck()
{
  isFalling = true;

  auto& terrains = GameManager::Get()->GetCurrentLevel()->GetTerrains();

  //auto* bottom = object->GetCollision()->GetBottom();
  auto* footholder = object->GetCollision()->GetFootholder();
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

  Terrain* nearestTerrainY = nullptr;
  Terrain* nearestTerrainX = nullptr;

  float nearestPositionY = 0.0f;
  float nearestPositionX = 0.0f;

  for (auto terr : terrains) {
    auto terrainType = terr->GetTerrainType();

    terrTop = terr->GetCollision()->GetFootholder();
    terrBase = terr->GetCollision()->GetBase();
    //terrBottom = terr->GetCollision()->GetBottom();

    terrPos = terr->GetPosition();
    terrSize = terr->GetSize();

    if (ySpeed < 0)
    {
        if (BoundingBox::OBB(bottomSpeedBox, terrTop))
        {
          isFalling = false;
          if (nearestTerrainY == nullptr || terrTop->GetRect()->LT.y > nearestPositionY)
          {
            nearestPositionY = terrTop->GetRect()->LT.y;
            nearestTerrainY = terr;
          }
        }
    }
    //if (ySpeed > 0) {
    //  if (BoundingBox::AABB(topSpeedBox, terrBottom))
    //  {
    //    if (nearestY == nullptr || terrBottom->GetRect()->LB.y < nearestY->GetRect()->LB.y)
    //    {
    //      nearestY = terrBottom;
    //
    //      float depth = std::abs(topSpeedBox->GetRect()->LT.y - nearestY->GetRect()->LB.y);
    //      ySpeed -= depth;
    //
    //      isJumping = false;
    //      ySpeedOrigin = 0;
    //    }
    //  }
    //}

    if (xSpeed > 0)
    {
      if (BoundingBox::OBB(rightSpeedBox, terrBase) == true)
      {
        if (nearestTerrainX == nullptr || terrBase->GetRect()->LB.x < nearestPositionX)
        {
          nearestPositionX = terrBase->GetRect()->LB.x;
          nearestTerrainX = terr;
          float depth = rightSpeedBox->GetRect()->RB.x - terrBase->GetRect()->LB.x;

          xSpeed -= depth;
          xSpeedOrigin = 0;
        }
      }
    }

    else if (xSpeed < 0)
    {
      if (BoundingBox::OBB(leftSpeedBox, terrBase) == true)
      {
        if (nearestTerrainX == nullptr || terrBase->GetRect()->RB.x > nearestPositionX)
        {
          nearestPositionX = terrBase->GetRect()->RB.x;
          nearestTerrainX = terr;

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
  if (nearestTerrainY != nullptr)
  {
    float depth = 0.0f;
    auto terrainType = nearestTerrainY->GetTerrainType();

    if (terrainType == Terrain::Type::STAIR_DOWN || terrainType == Terrain::Type::STAIR_UP)
    {
      float rotation = 0.0f;
      Vector3 speedBoxEdge = Values::ZeroVec3;
      Vector3 terrBoxEdgeBottom = Values::ZeroVec3;
      float length = 0.0f;

      if (terrainType == Terrain::Type::STAIR_UP)
      {
        rotation = 45;
        speedBoxEdge = bottomSpeedBox->GetRect()->RB;
        terrBoxEdgeBottom = nearestTerrainY->GetCollision()->GetFootholder()->GetRect()->LT;

        //if (speedBoxEdge.x > ) speedBoxEdge.x = terrBoxEdgeBottom.x;

        length = speedBoxEdge.x - terrBoxEdgeBottom.x;
        //std::cout << length << std::endl;
      }
      else
      {
        rotation = -45;
        speedBoxEdge = bottomSpeedBox->GetRect()->LB;
        terrBoxEdgeBottom = nearestTerrainY->GetCollision()->GetFootholder()->GetRect()->RT;

        if (speedBoxEdge.x < terrBoxEdgeBottom.x) speedBoxEdge.x = terrBoxEdgeBottom.x;

        length = terrBoxEdgeBottom.x - speedBoxEdge.x;
      }
      //float tangent = length * std::tan(rotation);

      //std::cout << "탄젠트 : " << tangent << std::endl;
      std::cout << "바닥에서 스피드박스까지 : " << speedBoxEdge.y - terrBoxEdgeBottom.y << std::endl;

      depth = length - (speedBoxEdge.y - terrBoxEdgeBottom.y);
    }
    else
    {
      depth = std::abs(bottomSpeedBox->GetRect()->RB.y - nearestPositionY);
    }
    ySpeed += depth;
    ySpeedOrigin = 0;
    std::cout << "뎁쓰 : " << depth << std::endl;
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
