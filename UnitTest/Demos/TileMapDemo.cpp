#include "stdafx.h"
#include "TileMapDemo.h"

#include "Geometries/Tile/TileMap.h"

void TileMapDemo::Init()
{
  UINT spacing = 32;

  UINT width = WinMaxWidth / spacing;
  UINT height = WinMaxHeight / spacing;

  tm = new TileMap(width, height, spacing);
}

void TileMapDemo::Destroy()
{
  SAFE_DELETE(tm);
}

void TileMapDemo::Update()
{
  tm->Update();
}

void TileMapDemo::Render()
{
  tm->Render();
}

void TileMapDemo::PostRender()
{
}

void TileMapDemo::GUI()
{
  tm->GUI();
}
