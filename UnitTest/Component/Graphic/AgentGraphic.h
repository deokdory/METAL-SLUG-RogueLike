#pragma once
#include "Component/Graphic/IGraphic.h"

class AgentGraphic : public IGraphic {
public:
  AgentGraphic(class GameObject* object);
  ~AgentGraphic();

  virtual void Update();
  virtual void Render();

  virtual void SetResource(class Animator* animator, Slot slot = NONE);

  virtual void SetCurrentAnimation(std::wstring name, Slot slot = NONE);
  virtual void SetCurrentFrame(UINT index, Slot slot = NONE);
  
private:
  class AnimationRect* lowerRect = nullptr;
  class AnimationRect* upperRect = nullptr;

  class Animator* lowerAnim = nullptr;
  class Animator* upperAnim = nullptr;
};