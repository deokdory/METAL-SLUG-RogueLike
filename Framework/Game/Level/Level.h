#pragma once
#include "Objects/Terrain.h"
#include "Game/Level/Room/Room.h"

class Level {
public:

  Level();
  virtual ~Level();

  virtual void init();
  virtual void Update();
  virtual void Render();
  virtual void GUI();

  void PushObject(GameObject* object) { objects.push_back(object); }

  std::vector<Terrain*>& GetTerrains() { return terrains; }
  std::vector<GameObject*>& GetObjects() { return objects; }

protected:
  std::vector<Room*> rooms;

  UINT levelWidth = 7;
  UINT levelHeight = 5;

  //std::vector<Background*> backgrounds;
  //std::vector<Decoration*> decos;

  GameObject* player = nullptr;

  std::vector<Terrain*> terrains;
  std::vector<GameObject*> objects;
  
};