#pragma once
#include "Component/Graphic/IGraphic.h"

class TexturedGraphic : public IGraphic {
public:
  TexturedGraphic(class GameObject* object);
  ~TexturedGraphic();

  virtual void Update();
  virtual void Render();

  virtual void SetResource(std::wstring path);

private:
  class TextureRect* textureRect = nullptr;
};