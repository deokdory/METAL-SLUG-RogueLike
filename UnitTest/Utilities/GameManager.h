#pragma once

class GameManager : public SingletonBase<GameManager> 
{
public:
  friend class SingletonBase<GameManager>;

  void Update();
  void GUI();

  void SetCurrentLevel(class Level* level);

  class Level* GetCurrentLevel();
  class Room* GetPlayerCurrentRoom();

  float GetGlobalGravity();

  void SetPlayer(class Agent* player);
  class Agent* GetPlayer();

  int GetPlayerLastStandedFloor() { return playerCurrentFloor; }

private:

  class Agent* player = nullptr;

  class Level* currentLevel = nullptr;
  class Room* playerCurrentRoom = nullptr;

  int topFloor = 0;
  int bottomFloor = 0;

  float globalGravity = 0.25f;

  class Terrain* lastStandedTerrain = nullptr;
  int playerCurrentFloor = -1;

};