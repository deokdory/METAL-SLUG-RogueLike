#pragma once

class Room
{
public:
  enum MapDataNum
  {
    EMPTY = 0,
    FOOTHOLDER,
    FOOTHOLDER_WITH_DECO,
    STAIR_NORMAL_UP,
    STAIR_NORMAL_DOWN,
    STAIR_LONG_UP,
    STAIR_LONG_DOWN
  };

  enum class Type { EMPTY, UPGRADE, BATTLE, ROOT, BOSS, ELIMINATE, ELEVATE, PASSAGE };
  enum class Layer { BACKGROUND, MIDDLEGROUND, FOREGROUND, STAIRS };

  // ������ �� ����, ����Ǵ� ���� ��, ����Ǵ� ����
  Room(Type type, Room* prevRoom, Direction direction);

  // �� ������ ���� �����Ͽ� ����
  Room(Type type, std::wstring mapDataFilePath, Room* prevRoom, Direction direction);

  // ��� ���� ( 0��, 1��, 2�� Ȥ�� -1(��� ��)
  Room(int enterFloorL, int enterFloorR);

  Room(Type type); // TEST
  ~Room();

  void Update();
  void Render();
  void ForegroundRender();

  Vector3 GetPosition() { return this->position; }
  Vector3 GetSize() { return this->size; }

  UINT GetEnterFloor(bool isLeft) { return isLeft ? enterFloorL : enterFloorR; }

  void SetLinkedRoom(Direction direction, Room* linkedRoom);
  Room* GetLinkedRoom(Direction direction);

  BoundingBox* GetArea() { return area; }
  Type GetRoomType() { return type; }

  std::vector<Terrain*>& GetTerrains(Layer layer);

  void SetIsActived(bool isActived);
  bool GetIsActived() { return isActived; }

  int GetFloor() { return floor; }

private:
  Color setAreaColor(Type type);

  bool initTerrains(std::wstring mapDataFilePath, Room* prevRoom = nullptr, Direction direction = Direction::NONE);

  void setRoomPosition(Room* prevRoom, Direction direction);
  void setFloorFromPrevRoom(Room* prevRoom, Direction direction);
  void setEnterFloor(UINT tilePositionX, UINT tilePositionY);

  Type type = Type::EMPTY;

  // ���� �Ա� ���� ( 0 ~ 2 )
  int enterFloorL = -1;
  int enterFloorR = -1;

  Vector3 position = Values::ZeroVec3;
  Vector3 size = Values::ZeroVec3;

  UINT totalTileX = 0;
  UINT totalTileY = 0;
  
  GameObject* elevator = nullptr;

  std::vector<TextureRect*> decorations;

  std::vector<Terrain*> trnBackground;
  std::vector<Terrain*> trnMiddleground;
  std::vector<Terrain*> trnForeground;

  std::vector<Terrain*> trnStairs;

  wstring mapDataFilePath = L"";

  Room* linkedRoomLeft = nullptr;
  Room* linkedRoomRight = nullptr;
  Room* linkedRoomUp = nullptr;
  Room* linkedRoomDown = nullptr;

  BoundingBox* area = nullptr;
  bool isActived = false;

  int floor = 0;

  // ENEMIES
  // PROPS
  // TRAPS
  // 
};