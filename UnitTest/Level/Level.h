#pragma once
#include "Geometries/TextureRect.h"
#include "Game/GameObject.h"

class Level {
  virtual void update() = 0;
  virtual void render() = 0;

  protected:
  std::vector<TextureRect*> backgrounds;
  std::vector<Terrain*> terrains;
  std::vector<Decorations*> decos;
  std::vector<GameObject*> objects;
};