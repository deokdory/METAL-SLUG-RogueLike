#pragma once
#include "Geometries/Tile/TileMap.h"

#define ROOM_TILE_X 25
#define ROOM_TILE_Y 15

class Room
{
public:
  enum class Type { EMPTY, STORE, BATTLE, ROOT, BOSS, ELIMINATE };

  Room();
  ~Room();

private:
  Type type = Type::EMPTY;
  bool isEntrance[4] = {}; // Direction

  std::vector<GameObject*> tileBackground;
  std::vector<GameObject*> tileMiddleground;
  std::vector<GameObject*> tileForeground;

 

  // ENEMIES
  // PROPS
  // TRAPS
  // 
};