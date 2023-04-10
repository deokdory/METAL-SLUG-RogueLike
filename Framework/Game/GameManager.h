#pragma once

class GameManager : public SingletonBase<GameManager> {
 public:
  friend class SingletonBase<GameManager>;

  const float GetGlobalSpeed() { return globalSpeed; }
  const float GetGravity() { return gravity; }

  void SetGlobalSpeed(float globalSpeed = 1.0f) { this->globalSpeed = globalSpeed; }
  void SetGravity(float gravity) { this->gravity = gravity; }
 private:
  GameManager(void);

  float globalSpeed;
  float gravity;
};