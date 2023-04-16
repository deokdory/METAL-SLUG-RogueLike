#pragma once
#include "Game/GameObject.h"

class Terrain : public GameObject {
 public:
  Terrain(Vector3 position, Vector3 size, std::wstring path);
  ~Terrain();

  virtual void Update();
  virtual void Render();

  Vector3 GetPosition() { return position; }
  Vector3 GetSize() { return size; }
  float GetRotation() { return rotation; }
};