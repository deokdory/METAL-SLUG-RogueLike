#pragma once
#include "Game/GameObject.h"

class Terrain : public GameObject {
 public:
   Terrain(Vector3 position, Vector3 size, std::wstring path);
  ~Terrain();

  virtual void Update();
  virtual void Render();

};