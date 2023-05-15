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
  SAFE_DELETE(top);
  SAFE_DELETE(bottom);
}

void Collision::Update() {

  objPos = object->GetPosition();
  objSize = object->GetSize();
  objRotation = object->GetRotation();

  if (base) {
    Vector3 size = objSize - Vector3(1, 1, 0);
    base->Update(objPos, size, objRotation);
  }

  if (bottom) {
    Vector3 position = objPos;
    Vector3 size = objSize;

    if (anchorPoint == AnchorPoint::CENTER) position.y -= objSize.y / 2;

    size.x -= 1;
    size.y = collisionThickness;

    bottom->Update(position, size, objRotation);
  }
  if (top) {
    Vector3 position = objPos;
    Vector3 size = objSize;

    if (anchorPoint == AnchorPoint::CENTER) position.y += objSize.y / 2;

    size.x -= 1;
    size.y = collisionThickness;

    top->Update(position, size, objRotation);
  }
}

void Collision::Render() {
  if (base) base->Render();
  if (top) top->Render();
  if (bottom) bottom->Render();
}

void Collision::InitializeBase() {
  base = new BoundingBox(objPos, objSize, objRotation, Color(0, 0, 1, 0.25f));
  if (anchorPoint == AnchorPoint::MID_BOT) base->SetAnchorPoint(AnchorPoint::MID_BOT);
}

void Collision::InitializeBottom() {
  Vector3 position = objPos;
  Vector3 size = objSize;

  if (anchorPoint == AnchorPoint::CENTER) position.y -= objSize.y / 2;

  size.x -= 1;
  size.y = collisionThickness;

  bottom = new BoundingBox(position, size, objRotation, Color(1, 0, 1, 0.5f));
  bottom->SetAnchorPoint(AnchorPoint::MID_BOT);
}

void Collision::InitializeTop() {
  Vector3 position = objPos;
  Vector3 size = objSize;

  if (anchorPoint == AnchorPoint::CENTER) position.y += objSize.y / 2;

  size.x -= 1;
  size.y = collisionThickness;

  top = new BoundingBox(position, size, objRotation, Color(1, 0, 1, 0.5f));
  top->SetAnchorPoint(AnchorPoint::MID_TOP);
}

