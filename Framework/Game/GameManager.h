#pragma once

class GameManager : public SingletonBase<GameManager> 
{
public:
  friend class SingletonBase<GameManager>;

  void SetCurrentLevel(class Level* level);
  class Level* GetCurrentLevel();

  float GetGlobalGravity();

private:
  class Level* currentLevel = nullptr;
  class Room* currentRoom = nullptr;

  float globalGravity = 0.25f;
};