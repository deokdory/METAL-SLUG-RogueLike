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

  if (Keyboard::Get()->Down(VK_F7)) Save(TilePath + L"TileData.txt");
  if (Keyboard::Get()->Down(VK_F8)) Load(TilePath + L"TileData.txt");

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

  std::string index = "";
  if (GetTile(mousePos)) index += std::to_string(GetTile(mousePos)->GetIndex());
  ImGui::Text(index.c_str());
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

void TileMap::Save(wstring path)
{
  std::ofstream fout(path);

  fout << to_string(width) << ' ' << to_string(height) << ' ' << to_string(spacing) << std::endl;

  for (UINT y = 0; y < height; y++)
  {
    for (UINT x = 0; x < width; x++)
    {
      Tile& tile = tiles[y][x];
      std::string output;

      output += std::to_string(tile.GetStartUV().x) + ' ' + std::to_string(tile.GetStartUV().y) + ' ';
      output += std::to_string(tile.GetEndUV().x) + ' ' + std::to_string(tile.GetEndUV().y);

      fout << output << endl;
    }
  }
}

void TileMap::Load(wstring path)
{
  std::ifstream fin(path);

  if (fin.fail())
  {
    std::cout << "Wrong File" << std::endl;
    return;
  }
  
  for(UINT y = 0; y < height; y++) SAFE_DELETE_ARRAY(tiles[y]);
  SAFE_DELETE_ARRAY(tiles);

  char temp[256];
  fin.getline(temp, 256);
  std::string t = "";

  // Reading width, height, spacing
  for (int i = 0; i < 256; i++)
  {
    if (temp[i] != ' ' && temp[i] != '\0')
      t = temp[i];
    else
    {
      if (width == 0)
      {
        width = std::stoi(t); // string to int
        t.clear();
      }
      else if (height == 0)
      {
        height = std::stoi(t);
        t.clear();
      }
      else if (spacing == 0)
      {
        spacing = std::stoi(t);
      }
      continue;
    }
  }

  if (width == 0 || height == 0 || spacing == 0) assert(false);

  tiles = new Tile * [height];
  int count = 0;

  for (UINT y = 0; y < height; y++)
  {
    tiles[y] = new Tile[width];
    for (UINT x = 0; x < width; x++)
    {
      float vx = (float)(x * spacing);
      float vy = (float)(y * spacing);
      tiles[y][x].SetPosition(Vector3(vx, vy, 0.0f));
      tiles[y][x].SetIndex(count++);

      fin.getline(temp, 256);
      Vector2 uv;
      std::string t;

      int flag = 0;
      for (int i = 0; i < 256; i++)
      {
        if ((i + 1) % 9 == 0)
        {
          switch (flag)
          {
          case 0:
          {
            uv.x = std::stof(t);
            ++flag;
            break;
          }
          case 1:
          {
            uv.y = std::stof(t);
            ++flag;
            tiles[y][x].SetStartUV(uv);
            break;
          }
          case 2:
          {
            uv.x = std::stof(t);
            ++flag;
            break;
          }
          case 3:
          {
            uv.y = std::stof(t);
            ++flag;
            tiles[y][x].SetEndUV(uv);
            break;
          }
          default:
            break;
          }
          t.clear();
          continue;
        }
        else t += temp[i];
      }
    }
  }
}

Tile* TileMap::GetTile(Vector3 position)
{
  UINT x = (int)position.x / spacing;
  UINT y = (int)position.y / spacing;

  if (x < 0 || x >= width || y < 0 || y >= height) return nullptr;
  else return &tiles[y][x];
}
