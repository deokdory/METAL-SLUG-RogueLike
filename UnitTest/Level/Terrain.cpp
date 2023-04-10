#include "stdafx.h"
#include "Terrain.h"

Terrain::Terrain(Vector3 position, Vector3 size, float rotation,
                 std::wstring path) 
: position(position), size(size), rotation(rotation) {

  textureRect = new TextureRect(position, size, rotation, path);
  collision = new BoundingBox(position, size, rotation, Color(1, 1, 0, 1.3f));

  textureRect->Update();
  collision->Update(position, size, rotation);
}

void Terrain::update() {}

void Terrain::render() {
  textureRect->Render();
  collision->Render();
}