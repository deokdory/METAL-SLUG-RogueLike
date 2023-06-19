#pragma once
#include "Geometries/Tile/TileMap.h"

class Room
{
public:
  enum class Type { EMPTY, START, UPGRADE, BATTLE, ROOT, BOSS, ELIMINATE, ELEVATE, PASSAGE };
  
  Room(Type type, Room* prevRoom); // 랜덤 생성용 생성자

  Room(Type type, std::wstring mapDataFilePath, Room* prevRoom);
  Room(Type type); // TEST
  ~Room();

  void Update();
  void Render();
  void ForegroundRender();

private:
  void initTerrains(std::wstring mapDataFilePath);
  Vector3 tilePosToVector3(Terrain::Type trnType, UINT tilePositionX, UINT tilePositionY);
  Type type = Type::EMPTY;

  // 양쪽 입구 층수 ( 0 ~ 2 )
  UINT enterFloorL = 0;
  UINT enterFloorR = 0;

  Vector3 position = {};
  Vector3 size = {};

  UINT totalTileX = 0;
  UINT totalTileY = 0;

  std::vector<Terrain*> trnBackground;
  std::vector<Terrain*> trnMiddleground;
  std::vector<Terrain*> trnForeground;

  wstring mapDataFilePath = L"";

  // ENEMIES
  // PROPS
  // TRAPS
  // 
};