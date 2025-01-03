#pragma once

class UI {
 public:
  enum FillType {
    NONE = 0,
    LEFT_TO_RIGHT,
    RIGHT_TO_LEFT,
    UP_TO_DOWN,
    DOWN_TO_UP
  };

 public:
  virtual ~UI();

  virtual void Update();
  virtual void Render();

  void Init(Vector3 position, Vector3 size, float rotation, Color color,
            FillType type = NONE);
  void Init(Vector3 position, Vector3 size, float rotation, std::wstring path,
            FillType type = NONE);
  void Init(Vector3 position, Vector3 size, float rotation, FillType type = NONE);

  void mapVertexBuffer();
  void unmapVertexBuffer();

  void SetShader(std::wstring shaderpath);

  const Vector3 GetPosition() { return position; }
  void SetPosition(Vector3 position);

 private:

  template<typename T>
  void SetVertices(std::vector<T>& vertices, FillType type);
  void UpdateWorld();

  protected:
  std::vector<VertexColor> colorVertices;
   std::vector<VertexTexture> textureVertices;
  VertexBuffer* vb = nullptr;

  std::vector<UINT> indices;
  IndexBuffer* ib = nullptr;

  VertexShader* vs = nullptr;
  PixelShader* ps = nullptr;

  InputLayout* il = nullptr;
  
  WorldBuffer* wb = nullptr;
  Matrix world;

  Vector3 originSize;

  Vector3 size;
  Vector3 position;
  float rotation;

  Vector2 uv;
  Color color;

  ID3D11ShaderResourceView* srv = nullptr;
  D3D11_MAPPED_SUBRESOURCE subResource = D3D11_MAPPED_SUBRESOURCE();

  FillType type;
};