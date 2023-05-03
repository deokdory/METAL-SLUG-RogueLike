#include "Framework.h"
#include "UI.h"

UI::~UI() {
  SAFE_RELEASE(srv);
  SAFE_DELETE(wb);
  SAFE_DELETE(il);
  SAFE_DELETE(ps);
  SAFE_DELETE(vs);
  SAFE_DELETE(ib);
  SAFE_DELETE(vb);
}

void UI::Update() {
  UpdateWorld();
}

void UI::Render() {
  vb->SetIA();
  ib->SetIA();
  il->SetIA();
  DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  // VS
  vs->SetShader();
  wb->SetVSBuffer(0);

  // PS
  ps->SetShader();

  if (srv) DC->PSGetShaderResources(0, 1, &srv);

  DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void UI::Init(Vector3 position, Vector3 size, float rotation, Color color,
              FillType type) {

  this->position = position;
  this->size = this->originSize = size;
  this->rotation = rotation;
  this->type = type;

  colorVertices.assign(4, VertexColor());
  SetVertices(colorVertices, type);

  for (VertexColor& v : colorVertices) v.color = color;

  // Vertex Buffer
  {
    vb = new VertexBuffer();
    vb->Create(colorVertices, D3D11_USAGE_DYNAMIC);
  }

  // Index Buffer
  {
    indices = {0, 1, 2, 0, 3, 1};
    ib = new IndexBuffer();
    ib->Create(indices, D3D11_USAGE_IMMUTABLE);
  }

  // Vertex Shader
  {
    vs = new VertexShader();
    vs->Create(ShaderPath + L"UI/ColorUI.hlsl", "VS");
  }

  // Input Layout
  {
    il = new InputLayout();
    il->Create(VertexColor::descs, VertexColor::count,
                        vs->GetBlob());
  }

  // Pixel Shader
  {
    ps = new PixelShader();
    ps->Create(ShaderPath + L"UI/ColorUI.hlsl", "PS");
  }

  // World
  { wb = new WorldBuffer(); }
}

void UI::Init(Vector3 position, Vector3 size, float rotation, std::wstring path,
              FillType type) {
  this->position = position;
  this->size = this->originSize = size;
  this->rotation = rotation;
  this->type = type;

  textureVertices.assign(4, VertexTexture());
  SetVertices(textureVertices, type);
  
  textureVertices[0].uv = Vector2(0, 1);
  textureVertices[1].uv = Vector2(1, 0);
  textureVertices[2].uv = Vector2(1, 1);
  textureVertices[3].uv = Vector2(0, 0);

  // Vertex Buffer
  {
    vb = new VertexBuffer();
    vb->Create(textureVertices, D3D11_USAGE_DYNAMIC);
  }

  // Index Buffer
  {
    indices = {0, 1, 2, 0, 3, 1};
    ib = new IndexBuffer();
    ib->Create(indices, D3D11_USAGE_IMMUTABLE);
  }

  // Vertex Shader
  {
    vs = new VertexShader();
    vs->Create(ShaderPath + L"UI/TextureUI.hlsl", "VS");
  }

  // Input Layout
  {
    il = new InputLayout();
    il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
  }

  // Pixel Shader
  {
    ps = new PixelShader();
    ps->Create(ShaderPath + L"UI/TextureUI.hlsl", "PS");
  }

  // World
  { wb = new WorldBuffer(); }

  Texture2D* srcTex = new Texture2D(path);
  srv = srcTex->GetSRV();
  SAFE_DELETE(srcTex);
}

void UI::Init(Vector3 position, Vector3 size, float rotation, FillType type) {
  this->position = position;
  this->size = this->originSize = size;
  this->rotation = rotation;
  this->type;

  textureVertices.assign(4, VertexTexture());
  SetVertices(textureVertices, type);

  textureVertices[0].uv = Vector2(0, 1);
  textureVertices[1].uv = Vector2(1, 0);
  textureVertices[2].uv = Vector2(1, 1);
  textureVertices[3].uv = Vector2(0, 0);

  // Vertex Buffer
  {
    vb = new VertexBuffer();
    vb->Create(textureVertices, D3D11_USAGE_DYNAMIC);
  }

  // Index Buffer
  {
    indices = {0, 1, 2, 0, 3, 1};
    ib = new IndexBuffer();
    ib->Create(indices, D3D11_USAGE_IMMUTABLE);
  }

  // Vertex Shader
  {
    vs = new VertexShader();
    vs->Create(ShaderPath + L"UI/TextureUI.hlsl", "VS");
  }

  // Input Layout
  {
    il = new InputLayout();
    il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
  }

  // Pixel Shader
  {
    ps = new PixelShader();
    ps->Create(ShaderPath + L"UI/TextureUI.hlsl", "PS");
  }

  // World
  { wb = new WorldBuffer(); }
}

void UI::MapVertexBuffer() {
  DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0,
          &subResource);
}

