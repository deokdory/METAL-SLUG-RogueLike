#pragma once
#include "Objects/Terrain.h"

class Level {
 public:
  virtual ~Level();

  virtual void init();
  virtual void Update();
  virtual void Render();
  virtual void GUI();

  void PushObject(GameObject* object) { objects.push_back(object); }

  std::vector<Terrain*>& GetTerrains() { return terrains; }
  std::vector<GameObject*>& GetObjects() { return objects; }
  
  protected:
  //std::vector<Background*> backgrounds;
  //std::vector<Decoration*> decos;
  
  std::vector<Terrain*> terrains;
  std::vector<GameObject*> objects;
};