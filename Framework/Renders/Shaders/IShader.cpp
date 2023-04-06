#include "Framework.h"
#include "IShader.h"


void IShader::CompileShader(std::wstring path, std::string entryName,
                            std::string profile, ID3DBlob** blob) {
  ID3DBlob* error = nullptr;  // 컴파일러 오류 메세지를 저장할 blob 포인터 변수
  // 쉐이더를 컴파일, 결과를 blob 포인터로 전달 받음
  HRESULT hr = D3DCompileFromFile(
      path.c_str(),  // 컴파일할 쉐이더 경로
      nullptr,       // 쉐이더 파일의 헤더를 나타내는 포인터
      nullptr,       // 사용 안 함
      entryName.c_str(),  // 컴파일할 쉐이더 파일에서 최초
                          // 진입점으로 사용할 함수 이름
      profile.c_str(),  // 컴파일할 쉐이더 파일에서 사용할 프로필 이름
      D3DCOMPILE_ENABLE_STRICTNESS,  // 엄격한 컴파일 옵션 / 경고 메세지를 레벨
                                     // 1로 설정
      0,  // 디버그 정보가 포함된 컴파일 결과를 생성하기 위한 옵션
      blob,  // 컴파일 결과를 저장할 blob 포인터 주소값
      &error  // 컴파일러 오류 메세지를 저장할 blob 포인터 주소값
  );
  CheckShaderError(hr, error);
  SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob* error) {
  if (FAILED(hr)) {
    if (error) {
      std::string str = (const char*)error->GetBufferPointer();
      MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
    }
    // 프로그램 중단
    CHECK(false);
  }
}
