#pragma once
#include "GameWorld.h"

class Game : public IObject {
 public:
  virtual void Init() override;
  virtual void Destroy() override;
  virtual void Update() override;
  virtual void Render() override;
  virtual void PostRender() override;
  virtual void GUI() override;

 private:
  GameWorld* gameWorld = nullptr;

  const UINT32 UPDATES_PER_SECOND = 120;
  const double MS_PER_UPDATE = 1.0 / UPDATES_PER_SECOND;

  double prevTime = 0.0;
  double elapsedTotal = 0.0;
};