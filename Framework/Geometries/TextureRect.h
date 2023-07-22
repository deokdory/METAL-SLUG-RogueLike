#pragma once

class TextureBuffer : public ShaderBuffer {
 public:
  TextureBuffer() : ShaderBuffer(&data, sizeof(data)) {}

  void Flip(bool flip) { this->data.bFliped = flip; }
  void SetOpacity(float opacity) { this->data.opacity = opacity; }

 private:
  struct Data {
    int bFliped = false;
    float opacity = 1.0f;
    Vector2 dummy = {0, 0};
  } data;
};

class TextureRect {
 public:
  TextureRect(Vector3 position, Vector3 size, float rotation,
              std::wstring path);
  TextureRect(Vector3 position, Vector3 size, float rotation);
  ~TextureRect();

  void SetSRV(ID3D11ShaderResourceView* srv) { this->shaderResourceView = srv; }
  void SetShader(std::wstring shaderpath);

  void SetUV(Vector2 startUV, Vector2 endUV);

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

  void SetOpacity(float opacity);
  float GetOpacity() { return this->opacity; }

 protected:
  void mapVertexBuffer();
  void unmapVertexBuffer();

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

  ID3D11SamplerState* point[2];
  ID3D11BlendState* bPoint[2];

  protected:
  bool bFliped = false;

  Vector3 position;
  Vector3 size;
  float rotation;

  float opacity = 1.0f;
};