#pragma once
#include "Component/Graphic/IGraphic.h"

class AnimatedGraphic : public IGraphic {
public:
  AnimatedGraphic(class GameObject* object);
  ~AnimatedGraphic();

  virtual void Update();
  virtual void Render();

  virtual void SetResource(class Animator* animator, Slot slot = NONE);

  virtual void SetCurrentAnimation(std::wstring name, Slot slot = NONE);
  virtual void SetCurrentFrame(UINT index, Slot slot = NONE);

private:
  class AnimationRect* animRect = nullptr;
  class Animator* animator = nullptr;
};