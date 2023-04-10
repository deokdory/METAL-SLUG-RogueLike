#pragma once
#include "Geometries/TextureRect.h"
#include "Level/Level.h"

class GameWorld {
 public:
  GameWorld();
  ~GameWorld();

  void update();
  void render(double interpolation);
  
 private:
   
};