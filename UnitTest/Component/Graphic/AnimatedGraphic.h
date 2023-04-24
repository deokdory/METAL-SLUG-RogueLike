#pragma once
#include "Component/Graphic/IGraphic.h"

class AnimatedGraphic : public ObjectGraphic {
public:
  AnimatedGraphic(class GameObject* object);
  ~AnimatedGraphic();

  virtual void Update();
  virtual void Render();

  virtual class Animator* GetAnimator(Slot slot = NORMAL) { return animator; }

  virtual void SetResource(class Animator* animator, Slot slot = NORMAL);

  virtual void SetCurrentAnimation(std::wstring name, Slot slot = NORMAL);
  virtual void SetCurrentFrame(UINT index, Slot slot = NORMAL);

  virtual Matrix GetRectWorld(Slot slot = NORMAL);
  virtual Vector3 GetRectPosition(Slot slot = NORMAL) { return animRect->GetPosition(); }
  virtual Vector3 GetRectSize(Slot slot = NORMAL);

private:
  class AnimationRect* animRect = nullptr;
  class Animator* animator = nullptr;
};