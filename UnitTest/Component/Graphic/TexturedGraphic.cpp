#include "stdafx.h"
#include "TexturedGraphic.h"

//#include "Geometries/TextureRect.h"
//#include "Geometries/AnimationRect.h"

#include "Component/Graphic/IGraphic.h"

#include "Game/GameObject.h"

TexturedGraphic::TexturedGraphic(GameObject* object)
  : IGraphic(object) {}

TexturedGraphic::~TexturedGraphic() {
  SAFE_DELETE(textureRect);
}

void TexturedGraphic::Update() {
  if (textureRect) {
    if (object->GetFliped()) textureRect->SetIsFliped(true);
    else textureRect->SetIsFliped(false);

    textureRect->SetPosition(object->GetPosition());
    textureRect->SetSize(object->GetSize());
    textureRect->SetRotation(object->GetRotation());

    textureRect->Update();
  }
}

void TexturedGraphic::Render() { if (textureRect) textureRect->Render(); }

void TexturedGraphic::SetResource(std::wstring path) {
  SAFE_DELETE(textureRect);
  textureRect = new TextureRect(object->GetPosition(), object->GetSize(),
    object->GetRotation(), path);
}

Matrix TexturedGraphic::GetWorld(Slot slot)
{
  return textureRect->GetWorld();
}

Vector3 TexturedGraphic::GetRectSize(Slot slot)
{
  return textureRect->GetSize();
}