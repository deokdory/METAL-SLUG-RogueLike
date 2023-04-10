#pragma once
#include "Geometries/TextureRect.h"
#include "Game/GameObject.h"

class GameWorld {
 public:
  GameWorld();
  ~GameWorld();

  void update();
  void render(double interpolation);
  
 private:
  std::vector<GameObject*> objects;
  
};