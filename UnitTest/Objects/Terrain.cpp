#include "stdafx.h"
#include "Terrain.h"

Terrain::Terrain(Vector3 position, Vector3 size, std::wstring path)
    : GameObject(position, size) {
  InitGraphic(TEXTURE_GRAPHIC);
  setGraphicResource(path);

  collision->InitializeBase();
  collision->InitializeBottom();
  collision->InitializeTop();

}

Terrain::~Terrain() { 
  SAFE_DELETE(collision);
}

void Terrain::update() { 
  graphic->update();
  collision->update();
}

void Terrain::render() { 
  graphic->render();
  collision->render();
}