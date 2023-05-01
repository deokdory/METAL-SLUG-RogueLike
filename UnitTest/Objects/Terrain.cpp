#include "stdafx.h"
#include "Terrain.h"

#include "Component/Collision/Collision.h"
#include "Component/Graphic/ObjectGraphic.h"

Terrain::Terrain(Vector3 position, Vector3 size, std::wstring path)
    : GameObject(position, size) {

  type = Type::TERRAIN;

  collision->InitializeBase();
  collision->InitializeBottom();
  collision->InitializeTop();

  graphic->InitTexture(path);
  //Update();
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