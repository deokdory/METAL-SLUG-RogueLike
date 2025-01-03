#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation,
  std::wstring path)
  : position(position),
  size(size),
  rotation(rotation) {

  Texture2D* texture = new Texture2D(path);

  // vertices
  vertices.assign(4, VertexTexture());

  vertices[0].position = verticesLocalPosition[0] = Vector3(-0.5f, -0.5f, 0.0f);
  vertices[1].position = verticesLocalPosition[1] = Vector3(0.5f, 0.5f, 0.0f);
  vertices[2].position = verticesLocalPosition[2] = Vector3(0.5f, -0.5f, 0.0f);
  vertices[3].position = verticesLocalPosition[3] = Vector3(-0.5f, 0.5f, 0.0f);

  vertices[0].uv = Vector2(0, 1);
  vertices[1].uv = Vector2(1, 0);
  vertices[2].uv = Vector2(1, 1);
  vertices[3].uv = Vector2(0, 0);

  // vertex Buffer
  vertexBuffer = new VertexBuffer;
  vertexBuffer->Create(vertices, D3D11_USAGE_DYNAMIC);

  // index Buffer
  incides = { 0, 1, 2, 0, 3, 1 };
  indexBuffer = new IndexBuffer();
  indexBuffer->Create(incides, D3D11_USAGE_IMMUTABLE);

  // Texture Buffer
  textureBuffer = new TextureBuffer();

  // vertex Shader
  vertexShader = new VertexShader();
  vertexShader->Create(ShaderPath + L"VertexTexture.hlsl", "VS");

  // pixel Shader
  pixelShader = new PixelShader();
  pixelShader->Create(ShaderPath + L"VertexTexture.hlsl", "PS");

  // input Layout
  inputLayout = new InputLayout();
  inputLayout->Create(VertexTexture::descs, VertexTexture::count, vertexShader->GetBlob());

  // world Buffer
  worldBuffer = new WorldBuffer();

  // Shader Resource View
  {
    shaderResourceView = texture->GetSRV();
  }

  // Sampler
  {
    // 선형 보간
    D3D11_SAMPLER_DESC desc;
    States::GetSamplerDesc(&desc);
    States::CreateSamplerState(&desc, &point[0]);

    // Point Sampling
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    States::CreateSamplerState(&desc, &point[1]);
  }

  // Blende
  {
    // 블렌드 비활성화
    D3D11_BLEND_DESC desc;
    States::GetBlendDesc(&desc);
    States::CreateBlendState(&desc, &bPoint[0]);

    // 활성화
    desc.RenderTarget[0].BlendEnable = true;
    States::CreateBlendState(&desc, &bPoint[1]);
  }
  SAFE_DELETE(texture);
}

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation)
  : position(position), size(size), rotation(rotation) {
  // vertices
  vertices.assign(4, VertexTexture());

  vertices[0].position = verticesLocalPosition[0] = Vector3(-0.5f, -0.5f, 0.0f);
  vertices[1].position = verticesLocalPosition[1] = Vector3(0.5f, 0.5f, 0.0f);
  vertices[2].position = verticesLocalPosition[2] = Vector3(0.5f, -0.5f, 0.0f);
  vertices[3].position = verticesLocalPosition[3] = Vector3(-0.5f, 0.5f, 0.0f);

  vertices[0].uv = Vector2(0, 1);
  vertices[1].uv = Vector2(1, 0);
  vertices[2].uv = Vector2(1, 1);
  vertices[3].uv = Vector2(0, 0);

  // vertex Buffer
  vertexBuffer = new VertexBuffer;
  vertexBuffer->Create(vertices, D3D11_USAGE_DYNAMIC);

  // index Buffer
  incides = { 0, 1, 2, 0, 3, 1 };
  indexBuffer = new IndexBuffer();
  indexBuffer->Create(incides, D3D11_USAGE_IMMUTABLE);

  // Texture Buffer
  textureBuffer = new TextureBuffer();

  // vertex Shader
  vertexShader = new VertexShader();
  vertexShader->Create(ShaderPath + L"VertexTexture.hlsl", "VS");

  // pixel Shader
  pixelShader = new PixelShader();
  pixelShader->Create(ShaderPath + L"VertexTexture.hlsl", "PS");

  // input Layout
  inputLayout = new InputLayout();
  inputLayout->Create(VertexTexture::descs, VertexTexture::count, vertexShader->GetBlob());

  // world Buffer
  worldBuffer = new WorldBuffer();

  // Sampler
  {
    // Linear Sampling
    D3D11_SAMPLER_DESC desc;
    States::GetSamplerDesc(&desc);
    States::CreateSamplerState(&desc, &point[0]);

    // Point Sampling
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    States::CreateSamplerState(&desc, &point[1]);
  }

  // Blende
  {
    // 블렌드 비활성화
    D3D11_BLEND_DESC desc;
    States::GetBlendDesc(&desc);
    States::CreateBlendState(&desc, &bPoint[0]);

    // 활성화
    desc.RenderTarget[0].BlendEnable = true;
    States::CreateBlendState(&desc, &bPoint[1]);
  }

}

