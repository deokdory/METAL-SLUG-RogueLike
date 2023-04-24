#pragma once

class GameManager : public SingletonBase<GameManager> 
{
public:
  friend class SingletonBase<GameManager>;

  void SetCurrentLevel(class Level* level);
  class Level* GetCurrentLevel();

  void SetGlobalSpeed(float speed);
  float GetGlobalSpeed();

  float GetGlobalGravity();

private:
  class Level* currentLevel = nullptr;
  float globalSpeed = 1.0f;

  float globalGravity = 0.15f;
};