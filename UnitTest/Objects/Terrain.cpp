#include "stdafx.h"
#include "Terrain.h"

#include "Component/Collision/Collision.h"
#include "Component/Graphic/TexturedGraphic.h"

Terrain::Terrain(Vector3 position, Vector3 size, std::wstring path)
    : GameObject(position, size) {
  InitGraphic(ObjectGraphic::Type::TEXTURE_GRAPHIC);
  SetGraphicResource(path);

  collision->InitializeBase();
  collision->InitializeBottom();
  collision->InitializeTop();

}

Terrain::~Terrain() { 
  SAFE_DELETE(collision);
}

void Terrain::Update() { 
  graphic->Update();
  collision->Update();
}

void Terrain::Render() { 
  graphic->Render();
  collision->Render();
}