void UI::UnmapVertexBuffer() {
  std::memcpy(subResource.pData, textureVertices.data(),
              sizeof(textureVertices[0]) * textureVertices.size());
  DC->Unmap(vb->GetResource(), 0);
}

template <typename T>
inline void UI::SetVertices(std::vector<T>& vertices, FillType type) {

  switch (type) {
    case UI::NONE: {
      vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
      vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
      vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
      vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
      break;
    }
    case UI::LEFT_TO_RIGHT: {
      vertices[0].position =
          Vector3(0.0f, -0.5f, 0.0f);
      vertices[1].position = 
          Vector3(1.0f, 0.5f, 0.0f);
      vertices[2].position =
          Vector3(1.0f, -0.5f, 0.0f);
      vertices[3].position = 
          Vector3(0.0f, 0.5f, 0.0f);
      break;
    }
    case UI::RIGHT_TO_LEFT: {
      vertices[0].position = 
          Vector3(-1.0f, -0.5f, 0.0f);
      vertices[1].position = 
          Vector3(0.0f, 0.5f, 0.0f);
      vertices[2].position = 
          Vector3(0.0f, -0.5f, 0.0f);
      vertices[3].position = 
          Vector3(-1.0f, 0.5f, 0.0f);
      break;
    }
    case UI::UP_TO_DOWN: {
      vertices[0].position = 
          Vector3(-0.5f, 0.0f, 0.0f);
      vertices[1].position = 
          Vector3(0.5f, 1.0f, 0.0f);
      vertices[2].position = 
          Vector3(0.5f, 0.0f, 0.0f);
      vertices[3].position = 
          Vector3(-0.5f, 1.0f, 0.0f);
      break;
    }
    case UI::DOWN_TO_UP: {
      vertices[0].position = 
          Vector3(-0.5f, -1.0f, 0.0f);
      vertices[1].position = 
          Vector3(0.5f, 0.0f, 0.0f);
      vertices[2].position = 
          Vector3(0.5f, -1.0f, 0.0f);
      vertices[3].position = 
          Vector3(-0.5f, 0.0f, 0.0f);
      break;
    }
    default:
      break;
  }
}

void UI::SetShader(std::wstring shaderpath) {
  vs->Clear();
  ps->Clear();

  vs->Create(shaderpath, "VS");
  ps->Create(shaderpath, "PS");
}

void UI::SetPosition(Vector3 position)
{
  switch (type)
  {
  case UI::NONE:
    break;
  case UI::LEFT_TO_RIGHT:
    position.x -= originSize.x / 2;
    break;
  case UI::RIGHT_TO_LEFT:
    position.x += originSize.x / 2;
    break;
  case UI::UP_TO_DOWN:
    position.y += originSize.y / 2;
    break;
  case UI::DOWN_TO_UP:
    position.y -= originSize.y / 2;
    break;
  default:
    break;
  }
  this->position = position;
}

void UI::UpdateWorld() {
  world = DXMath::Scaling(size) * DXMath::RotationInDegree(rotation) *
          DXMath::Translation(position);

  wb->SetWorld(world);
}