TextureRect::~TextureRect() {
  //SAFE_RELEASE(shaderResourceView); // Texture2D -> Textures 에서 지움
  SAFE_DELETE(worldBuffer);
  SAFE_DELETE(inputLayout);
  SAFE_DELETE(pixelShader);
  SAFE_DELETE(vertexShader);
  SAFE_DELETE(textureBuffer);
  SAFE_DELETE(indexBuffer);
  SAFE_DELETE(vertexBuffer);
}

void TextureRect::Move(Vector2 Move) {
  position += {Move.x, Move.y, 0.0f};
}

void TextureRect::mapVertexBuffer() {
  DC->Map(vertexBuffer->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void TextureRect::unmapVertexBuffer() {
  std::memcpy(subResource.pData, vertices.data(),
    sizeof(vertices[0]) * vertices.size());
  DC->Unmap(vertexBuffer->GetResource(), 0);

}

void TextureRect::SetShader(std::wstring shaderpath) {
  vertexShader->Clear();
  pixelShader->Clear();

  vertexShader->Create(shaderpath, "VS");
  pixelShader->Create(shaderpath, "PS");
}

void TextureRect::SetUV(Vector2 startUV, Vector2 endUV)
{
  mapVertexBuffer();
  {
    vertices[0].uv.x = startUV.x;
    vertices[0].uv.y = endUV.y;

    vertices[1].uv.x = endUV.x;
    vertices[1].uv.y = startUV.y;

    vertices[2].uv.x = endUV.x;
    vertices[2].uv.y = endUV.y;

    vertices[3].uv.x = startUV.x;
    vertices[3].uv.y = startUV.y;
  }
  unmapVertexBuffer();
}

void TextureRect::SetAnchorPoint(AnchorPoint anchor) {

  switch (anchor)
  {
  case AnchorPoint::LEFT_TOP:
    mapVertexBuffer();
    {
      vertices[0].position = verticesLocalPosition[0] =
        Vector3(0.0f, -1.0f, 0.0f);
      vertices[1].position = verticesLocalPosition[1] =
        Vector3(1.0f, 0.0f, 0.0f);
      vertices[2].position = verticesLocalPosition[2] =
        Vector3(1.0f, -1.0f, 0.0f);
      vertices[3].position = verticesLocalPosition[3] =
        Vector3(0.0f, 0.0f, 0.0f);
    }
    unmapVertexBuffer();
    break;
  case AnchorPoint::MID_TOP:
    mapVertexBuffer();
    {
      vertices[0].position = verticesLocalPosition[0] =
        Vector3(-0.5f, -1.0f, 0.0f);
      vertices[1].position = verticesLocalPosition[1] =
        Vector3(0.5f, 0.0f, 0.0f);
      vertices[2].position = verticesLocalPosition[2] =
        Vector3(0.5f, -1.0f, 0.0f);
      vertices[3].position = verticesLocalPosition[3] =
        Vector3(-0.5f, 0.0f, 0.0f);
    }
    unmapVertexBuffer();
    break;
  case AnchorPoint::RIGHT_TOP:
    mapVertexBuffer();
    {
      vertices[0].position = verticesLocalPosition[0] =
        Vector3(-1.0f, -1.0f, 0.0f);
      vertices[1].position = verticesLocalPosition[1] =
        Vector3(0.0f, 0.0f, 0.0f);
      vertices[2].position = verticesLocalPosition[2] =
        Vector3(0.0f, -1.0f, 0.0f);
      vertices[3].position = verticesLocalPosition[3] =
        Vector3(-1.0f, 0.0f, 0.0f);
    }
    unmapVertexBuffer();
    break;
  case AnchorPoint::LEFT_MID:
    mapVertexBuffer();
    {
      vertices[0].position = verticesLocalPosition[0] =
        Vector3(0.0f, -0.5f, 0.0f);
      vertices[1].position = verticesLocalPosition[1] =
        Vector3(1.0f, 0.5f, 0.0f);
      vertices[2].position = verticesLocalPosition[2] =
        Vector3(1.0f, -0.5f, 0.0f);
      vertices[3].position = verticesLocalPosition[3] =
        Vector3(0.0f, 0.5f, 0.0f);
    }
    unmapVertexBuffer();
    break;
  case AnchorPoint::CENTER:
    mapVertexBuffer();
    {
      vertices[0].position = verticesLocalPosition[0] =
        Vector3(-0.5f, -0.5f, 0.0f);
      vertices[1].position = verticesLocalPosition[1] =
        Vector3(0.5f, 0.5f, 0.0f);
      vertices[2].position = verticesLocalPosition[2] =
        Vector3(0.5f, -0.5f, 0.0f);
      vertices[3].position = verticesLocalPosition[3] =
        Vector3(-0.5f, 0.5f, 0.0f);
    }
    unmapVertexBuffer();
    break;
  case AnchorPoint::RIGHT_MID:
    mapVertexBuffer();
    {
      vertices[0].position = verticesLocalPosition[0] =
        Vector3(-1.0f, -0.5f, 0.0f);
      vertices[1].position = verticesLocalPosition[1] =
        Vector3(0.0f, 0.5f, 0.0f);
      vertices[2].position = verticesLocalPosition[2] =
        Vector3(0.0f, -0.5f, 0.0f);
      vertices[3].position = verticesLocalPosition[3] =
        Vector3(-1.0f, 0.5f, 0.0f);
    }
    unmapVertexBuffer();
    break;
  case AnchorPoint::LEFT_BOT:
    mapVertexBuffer();
    {
      vertices[0].position = verticesLocalPosition[0] =
        Vector3(0.0f, 0.0f, 0.0f);
      vertices[1].position = verticesLocalPosition[1] =
        Vector3(1.0f, 1.0f, 0.0f);
      vertices[2].position = verticesLocalPosition[2] =
        Vector3(1.0f, 0.0f, 0.0f);
      vertices[3].position = verticesLocalPosition[3] =
        Vector3(0.0f, 1.0f, 0.0f);
    }
    unmapVertexBuffer();
    break;
  case AnchorPoint::MID_BOT:
    mapVertexBuffer();
    {
      vertices[0].position = verticesLocalPosition[0] =
        Vector3(-0.5f, 0.0f, 0.0f);
      vertices[1].position = verticesLocalPosition[1] =
        Vector3(0.5f, 1.0f, 0.0f);
      vertices[2].position = verticesLocalPosition[2] =
        Vector3(0.5f, 0.0f, 0.0f);
      vertices[3].position = verticesLocalPosition[3] =
        Vector3(-0.5f, 1.0f, 0.0f);
    }
    unmapVertexBuffer();
    break;
  case AnchorPoint::RIGHT_BOT:
    mapVertexBuffer();
    {
      vertices[0].position = verticesLocalPosition[0] =
        Vector3(-1.0f, 0.0f, 0.0f);
      vertices[1].position = verticesLocalPosition[1] =
        Vector3(0.0f, 1.0f, 0.0f);
      vertices[2].position = verticesLocalPosition[2] =
        Vector3(0.0f, 0.0f, 0.0f);
      vertices[3].position = verticesLocalPosition[3] =
        Vector3(-1.0f, 1.0f, 0.0f);
    }
    unmapVertexBuffer();
    break;
  default:
    break;
  }
}

void TextureRect::Update() {
  UpdateWorld();
}

void TextureRect::UpdateWorld() {
  D3DXMatrixTranslation(&transMatrix, position.x, position.y, position.z);
  D3DXMatrixScaling(&scaleMatrix, size.x, size.y, size.z);
  D3DXMatrixRotationZ(&rotationMatrix, (float)D3DXToRadian(rotation));

  worldMatrix = scaleMatrix * rotationMatrix * transMatrix;
  worldBuffer->SetWorld(worldMatrix);
}

void TextureRect::Render() {

  DC->PSSetSamplers(0, 1, &point[1]);
  DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFFFF);

  vertexBuffer->SetIA();
  indexBuffer->SetIA();
  inputLayout->SetIA();
  DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  vertexShader->SetShader();
  pixelShader->SetShader();
  worldBuffer->SetVSBuffer(0);

  textureBuffer->SetPSBuffer(2);
  DC->PSSetShaderResources(0, 1, &shaderResourceView);

  DC->DrawIndexed(indexBuffer->GetCount(), 0, 0);
}

void TextureRect::GUI() {}

void TextureRect::SetIsFliped(bool bFliped) 
{
  textureBuffer->Flip(bFliped);
  this->bFliped = bFliped;
}

void TextureRect::SetOpacity(float opacity)
{
  textureBuffer->SetOpacity(opacity);
  this->opacity = opacity;
}
