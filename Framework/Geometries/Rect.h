#pragma once

class Rect {
 public:
  Rect(Vector3 position, Vector3 size,
       float rotation);  // 2D 라서 rotation 은 float 단일변수
  ~Rect();

  void Update();
  void Render();

  // void GUI();

  void UpdateWorld();
  void UpdateColor();

  void SetColor(Color color);

  const Vector3 GetPosition() { return position; }
  const Vector3 GetSize() { return size; }
  const float GetRotation() { return rotation; }

  void SetPosition(Vector3 position) { this->position = position; }


  Matrix GetWorld() { return worldMatrix; }

  Vector3* GetVerticesLocalPosition() { return verticesLocalPosition; }

 private:
  std::vector<VertexColor> vertices;
  VertexBuffer* vertexBuffer = nullptr;
  std::vector<UINT> indices;
  IndexBuffer* indexBuffer = nullptr;
  InputLayout* indexLayout = nullptr;
  VertexShader* vertexShader = nullptr;
  PixelShader* pixelShader = nullptr;

  Matrix worldMatrix;
  Matrix ScaleMatrix, rotationMatrix, transMatrix;

  Vector3 position;
  Vector3 size;
  float rotation;

  Vector3 verticesLocalPosition[4];

  Color color = Values::Red;

  WorldBuffer* worldBuffer = nullptr;
};