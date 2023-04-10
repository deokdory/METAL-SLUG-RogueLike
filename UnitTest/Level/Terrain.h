#pragma once
#include "Geometries/TextureRect.h"

class Terrain {
 public:
  Terrain(Vector3 position, Vector3 size, float rotation, std::wstring path);
  ~Terrain();

  virtual void update();
  virtual void render();

  private:
  TextureRect* textureRect;
  BoundingBox* collision;

  Vector3 position;
  Vector3 size;
  float rotation;
};