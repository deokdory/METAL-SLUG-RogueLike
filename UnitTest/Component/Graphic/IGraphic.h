#pragma once
class IGraphic {
 public:
   enum Slot { NONE = 0, LOWER, UPPER, MERGED };
   enum Type { TEXTURE_GRAPHIC = 0, ANIMATION_GRAPHIC, AGENT_GRAPHIC };

  IGraphic(class GameObject* object);
  virtual ~IGraphic();

  virtual void Update() = 0;
  virtual void Render() = 0;

  virtual void SetResource(class Animator* animator, Slot slot = NONE ) {}
  virtual void SetResource(std::wstring path) {}

  virtual void SetCurrentAnimation(std::wstring name, Slot slot = NONE) {}
  virtual void SetCurrentFrame(UINT index, Slot slot = NONE) {}


  protected:
  class GameObject* object = nullptr;
};