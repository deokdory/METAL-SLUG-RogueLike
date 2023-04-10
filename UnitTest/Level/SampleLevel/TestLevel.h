#pragma once

#include "Geometries/TextureRect.h"
#include "Game/GameObject.h"
#include "Level/Level.h"

class TestLevel : public Level {
 public:
  TestLevel();

 private:
  virtual void init();
  virtual void update();
  virtual void render();
};