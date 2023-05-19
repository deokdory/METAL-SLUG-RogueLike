#pragma once

class TileSet
{
public:
  friend class TileMap;

  bool GUI();

  ID3D11ShaderResourceView* GetSRV() { return tileSRV; }

private:
  TileSet(std::wstring filePath, UINT tileXCount, UINT tileYCount);
  ~TileSet();

  std::string themeName = "NONE";

  ID3D11ShaderResourceView* tileSRV = nullptr;

  UINT tileXCount = 0;
  UINT tileYCount = 0;

  Vector2 selectedStartUV = Values::ZeroVec2;
  Vector2 tileUV = Values::ZeroVec2;

  Vector2 singlePixelUV = {};
};
