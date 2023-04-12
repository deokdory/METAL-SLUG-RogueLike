#pragma once
#include "Game/GameObject.h"

class Terrain : public GameObject {
 public:
  Terrain(Vector3 position, Vector3 size, std::wstring path);
  ~Terrain();

  virtual void update();
  virtual void render();

  Vector3 getPosition() { return position; }
  Vector3 getSize() { return size; }
  float getRotation() { return rotation; }
};