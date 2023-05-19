#pragma once

class Tile
{
public:
  void SetPosition(Vector3 position) { this->position = position; }
  void SetTilePosition(Vector2 tilePosition) { this->tilePosition = tilePosition; }

  void SetStartUV(Vector2 startUV) { this->startUV = startUV; }
  void SetEndUV(Vector2 endUV) { this->endUV = endUV; }

  void SetColor(Color color) { this->color = color; }
  void SetIndex(UINT index) { this->index = index; }
  void SetTheme(std::string themeName) { this->themeName = themeName; }
  void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }


  Vector3 GetPosition() { return position; }
  Vector2 GetTilePosition() { return tilePosition; }

  Vector2 GetStartUV() { return startUV; }
  Vector2 GetEndUV() { return endUV; }

  Color GetColor() { return color; }
  UINT GetIndex() { return index; }
  std::string GetTheme() { return themeName; }
  ID3D11ShaderResourceView* GetSRV() { return srv; }

  virtual void Interaction(GameObject* object) {}
  
private:
  std::string themeName = "";

  Vector3 position = Values::ZeroVec3;

  Vector2 tilePosition = {};

  Color color = {};

  Vector2 startUV = Values::ZeroVec2;
  Vector2 endUV = Values::ZeroVec2;

  ID3D11ShaderResourceView* srv = nullptr;

  Collision* collision = nullptr;

  UINT index = -1;
};