#include "Framework.h"
#include "Collision.h"

Collision::Collision(GameObject* object)
  : object(object),
  objPos(object->GetPosition()),
  objSize(object->GetSize()),
  objRotation(object->GetRotation()) {}

Collision::~Collision() 
{
  SAFE_DELETE(base);
  SAFE_DELETE(footholder);
}

void Collision::Update() {

  objPos = object->GetPosition();
  objSize = object->GetSize();
  objRotation = object->GetRotation();

  if (base) 
  {
    Vector3 size = objSize - Vector3(1, 1, 0);
    base->Update(objPos, size, objRotation);
  }

  //if (bottom) {
  //  Vector3 position = objPos;
  //  Vector3 size = objSize;
  //
  //  if (anchorPoint == AnchorPoint::CENTER) position.y -= objSize.y / 2;
  //
  //  size.x -= 1;
  //  size.y = collisionThickness;
  //
  //  bottom->Update(position, size, objRotation);
  //}
  //if (footholder) {
  //  Vector3 position = objPos;
  //  Vector3 size = objSize;
  //
  //  if (anchorPoint == AnchorPoint::CENTER) position.y += objSize.y / 2;
  //
  //  size.x -= 1;
  //  size.y = collisionThickness;
  //
  //  footholder->Update(position, size, objRotation);
  //}
}

void Collision::Render() {
  if (base) base->Render();
  if (footholder) footholder->Render();
}

void Collision::InitializeBase() {
  base = new BoundingBox(objPos, objSize, objRotation, Color(0, 0, 1, 0.25f));
  if (anchorPoint == AnchorPoint::MID_BOT) base->SetAnchorPoint(AnchorPoint::MID_BOT);
}

//void Collision::InitializeBottom() {
//  Vector3 position = objPos;
//  Vector3 size = objSize;
//
//  if (anchorPoint == AnchorPoint::CENTER) position.y -= objSize.y / 2;
//
//  size.x -= 1;
//  size.y = collisionThickness;
//
//  bottom = new BoundingBox(position, size, objRotation, Color(1, 0, 1, 0.5f));
//  bottom->SetAnchorPoint(AnchorPoint::MID_BOT);
//}
//
void Collision::InitializeFootholder() {
  Vector3 position = objPos;
  Vector3 size = objSize;

  if (anchorPoint == AnchorPoint::CENTER) position.y += objSize.y / 2;

  size.x -= 1;
  size.y = collisionThickness;

  footholder = new BoundingBox(position, size, objRotation, Color(1, 0, 1, 0.5f));
  footholder->SetAnchorPoint(AnchorPoint::MID_TOP);
}

TerrainCollision::TerrainCollision(GameObject* object, Type type)
 : Collision(object), terrainType(type)
{
  if (footholder != nullptr)
  {
    std::cout << "Collision::footholder slot is already exist!" << std::endl;
    assert(false);
  }

  objPos = object->GetPosition();
  objSize = object->GetSize();

  Vector3 position = Values::ZeroVec3;
  Vector3 size = { TILESIZE, collisionThickness, 0 };
  float rotation = 0.0f;

  switch (type)
  {
  case TerrainCollision::Type::FH_MID:
    position = objPos + Vector3(0, 20, 0);
    footholder = new BoundingBox(position, size, rotation, Color(1.0f, 0.0f, 1.0f, 0.25f));
    break;
  case TerrainCollision::Type::FH_EDGE_L:
    position = objPos + Vector3(0, 20, 0);
    size.x /= 2;

    footholder = new BoundingBox(position, size, rotation, Color(1.0f, 0.0f, 1.0f, 0.25f));
    footholder->SetAnchorPoint(AnchorPoint::LEFT_MID);

    break;
  case TerrainCollision::Type::FH_EDGE_R:
    position = objPos + Vector3(0, 20, 0);
    size.x /= 2;

    footholder = new BoundingBox(position, size, rotation, Color(1.0f, 0.0f, 1.0f, 0.25f));
    footholder->SetAnchorPoint(AnchorPoint::RIGHT_MID);

    break;
  case TerrainCollision::Type::STAIR_UP:
    position = objPos;
    size.x = TILESIZE * 4;
    rotation = 45;

    footholder = new BoundingBox(position, size, rotation, Color(1.0f, 0.0f, 1.0f, 0.25f));
    
    break;
  case TerrainCollision::Type::STAIR_DOWN:
    position = objPos;
    size.x = TILESIZE * 4;
    rotation = -45;

    footholder = new BoundingBox(position, size, rotation, Color(1.0f, 0.0f, 1.0f, 0.25f));

    break;
  default:
    break;
  }

  footholder->Update(position, size, rotation);

}

void TerrainCollision::Update()
{
}
