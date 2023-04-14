#include "Framework.h"
#include "InputLayout.h"


InputLayout::~InputLayout() { SAFE_RELEASE(inputLayout); }

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* desc, UINT count,
                         ID3DBlob* blob) {
  // 하나라도 없으면 프로그램 종료
  if (!desc || !count || !blob) CHECK(false);

  HRESULT hr = DEVICE->CreateInputLayout(
      desc,                      // InputLayout desc
      count,                     // InputLayout을 구성하는 선언의 수
                                 // blob = 메모리 블록
      blob->GetBufferPointer(),  // 셰이더 코드를 포함하는 블롭에 대한 포인터
      blob->GetBufferSize(),  // 셰이더 코드 블롭의 크기
      &inputLayout);          // 리턴 받을 변수

  CHECK(hr);
}

void InputLayout::SetIA() { DC->IASetInputLayout(inputLayout); }
