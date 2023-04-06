#pragma once

class GameManager : public SingletonBase<GameManager> {
 public:
  friend class SingletonBase<GameManager>;

  float GetGlobalSpeed() const { return globalSpeed; }
  void SetGlobalSpeed(float globalSpeed) { this->globalSpeed = globalSpeed; }

 private:
  GameManager(void);

  float globalSpeed;
};