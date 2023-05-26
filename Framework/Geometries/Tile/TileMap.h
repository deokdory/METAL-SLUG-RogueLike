#pragma once
#include "TileSet.h"
#include "Tile.h"

enum class EDrawingMode
{
  Normal
};

enum class ColorChoice
{
  Default
};

class IndexNumBuffer : public ShaderBuffer
{
public:
  struct Data
  {
    UINT index;
    Vector3 dummy;
  };

  IndexNumBuffer() : ShaderBuffer(&data, sizeof(data))
  {
    data.index = 0;
  }

  void SetIndex(UINT index) { data.index = index; }

private:
  Data data;
};

class TileMap
{
public:
  TileMap(UINT width, UINT height, UINT spacing);
  ~TileMap();

  void Update();
  void Render();
  void GUI();

  void GenerateTileMap();
  void mapVertexBuffer();
  void unmapVertexBuffer();

  void Save();
  void Load();

  Tile* GetTile(Vector3 position);

private:
  UINT width = 0;
  UINT height = 0;
  UINT spacing = 0;

  UINT vertexCount = 0;
  UINT indexCount = 0;

  std::vector<VertexTile> vertices;
  VertexBuffer* vb = nullptr;
  D3D11_MAPPED_SUBRESOURCE subResource;

  std::vector<UINT> indices;
  IndexBuffer* ib = nullptr;

  VertexShader* vs = nullptr;
  PixelShader* ps = nullptr;

  InputLayout* il = nullptr;

  Matrix world = Values::Identity;
  WorldBuffer* wb = nullptr;

  IndexNumBuffer* inb = nullptr;

  class Tile** tiles = nullptr;

  EDrawingMode mode = EDrawingMode::Normal;
  ColorChoice choice = ColorChoice::Default;

  ID3D11SamplerState* sampler;
  ID3D11BlendState* blend;

  TileSet* tileSet = nullptr;
};