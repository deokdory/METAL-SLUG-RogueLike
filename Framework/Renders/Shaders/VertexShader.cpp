#include "Framework.h"
#include "VertexShader.h"

VertexShader::~VertexShader() { Clear(); }

void VertexShader::Create(const std::wstring path,
                          const std::string entryName) {
  // 쉐이더 경로와 엔트리 이름을 저장
  this->path = path;
  this->entryName = entryName;

  // 쉐이더 컴파일
  CompileShader(path, entryName, "vs_5_0",
                &blob);  // 경로, 함수이름, 정점쉐이더 버전?, blob

  // 정점 쉐이더 생성
  HRESULT hr = DEVICE->CreateVertexShader(
      blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
  CHECK(hr);
}

void VertexShader::Clear() {
  SAFE_RELEASE(blob);
  SAFE_RELEASE(shader);
}

void VertexShader::SetShader() { DC->VSSetShader(shader, nullptr, 0); }
