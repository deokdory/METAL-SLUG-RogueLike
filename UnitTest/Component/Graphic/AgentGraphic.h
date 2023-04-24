#pragma once
#include "Component/Graphic/IGraphic.h"

class AgentGraphic : public ObjectGraphic {
public:
  AgentGraphic(class GameObject* object);
  ~AgentGraphic();

  virtual void Update();
  virtual void Render();

  virtual void SetResource(class Animator* animator, Slot slot = NORMAL);

  virtual class Animator* GetAnimator(Slot slot);

  virtual void SetCurrentAnimation(std::wstring name, Slot slot = NORMAL);
  virtual void SetCurrentFrame(UINT index, Slot slot = NORMAL);
  
  virtual Matrix GetRectWorld(Slot slot = NORMAL);
  virtual Vector3 GetRectPosition(Slot slot = NORMAL);
  virtual Vector3 GetRectSize(Slot slot = NORMAL);

private:
  class AnimationRect* lowerRect = nullptr;
  class AnimationRect* upperRect = nullptr;

  class Animator* lowerAnim = nullptr;
  class Animator* upperAnim = nullptr;
};