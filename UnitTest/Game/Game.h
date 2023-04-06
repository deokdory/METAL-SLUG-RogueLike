#pragma once
#include "Geometries/TextureRect.h"

#define GRAVITY 100.f

class Game : public IObject {
 public:
  virtual void Init() override;
  virtual void Destroy() override;
  virtual void Update() override;
  virtual void Render() override;
  virtual void PostRender() override;
  virtual void GUI() override;

 private:
  class Player* player = nullptr;
  float gravity = GRAVITY;

  std::vector<class SamplePlate*> plates;
  TextureRect* background;
};