#include "Framework.h"
// PCH
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation)
    : position(position), size(size), rotation(rotation) {
  // vertices
  {
    vertices.assign(4, VertexColor());

    vertices[0].position = verticesLocalPosition[0] = Vector3(-0.5f, -0.5f, 0.0f);
    vertices[1].position = verticesLocalPosition[1] = Vector3(0.5f, 0.5f, 0.0f);
    vertices[2].position = verticesLocalPosition[2] = Vector3(0.5f, -0.5f, 0.0f);
    vertices[3].position = verticesLocalPosition[3] = Vector3(-0.5f, 0.5f, 0.0f);

    for (auto& v : vertices) {
      v.color = color;
    }
  }

  // Vertex Buffer
  {
    vertexBuffer = new VertexBuffer();
    vertexBuffer->Create(vertices, D3D11_USAGE_DYNAMIC);
  }

  // Index Buffer
  {
    indices = {0, 1, 2, 0, 3, 1};
    indexBuffer = new IndexBuffer();
    indexBuffer->Create(indices, D3D11_USAGE_IMMUTABLE);
  }

  // Vertex Shader
  {
    vertexShader = new VertexShader();
    vertexShader->Create(ShaderPath + L"VertexColor.hlsl", "VS");
  }

  // Input Layout
  {
    indexLayout = new InputLayout();
    indexLayout->Create(VertexColor::descs, VertexColor::count, vertexShader->GetBlob());
  }

  // Pixel Shader
  {
    pixelShader = new PixelShader();
    pixelShader->Create(ShaderPath + L"VertexColor.hlsl", "PS");
  }

  // World
  { worldBuffer = new WorldBuffer(); }
}

Rect::~Rect() {
  SAFE_DELETE(worldBuffer);
  SAFE_DELETE(pixelShader);
  SAFE_DELETE(indexLayout);
  SAFE_DELETE(vertexShader);
  SAFE_DELETE(indexBuffer);
  SAFE_DELETE(vertexBuffer);
  }

void Rect::Update() {
  UpdateWorld();
}

void Rect::Render() {
  // IA
  {
    vertexBuffer->SetIA();
    indexBuffer->SetIA();
    indexLayout->SetIA();
    DC->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // 토폴로지 ( 그리는 방식 )
                                                 // 검색해보길 권장
  }

  // VS
  {
    vertexShader->SetShader();
    worldBuffer->SetVSBuffer(0);
  }

  // PS
  { pixelShader->SetShader(); }

  // Draw
  DC->DrawIndexed(indexBuffer->GetCount(), 0, 0);

}

void Rect::UpdateColor() {
  D3D11_MAPPED_SUBRESOURCE subResource;
  DC->Map(vertexBuffer->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
  {
    for (VertexColor& v : vertices) v.color = color;

    memcpy(subResource.pData, vertices.data(),
           vertexBuffer->GetCount() * vertexBuffer->GetStride());
  }
  DC->Unmap(vertexBuffer->GetResource(), 0);
}

void Rect::UpdateWorld() {
  // Scale
  D3DXMatrixScaling(&ScaleMatrix, size.x, size.y, size.z);
  // Rotation
  D3DXMatrixRotationZ(&rotationMatrix, (float)D3DXToRadian(rotation));
  // Translation
  D3DXMatrixTranslation(&transMatrix, position.x, position.y, position.z);

  worldMatrix = ScaleMatrix * rotationMatrix * transMatrix;  // 순서 중요 -> 행렬은 순서가 바뀌면 결과가 바뀜!!
  worldBuffer->SetWorld(worldMatrix);
}

void Rect::SetColor(Color color) {
  this->color = color;
  UpdateColor();
}
