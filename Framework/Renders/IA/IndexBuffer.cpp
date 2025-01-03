#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::~IndexBuffer() { SAFE_RELEASE(buffer); }

void IndexBuffer::Create(const vector<UINT>& indices,
                         const D3D11_USAGE& usage) {
  stride = sizeof(UINT);
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

      // CPU���� ���� ����, GPU���� ����� �� �ִ� ���·� ��ȯ ������ ����
      case D3D11_USAGE_STAGING:
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
        break;
    }
  // Buffer ����
  {
    D3D11_SUBRESOURCE_DATA subData;  // ���� �����͸� ���� ����ü
    ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));  // ����ü �ʱ�ȭ

    subData.pSysMem = indices.data();  // ���� �����͸� �Ҵ��� �޸𸮿� ����

    HRESULT hr =
        DEVICE->CreateBuffer(&desc, &subData, &buffer);  // ���� ���� ����
    CHECK(hr);  // ���� ���� �� ��
  }
}

void IndexBuffer::SetIA() {
  // ���� ������ 32��Ʈ�� ����
  DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
