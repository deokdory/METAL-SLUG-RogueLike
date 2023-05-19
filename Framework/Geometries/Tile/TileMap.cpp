#include "Framework.h"
#include "TileMap.h"

TileMap::TileMap(UINT width, UINT height, UINT spacing)
  : width(width), height(height), spacing(spacing)
{
  tileSet = new TileSet(TexturePath + L"Tiles.png", 6, 9);
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

  // Point sampling
  {
    D3D11_SAMPLER_DESC desc;
    States::GetSamplerDesc(&desc);
  
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    States::CreateSamplerState(&desc, &sampler);
  }

  // Blend
  {
    D3D11_BLEND_DESC desc;
    States::GetBlendDesc(&desc);

    desc.RenderTarget[0].BlendEnable = true;
    States::CreateBlendState(&desc, &blend);
  }
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

  SAFE_DELETE(tileSet);
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

        Vector2 startUV = tileSet->selectedStartUV;
        Vector2 endUV = startUV + tileSet->tileUV;

        tile->SetStartUV(tileSet->selectedStartUV);
        tile->SetEndUV(endUV);
    }
  }

  else if (Mouse::Get()->Press(1))
  {
    if (tile)
    {
      tile->SetColor({});
      tile->SetTheme("");
      tile->SetStartUV(Vector2(-1, -1));
      tile->SetEndUV(Vector2(-1, -1));
    }
  }

  if (Keyboard::Get()->Down(VK_F7)) Save();
  if (Keyboard::Get()->Down(VK_F8)) Load();

}

void TileMap::Render()
{
  DC->PSSetSamplers(0, 1, &sampler);
  DC->OMSetBlendState(blend, nullptr, (UINT)0xFFFFFFFFFF);

  vb->SetIA();
  ib->SetIA();
  il->SetIA();
  DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  vs->SetShader();
  ps->SetShader();

  ID3D11ShaderResourceView* srv = tileSet->tileSRV;
  DC->PSSetShaderResources(0, 1, &srv);

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
  Vector3 mousePos = Mouse::Get()->GetPosition();
  tileSet->GUI();

  //ImGui::Begin("TileMap");
  //ImGui::RadioButton("Normal", (int*)&mode, 0);
  //ImGui::End();
  //
  //ImGui::Begin("Color Choice");
  //ImGui::RadioButton("Default", (int*)&choice, 0);
  //ImGui::End();
  //
  ImGui::Begin("TilePosition");
  std::string tilePosStr = "";

  Tile* tile = GetTile(mousePos);
  if (tile != nullptr) {
    Vector2 tilePosition = tile->GetTilePosition();
    tilePosStr += std::to_string((int)tilePosition.x) + " x " + std::to_string((int)tilePosition.y);
  }

  ImGui::Text(tilePosStr.c_str());
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
      tiles[y][x].SetTilePosition(Vector2(x, y));
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

void TileMap::Save()
{
  nfdchar_t* nfdPath = NULL;
  nfdresult_t result = NFD_SaveDialog("txt", NULL, &nfdPath);

  if (result == NFD_OKAY)
  {
    puts(nfdPath);

    std::string path = "";
    path = nfdPath;
    free(nfdPath);

    String::Replace(&path, "\\", "/");

    std::string extension = Path::GetExtension(path);
    if (extension != "txt")
      path += ".txt";

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
  else if (result == NFD_CANCEL)
  {
    puts("User pressed cancel.");
  }
  else
  {
    std::cout << "Error::" << NFD_GetError();
  }
}

void TileMap::Load()
{
  nfdchar_t* nfdPath = NULL;
  nfdresult_t result = NFD_OpenDialog("txt", NULL, &nfdPath);

  if (result == NFD_OKAY)
  {
    puts("Success!");
    std::string path = "";
    path = nfdPath;
    free(nfdPath);

    String::Replace(&path, "\\", "/");

    std::ifstream fin(path);

    if (fin.fail())
    {
      std::cout << "Wrong File" << std::endl;
      return;
    }

    for (UINT y = 0; y < height; y++) SAFE_DELETE_ARRAY(tiles[y]);
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
        tiles[y][x].SetTilePosition(Vector2(x, y));

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
  else if (result == NFD_CANCEL)
  {
    puts("User pressed cancel.");
  }
  else
  {
    std::cout << "Error::" << NFD_GetError();
  }
}

Tile* TileMap::GetTile(Vector3 position)
{
  UINT x = (int)position.x / spacing;
  UINT y = (int)position.y / spacing;

  if (x < 0 || x >= width || y < 0 || y >= height) return nullptr;
  else return &tiles[y][x];
}
