#include "Framework.h"
#include "TileSet.h"
#include "Tile.h"
#include "TileMap.h"

TileMap::TileMap(UINT width, UINT height, UINT spacing)
{
}

TileMap::~TileMap()
{
}

void TileMap::Update()
{
}

void TileMap::Render()
{
}

void TileMap::GUI()
{
}

void TileMap::GenerateTileMap()
{
}

void TileMap::MapVertexBuffer()
{
  DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void TileMap::UnmapVertexBuffer()
{
  memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
  DC->Unmap(vb->GetResource(), 0);
}

Tile* TileMap::GetTile(Vector3 position)
{
  UINT x = (int)position.x / spacing;
  UINT y = (int)position.y / spacing;

  if (x < 0 || x >= width || y < 0 || y >= height) return nullptr;
  else return &tiles[y][x];
}
