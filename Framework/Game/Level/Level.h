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

  std::vector<Room*>& GetRooms() { return rooms; }
  std::vector<Terrain*>& GetTerrains() { return terrains; }
  std::vector<GameObject*>& GetObjects() { return objects; }
  std::vector<GameObject*>& GetObjectsForeground() { return objForeground; }

protected:
  void objectsUpdate(std::vector<GameObject*>& objects);
  void checkObjectsCurrentRoom(GameObject* object);

  std::vector<Room*> rooms;
  Room* playerCurrentRoom = nullptr;

  UINT levelWidth = 7;
  UINT levelHeight = 3;

  //std::vector<Background*> backgrounds;
  //std::vector<Decoration*> decos;

  GameObject* player = nullptr;

  std::vector<TextureRect*> backgrounds;
  std::vector<Terrain*> terrains;
  std::vector<GameObject*> objects;
  
  std::vector<GameObject*> objForeground;

};