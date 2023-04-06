#include "Framework.h"
#include "PixelShader.h"

PixelShader::~PixelShader() { Clear(); }

void PixelShader::Create(const std::wstring path, const std::string entryName) {
  // 쉐이더 경로와 엔트리 이름을 저장
  this->path = path;
  this->entryName = entryName;

  // 쉐이더 컴파일
  CompileShader(path, entryName, "ps_5_0",
                &blob);  // 경로, 함수이름, 픽셀쉐이더 버전?, blob

  // 정점 쉐이더 생성
  HRESULT hr = DEVICE->CreatePixelShader(
      blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
  CHECK(hr);
}

void PixelShader::Clear() {
  SAFE_RELEASE(blob);
  SAFE_RELEASE(shader);
}

void PixelShader::SetShader() { DC->PSSetShader(shader, nullptr, 0); }
