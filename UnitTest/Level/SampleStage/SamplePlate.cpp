#include "stdafx.h"
#include "SamplePlate.h"

SamplePlate::SamplePlate(Vector3 pos, Vector3 size, float rotation) {
  rect = new TextureRect(pos, size, rotation, TexturePath + L"SamplePlate.png");
  collision = new BoundingBox();
  collision->Init(Color(1, 1, 0, 0.3f));
}

SamplePlate::~SamplePlate() {
  SAFE_DELETE(rect);
  SAFE_DELETE(collision);
}

void SamplePlate::Update() { 
  collision->UpdateCollisionData(rect->GetWorld(),
                                 rect->GetVerticesLocalPosition());
  collision->Update(rect->GetSize(), Values::ZeroVec3, rect->GetRotation());
  rect->Update(); 
}

void SamplePlate::Render() {
  rect->Render();
  collision->Render();
}
