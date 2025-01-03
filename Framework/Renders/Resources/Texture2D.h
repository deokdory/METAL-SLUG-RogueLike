#pragma once

struct TextureDesc {
  std::wstring filePath = L"";
  UINT width = 0;
  UINT height = 0;
  ID3D11ShaderResourceView* srv = nullptr;

  bool operator==(const TextureDesc& other) { 
    bool b = true;

    b &= filePath == other.filePath;
    b &= width == other.width;
    b &= height == other.height;

    return b;
  }
};

class Texture2D {
public:
  Texture2D(std::wstring filePath);

  void ReadPixel(std::vector<Color>* pixels);
  static void ReadPixel(ID3D11Texture2D* texture, std::vector<Color>* pixels);

  ID3D11ShaderResourceView* GetSRV() { return srv; }

  float GetWidth() { return (float)width; }
  float GetHeight() { return (float)height; }
  std::wstring GetFilePath() { return filePath; }

private:
  friend class Textures;

  std::wstring filePath = L"";
  ID3D11ShaderResourceView* srv = nullptr;
  UINT width = 0;
  UINT height = 0;
};

class Textures {
public:
  static void Delete();

  private:
  friend class Texture2D;
  static void Load(Texture2D* texture);
  static TextureDesc* Find(std::wstring filePath);

  static std::map<std::wstring, TextureDesc> descs;
};

/*
DirectXTex
- 텍스쳐 처리 라이브러리
- DDS 파일 읽기, 쓰기, 리사이징, 포맷 변환, 미핑 맵 생성 등
  여러 텍스쳐 콘텐츠 처리 작업을 수행

- Metadata
- 너비, 높이, 깊이, 배열 크기, 미핑 맵 수 및 형식과 같은 정보를 저장
*/