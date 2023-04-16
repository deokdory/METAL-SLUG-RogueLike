#include "stdafx.h"
#include "Collision.h"

#include "Game/GameObject.h"

Collision::Collision(GameObject* object)
  : object(object),
  objPos(object->GetPosition()),
  objSize(object->GetSize()),
  objRotation(object->GetRotation()) {}

Collision::~Collision() { SAFE_DELETE(base); }

void Collision::Update() {

  objPos = object->GetPosition();
  objSize = object->GetSize();
  objRotation = object->GetRotation();

  if (base) {
    if (bottom == nullptr && top == nullptr) {
      base->Update(object->GetPosition(), object->GetSize(), object->GetRotation());
    }
    else if (bottom && top) {
      Vector3 baseSize = { objSize.x, objSize.y - collisionThickness,
                          objSize.z };
      base->Update(objPos, baseSize, objRotation);
    }
    else if (bottom) {
      Vector3 basePos = { objPos.x, objPos.y + collisionThickness / 4, objPos.z };
      Vector3 baseSize = { objSize.x, objSize.y - collisionThickness / 2, objSize.z };
      base->Update(basePos, baseSize, objRotation);
    }
    else {
      Vector3 basePos = { objPos.x, objPos.y - collisionThickness / 4, objPos.z };
      Vector3 baseSize = { objSize.x, objSize.y - collisionThickness / 2 , objSize.z };
      base->Update(basePos, baseSize, objRotation);
    }
  }
  if (bottom) {
    Vector3 bottomPos = { objPos.x, objPos.y - objSize.y / 2 + collisionThickness / 2,
                         objPos.z };
    Vector3 bottomSize = { objSize.x - 2, collisionThickness, objSize.z };

    bottom->Update(bottomPos, bottomSize, objRotation);
  }
  if (top) {
    Vector3 topPos = { objPos.x, objPos.y + objSize.y / 2 - collisionThickness / 2,
                         objPos.z };
    Vector3 topSize = { objSize.x - 2, collisionThickness, objSize.z };

    top->Update(topPos, topSize, objRotation);
  }
}

void Collision::Render() {
  if (base) base->Render();
  if (top) top->Render();
  if (bottom) bottom->Render();
}

void Collision::InitializeBase() {
  base = new BoundingBox(objPos, objSize, objRotation, Color(0, 0, 1, 0.25f));
}

void Collision::InitializeBottom() {
  Vector3 bottomPos = { objPos.x, objPos.y - objSize.y / 2 + collisionThickness / 2, objPos.z };
  Vector3 bottomSize = { objSize.x - 2, collisionThickness, objSize.z };

  bottom = new BoundingBox(bottomPos, bottomSize, objRotation, Color(1, 0, 1, 0.5f));
}

void Collision::InitializeTop() {
  Vector3 topPos = { objPos.x, objPos.y + objSize.y / 2 - collisionThickness / 2, objPos.z };
  Vector3 topSize = { objSize.x - 2, collisionThickness, objSize.z };

  top = new BoundingBox(topPos, topSize, objRotation, Color(1, 0, 1, 0.5f));
}

