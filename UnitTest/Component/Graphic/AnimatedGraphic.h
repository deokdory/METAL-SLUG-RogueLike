#pragma once
#include "Component/Graphic/IGraphic.h"

class AnimatedGraphic : public IGraphic {
public:
  AnimatedGraphic(class GameObject* object);
  ~AnimatedGraphic();

  virtual void Update();
  virtual void Render();

  virtual class Animator* GetAnimator(Slot slot = NONE) { return animator; }

  virtual void SetResource(class Animator* animator, Slot slot = NONE);

  virtual void SetCurrentAnimation(std::wstring name, Slot slot = NONE);
  virtual void SetCurrentFrame(UINT index, Slot slot = NONE);

  virtual Matrix GetWorld(Slot slot = NONE);
  virtual Vector3 GetRectPosition(Slot slot = NONE) { return animRect->GetPosition(); }

private:
  class AnimationRect* animRect = nullptr;
  class Animator* animator = nullptr;
};