#pragma once

#include "Geometries/TextureRect.h"
#include "Game/GameObject.h"
//#include "Level/Level.h"

class TestLevel : public Level {
 public:
  TestLevel();

  virtual void init();
  virtual void Update();
  virtual void Render();
 private:

  class HUD* playerHud = nullptr;
};