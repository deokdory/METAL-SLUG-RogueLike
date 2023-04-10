#pragma once
#include "Geometries/TextureRect.h"

class Terrain {
 public:
  Terrain();
  ~Terrain();

  private:
  TextureRect* textureRect;
  BoundingBox* collision;
};