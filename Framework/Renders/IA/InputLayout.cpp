#include "Framework.h"
#include "InputLayout.h"


InputLayout::~InputLayout() { SAFE_RELEASE(inputLayout); }

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* desc, UINT count,
                         ID3DBlob* blob) {
  // �ϳ��� ������ ���α׷� ����
  if (!desc || !count || !blob) CHECK(false);

  HRESULT hr = DEVICE->CreateInputLayout(
      desc,                      // InputLayout desc
      count,                     // InputLayout�� �����ϴ� ������ ��
                                 // blob = �޸� ���
      blob->GetBufferPointer(),  // ���̴� �ڵ带 �����ϴ� ��ӿ� ���� ������
      blob->GetBufferSize(),  // ���̴� �ڵ� ����� ũ��
      &inputLayout);          // ���� ���� ����

  CHECK(hr);
}

void InputLayout::SetIA() { DC->IASetInputLayout(inputLayout); }
