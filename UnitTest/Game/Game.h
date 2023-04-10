#pragma once

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

  const UINT32 UPDATES_PER_SECOND = 30;
  const UINT32 MS_PER_UPDATE = 1000 / UPDATES_PER_SECOND;

  double prevTime = 0.0;
  double lag = 0.0;

};