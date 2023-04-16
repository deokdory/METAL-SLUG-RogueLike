#pragma once
enum { x = 0, y };

struct RectEdge {
  Vector3 LT;
  Vector3 LB;
  Vector3 RT;
  Vector3 RB;
};

struct AxisData {
  Vector3 ceneterPos;
  Vector3 axisDir[2];
  float axisLen[2];
};

class CollisionBuffer : public ShaderBuffer {
 public:
  CollisionBuffer() : ShaderBuffer(&data, sizeof(data)) { data.isOn = 1; }

  void SwitchRender() { data.isOn = !data.isOn; }

 private:
  struct Data {
    bool isOn;
    Vector3 dummy;
  } data;
};

class BoundingBox {
 public:
  BoundingBox(Vector3 position, Vector3 size, float rotation, Color color);

  ~BoundingBox();

  void Init();

  void SetAnchorPoint(UINT point);

  void Update(Vector3 position, Vector3 size, float rotation);

  void Render();

  RectEdge* GetRect() { return edge; }

  void UpdateCollisionData();

  void MapVertexBuffer();
  void UnmapVertexBuffer();

  static bool AABB(BoundingBox* a, BoundingBox* b);
  static bool OBB(BoundingBox* a, BoundingBox* b);

 private:
  std::vector<VertexColor> vertices;
  VertexBuffer* vb = nullptr;

  std::vector<UINT> indices;
  IndexBuffer* ib = nullptr;
  InputLayout* il = nullptr;

  VertexShader* vs = nullptr;
  PixelShader* ps = nullptr;

  Matrix world;
  Matrix S, R, T;
  WorldBuffer* wb = nullptr;

  Vector3 position;
  Vector3 size;
  float rotation;
  Color color;

  CollisionBuffer* cb = nullptr;
  ID3D11BlendState* bs = nullptr;

  RectEdge* edge = nullptr;
  AxisData* data = nullptr;

  D3D11_MAPPED_SUBRESOURCE subResource;

};