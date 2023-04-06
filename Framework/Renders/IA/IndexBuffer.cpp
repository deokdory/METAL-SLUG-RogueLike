#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::~IndexBuffer() { SAFE_RELEASE(buffer); }

void IndexBuffer::Create(const vector<uint>& indices,
                         const D3D11_USAGE& usage) {
  stride = sizeof(uint);
  count = indices.size();

  D3D11_BUFFER_DESC desc;
  ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

  //desc
  {
    desc.Usage = usage;
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.ByteWidth = stride * count;
  }
			switch (usage) {
      case D3D11_USAGE_DEFAULT:
      case D3D11_USAGE_IMMUTABLE:
        break;

      case D3D11_USAGE_DYNAMIC:
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        break;

      // CPU에서 접근 가능, GPU에서 사용할 수 있는 형태로 변환 가능한 버퍼
      case D3D11_USAGE_STAGING:
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
        break;
    }
  // Buffer 생성
  {
    D3D11_SUBRESOURCE_DATA subData;  // 정점 데이터를 담을 구조체
    ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));  // 구조체 초기화

    subData.pSysMem = indices.data();  // 정점 데이터를 할당한 메모리에 복사

    HRESULT hr =
        DEVICE->CreateBuffer(&desc, &subData, &buffer);  // 정점 버퍼 생성
    CHECK(hr);  // 생성 실패 시 펑
  }
}

void IndexBuffer::SetIA() {
  // 정점 개수를 32비트로 설정
  DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
