#pragma once

enum AnchorPoint {
  LEFT_TOP, MID_TOP, RIGHT_TOP,
  LEFT_MID, CENTER, RIGHT_MID,
  LEFT_BOT, MID_BOT, RIGHT_BOT
};

class TextureBuffer : public ShaderBuffer {
 public:
  TextureBuffer() : ShaderBuffer(&data, sizeof(data)) { data.bFliped = false; }

  void Flip(bool flip) { this->data.bFliped = flip; }
 private:
  struct Data {
    int bFliped;
    Vector3 dummy;
  } data;
};

class TextureRect {
 public:


  TextureRect(Vector3 position, Vector3 size, float rotation,
              std::wstring path);
  TextureRect(Vector3 position, Vector3 size, float rotation);
  ~TextureRect();

  void MapVertexBuffer();
  void UnmapVertexBuffer();

  void SetSRV(ID3D11ShaderResourceView* srv) { this->shaderResourceView = srv; }
  void SetShader(std::wstring shaderpath);

  // 중심점 재설정
  void SetAnchorPoint(AnchorPoint anchor);

  void Update();
  void UpdateWorld();

  void Render();
  void GUI();

  void Move(Vector2 Move);
  void SetPosition(Vector3 position) { this->position = position; }
  void SetSize(Vector3 size) { this->size = size; }
  void SetRotation(float rotation) { this->rotation = rotation; }

  float GetRotation() { return rotation; }

  void SetIsFliped(bool bFliped = true);

  //Vector3 GetPosition() { return position; }
  //Vector3 GetSize() { return size; }
  //float GetRotation() { return rotation; }

  Matrix GetWorld() { return worldMatrix; }

  Vector3* GetVerticesLocalPosition() { return verticesLocalPosition; }

 protected:
  std::vector<VertexTexture> vertices;
  VertexBuffer* vertexBuffer = nullptr;

  std::vector<UINT> incides;
  IndexBuffer* indexBuffer = nullptr;

  TextureBuffer* textureBuffer;

  VertexShader* vertexShader;
  PixelShader* pixelShader;

  InputLayout* inputLayout;

  Matrix worldMatrix;
  Matrix scaleMatrix, rotationMatrix, transMatrix;

  ID3D11ShaderResourceView* shaderResourceView = nullptr;

  D3D11_MAPPED_SUBRESOURCE subResource;

  WorldBuffer* worldBuffer;

  Vector3 verticesLocalPosition[4];

  protected:
  bool bFliped = false;

  Vector3 position;
  Vector3 size;
  float rotation;
};