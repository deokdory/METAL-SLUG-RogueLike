#pragma once
#include "Component/Graphic/IGraphic.h"

class TexturedGraphic : public IGraphic {
public:
  TexturedGraphic(class GameObject* object);
  ~TexturedGraphic();

  virtual void Update();
  virtual void Render();

  virtual void SetResource(std::wstring path);

  virtual Matrix GetWorld(Slot slot = NONE);
  virtual Vector3 GetRectPosition(Slot slot = NONE) { return textureRect->GetPosition(); }
  virtual Vector3 GetRectSize(Slot slot = NONE);

private:
  class TextureRect* textureRect = nullptr;
};