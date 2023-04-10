#pragma once
#include "Geometries/TextureRect.h"

class SamplePlate {
 public:
  SamplePlate(Vector3 pos, Vector3 size, float rotation);
  ~SamplePlate();

  void Update();
  void Render();

  BoundingBox* GetCollision() { return collision; }

  Vector3 GetPosition() { return rect->GetPosition(); }
  Vector3 GetSize() { return rect->GetSize(); }
  float GetRotation() { return rect->GetRotation(); }

 private:
  class TextureRect* rect;
  class BoundingBox* collision;
};