#include "Framework.h"
#include "TileSet.h"
#include "Tile.h"
#include "TileMap.h"

TileMap::TileMap(UINT width, UINT height, UINT spacing)
  : width(width), height(height), spacing(spacing)
{
  TileSet::Create();

  GenerateTileMap();
  
  vertices.assign(4, VertexTile());
  vertices[0].position = Values::ZeroVec3;
  vertices[1].position = Vector3(0.f, (float)spacing, 0.f);
  vertices[2].position = Vector3((float)spacing, 0.f, 0.f);
  vertices[3].position = Vector3((float)spacing, (float)spacing, 0.f);

  indices = { 0,1,2,2,1,3 };

  vb = new VertexBuffer();
  vb->Create(vertices, D3D11_USAGE_DYNAMIC);

  ib = new IndexBuffer();
  ib->Create(indices, D3D11_USAGE_IMMUTABLE);

  vs = new VertexShader();
  vs->Create(ShaderPath + L"Tile/VertexTile.hlsl", "VS");

  ps = new PixelShader();
  ps->Create(ShaderPath + L"Tile/VertexTile.hlsl", "PS");

  il = new InputLayout();
  il->Create(VertexTile::descs, VertexTile::count, vs->GetBlob());

  wb = new WorldBuffer();
  wb->SetWorld(world);

  inb = new IndexNumBuffer();
  inb->SetIndex(0);
}

TileMap::~TileMap()
{
  SAFE_DELETE(inb);
  SAFE_DELETE(wb);
  SAFE_DELETE(il);
  SAFE_DELETE(ps);
  SAFE_DELETE(vs);
  SAFE_DELETE(ib);
  SAFE_DELETE(vb);
  
  for (UINT y = 0; y < height; y++) SAFE_DELETE_ARRAY(tiles[y]);
  SAFE_DELETE_ARRAY(tiles);

  TileSet::Delete();
}

void TileMap::Update()
{
  Vector3 mousePos = Mouse::Get()->GetPosition();
  Tile* tile = GetTile(mousePos);

  if (tile) inb->SetIndex(tile->GetIndex());

  if (Mouse::Get()->Press(0))
  {
    if (tile)
    {
      tile->SetColor(Values::Red);
      
      Vector2 startUV = TileSet::Get()->selectedStartUV;
      Vector2 endUV = startUV + TileSet::Get()->texelTileSize;
      
      tile->SetStartUV(TileSet::Get()->selectedStartUV);
      tile->SetEndUV(endUV);
    }
  }
}

void TileMap::Render()
{
  vb->SetIA();
  ib->SetIA();
  il->SetIA();
  DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  vs->SetShader();
  ps->SetShader();

  DC->PSSetShaderResources(0, 1, &TileSet::Get()->tileSRV);

  for (UINT y = 0; y < height; y++)
  {
    for (UINT x = 0; x < width; x++)
    {
      Tile& tile = tiles[y][x];
      MapVertexBuffer();
      {
        for (VertexTile& v : vertices)
        {
          v.color = tile.GetColor();
          v.index = tile.GetIndex();
        }

        vertices[0].uv = Vector2(tile.GetStartUV().x, tile.GetEndUV().y);
        vertices[1].uv = tile.GetStartUV();
        vertices[2].uv = tile.GetEndUV();
        vertices[3].uv = Vector2(tile.GetEndUV().x, tile.GetStartUV().y);

        vertices[0].uv2 = Vector2(0.f, 1.f);
        vertices[1].uv2 = Vector2(0.f, 0.f);
        vertices[2].uv2 = Vector2(1.f, 1.f);
        vertices[3].uv2 = Vector2(1.f, 0.f);
      }
      UnmapVertexBuffer();

      world = DXMath::Translation(tile.GetPosition());

      wb->SetWorld(world);
      wb->SetVSBuffer(0);
      inb->SetPSBuffer(0);

      DC->DrawIndexed(ib->GetCount(), 0, 0);
    }
  }
}

void TileMap::GUI()
{
  TileSet::Get()->GUI();

  Vector3 mousePos = Mouse::Get()->GetPosition();

  ImGui::Begin("TileMap");
  ImGui::RadioButton("Normal", (int*)&mode, 0);
  ImGui::End();

  ImGui::Begin("Color Choice");
  ImGui::RadioButton("Default", (int*)&choice, 0);
  ImGui::End();

  ImGui::Begin("Index");
  ImGui::Text(std::to_string(GetTile(mousePos)->GetIndex()).c_str());
  ImGui::End();
}

void TileMap::GenerateTileMap()
{
  if (width == 0 || height == 0 || spacing == 0)
    assert(false);

  tiles = new Tile*[height];
  int index = 0;

  for (UINT y = 0; y < height; y++)
  {
    tiles[y] = new Tile[width];

    for (UINT x = 0; x < width; x++)
    {
      tiles[y][x].SetPosition(Vector3((float)(x * spacing), (float)(y * spacing), 0));
      tiles[y][x].SetIndex(index++);
    }
  }
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
