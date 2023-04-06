// 가상 함수를 사용하여 DirectX에서 셰이더를 만들고 사용하는 인터페이스

#pragma once

class IShader {
 public:
  virtual void Create(const std::wstring path, const std::string entryName) = 0;
  virtual void Clear() = 0;
  virtual void SetShader() = 0;

 protected:
  void CompileShader(std::wstring path, std::string entryName,
                     std::string profile, ID3DBlob** blob);

  std::wstring path = L"";
  std::string entryName = "";

 private:
  void CheckShaderError(HRESULT hr, ID3DBlob* error);
};