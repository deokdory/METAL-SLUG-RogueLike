#pragma once
#include "Game/Level/Level.h"
#include "Geometries/TextureRect.h"

class TestLevel : public Level {
 public:
  TestLevel();

  virtual void init();
  virtual void Update();
  virtual void Render();

  void InitTestEnemies();
 private:

  class HUD* playerHud = nullptr;
};