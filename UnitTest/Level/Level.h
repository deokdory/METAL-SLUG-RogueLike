#pragma once
#include "Geometries/TextureRect.h"
#include "Game/GameObject.h"
#include "Level/Decoration.h"
#include "Level/Terrain.h"
#include "Level/Background.h"

class Level {
 public:
  virtual ~Level();

  virtual void init() = 0;
  virtual void update() = 0;
  virtual void render() = 0;

  std::vector<Terrain*>& GetTerrains() { return terrains; }
  std::vector<GameObject*>& GetObjects() { return objects; }
  
  protected:
  std::vector<Background*> backgrounds;
  std::vector<Decoration*> decos;

  std::vector<Terrain*> terrains;
  std::vector<GameObject*> objects;
};