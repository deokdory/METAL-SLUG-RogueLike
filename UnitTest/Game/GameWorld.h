#pragma once
#include "Geometries/TextureRect.h"
#include "Level/Level.h"

#include "Level/SampleLevel/TestLevel.h"

class GameWorld {
 public:
  GameWorld();
  ~GameWorld();

  void update();
  void render();
  
 private:
  Level* level = nullptr;
};