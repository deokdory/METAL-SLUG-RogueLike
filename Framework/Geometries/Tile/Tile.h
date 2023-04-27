#pragma once

class Tile
{
public:
  void SetPosition(Vector3 position) { this->position = position; }
  void SetStartUV(Vector2 startUV) { this->startUV = startUV; }
  void SetEndUV(Vector2 endUV) { this->endUV = endUV; }
  void SetColor(Color color) { this->color = color; }
  void SetIndex(UINT index) { this->index = index; }
  void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }

  Vector3 GetPosition() { return position; }
  Vector2 GetStartUV() { return startUV; }
  Vector2 GetEndUV() { return endUV; }
  Color GetColor() { return color; }
  UINT GetIndex() { return index; }
  ID3D11ShaderResourceView* GetSRV() { return srv; }
  
private:
  Vector3 position = Values::ZeroVec3;
  Color color = Values::Black;

  Vector2 startUV = Values::ZeroVec2;
  Vector2 endUV = Values::ZeroVec2;

  ID3D11ShaderResourceView* srv = nullptr;

  UINT index = -1;

};