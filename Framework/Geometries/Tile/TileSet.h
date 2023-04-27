#pragma once

class TileSet : public SingletonBase<TileSet>
{
public:
  friend class SingletonBase<TileSet>;
  friend class TileMap;

  void GUI();

  ID3D11ShaderResourceView* GetSRV() { return tileSRV; }

private:
  TileSet();
  ~TileSet();

  ID3D11ShaderResourceView* tileSRV = nullptr;

  UINT tileXCount = 0;
  UINT tileYCount = 0;

  Vector2 selectedStartUV = Values::ZeroVec2;
  Vector2 texelTileSize = Values::ZeroVec2;
};
