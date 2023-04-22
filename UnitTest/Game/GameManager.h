#pragma once

class GameManager : public SingletonBase<GameManager> 
{
public:
  friend class SingletonBase<GameManager>;

  void SetCurrentLevel(class Level* level);
  class Level* GetCurrentLevel();

  void SetGlobalSpeed(float speed);
  float GetGlobalSpeed();

private:
  class Level* currentLevel = nullptr;
  float globalSpeed = 1.0f;
};