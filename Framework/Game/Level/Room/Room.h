#pragma once
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

  // ENEMIES
  // PROPS
  // TRAPS
  // 
};