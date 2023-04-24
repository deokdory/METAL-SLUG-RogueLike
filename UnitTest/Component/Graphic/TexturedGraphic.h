#pragma once
#include "Component/Graphic/IGraphic.h"

class TexturedGraphic : public ObjectGraphic {
public:
  TexturedGraphic(class GameObject* object);
  ~TexturedGraphic();

  virtual void Update();
  virtual void Render();

  virtual void SetResource(std::wstring path);

  virtual Matrix GetRectWorld(Slot slot = NORMAL);
  virtual Vector3 GetRectPosition(Slot slot = NORMAL) { return textureRect->GetPosition(); }
  virtual Vector3 GetRectSize(Slot slot = NORMAL);

private:
  class TextureRect* textureRect = nullptr;
};