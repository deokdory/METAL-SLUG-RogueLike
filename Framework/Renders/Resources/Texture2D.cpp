#include "Framework.h"
#include "Texture2D.h"

//using namespace DirectX;
std::map<std::wstring, TextureDesc> Textures::descs;

Texture2D::Texture2D(std::wstring filePath)
: filePath(filePath) 
{
  auto find = Textures::Find(filePath);
  if (find != nullptr)
  {
    this->srv = find->srv;
    this->width = find->width;
    this->height = find->height;
  }
  else Textures::Load(this);
}

void Texture2D::ReadPixel(std::vector<Color>* pixels) {
  ID3D11Texture2D* texture;
  srv->GetResource((ID3D11Resource**)&texture);

  ReadPixel(texture, pixels);
}

void Texture2D::ReadPixel(ID3D11Texture2D* texture,
                          std::vector<Color>* pixels) {

  D3D11_TEXTURE2D_DESC srcDesc;  // 원본
  texture->GetDesc(&srcDesc);    // 원본에 데이터 복사

  D3D11_TEXTURE2D_DESC destDesc;  // 텍스쳐 정보의 복사본
  ZERO_MEMORY(destDesc);

  // 복사할 텍스쳐 desc 설정
  destDesc.Usage = D3D11_USAGE_STAGING;
  destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
  destDesc.Width = srcDesc.Width;
  destDesc.Height = srcDesc.Height;
  destDesc.MipLevels = 1;
  destDesc.ArraySize = 1;
  destDesc.Format = srcDesc.Format;
  destDesc.SampleDesc = srcDesc.SampleDesc;

  ID3D11Texture2D* destTex = nullptr;

  // 복사할 텍스쳐 생성
  HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr, &destTex);
  CHECK(hr);

  // 원본 텍스쳐에서 복사할 텍스쳐로 데이터를 복사
  D3DX11LoadTextureFromTexture(DC, texture, nullptr, destTex);

  // 픽셀 개수 ( 텍스쳐 크기 )
  int pixelNum = destDesc.Width * destDesc.Height;
  // 픽셀 데이터를 저장할 배열
  UINT* colors = new UINT[pixelNum];

  D3D11_MAPPED_SUBRESOURCE subResource;
  DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subResource);
  {
    // 데이터를 colors 배열에 복사
    memcpy(colors, subResource.pData,
           sizeof(UINT) * destDesc.Width * destDesc.Height);
  }
  DC->Unmap(destTex, 0);

  UINT* alpha = new UINT[pixelNum];
  UINT* red = new UINT[pixelNum];
  UINT* green = new UINT[pixelNum];
  UINT* blue = new UINT[pixelNum];

  for (int i = 0; i < pixelNum; i++) {
    red[i] = (colors[i] & 0xff000000);
    green[i] = (colors[i] & 0x00ff0000);
    blue[i] = (colors[i] & 0x0000ff00);
    alpha[i] = (colors[i] & 0x000000ff);
    // DirectX = RGBA 순서
    // 텍스쳐 원래 순서 = BGRA

    red[i] = colors[i] >> 16;
    blue[i] = colors[i] << 16;

    colors[i] = alpha[i] | red[i] | green[i] | blue[i];
  }
  // pixels 벡터에 colors 배열의 데이터를 할당
  pixels->assign(&colors[0], &colors[pixelNum - 1]);

  SAFE_DELETE_ARRAY(colors);
  SAFE_RELEASE(destTex);
}

void Textures::Delete() {
  for (auto it = descs.begin(); it != descs.end(); ++it) {
    SAFE_RELEASE(it->second.srv);
  }
}

void Textures::Load(Texture2D* texture)
{
  HRESULT hr;
  DirectX::TexMetadata metaData;

  std::wstring ext = Path::GetExtension(texture->filePath);

  if (ext == L"tga") {
    hr = DirectX::GetMetadataFromTGAFile(texture->filePath.c_str(), metaData);
  }
  else if (ext == L"dds") {
    hr = DirectX::GetMetadataFromDDSFile(texture->filePath.c_str(), DirectX::DDS_FLAGS_NONE,
      metaData);
  }
  else {
    hr = DirectX::GetMetadataFromWICFile(texture->filePath.c_str(), DirectX::WIC_FLAGS_NONE,
      metaData);
  }
  
  CHECK(hr);

  UINT width = metaData.width;
  UINT height = metaData.height;

  TextureDesc desc;

  desc.filePath = texture->filePath;
  desc.width = width;
  desc.height = height;

  //TextureDesc exist;
  //bool bExist = false;

  //for (TextureDesc temp : descs)
  //{
  //  if (desc == temp)
  //  {
  //    bExist = true;
  //    exist = temp;
  //    break;
  //  }
  //}

  //if (bExist == true) 
  //{
  //  texture->srv = exist.srv;
  //  texture->metaData = metaData;
  //}
  //else 

  {
    DirectX::ScratchImage image;

    if (ext == L"tga") {
      hr = DirectX::LoadFromTGAFile(texture->filePath.c_str(), &metaData, image);
    }

    else if (ext == L"dds") {
      hr = DirectX::LoadFromDDSFile(texture->filePath.c_str(), DirectX::DDS_FLAGS_NONE,
        &metaData, image);
    }
    else {
      hr = DirectX::LoadFromWICFile(texture->filePath.c_str(), DirectX::WIC_FLAGS_NONE,
        &metaData, image);
    }
    CHECK(hr);

    ID3D11ShaderResourceView* srv = nullptr;
    hr = CreateShaderResourceView(DEVICE, image.GetImages(),
      image.GetImageCount(), metaData, &srv);
    CHECK(hr);

    desc.srv = texture->srv = srv;
    texture->width = metaData.width;
    texture->height = metaData.height;

    descs.insert(std::make_pair(texture->filePath, desc));
  }
}

TextureDesc* Textures::Find(std::wstring filePath)
{
  auto find = descs.find(filePath);
  return find != descs.end() ? &find->second : nullptr;
}
