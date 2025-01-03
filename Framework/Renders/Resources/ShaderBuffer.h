// GPU���� ����ϴ� �����͸� CPU���� �����ϰ� ������ �� �ֵ��� ���۸� �����ϴ� ����
// ���� -> ���� ���

#pragma once
#include "Framework.h"

class ShaderBuffer {
public:
	// Vertex Shader Buffer
	void SetVSBuffer(UINT slot)
	{
		MapData();
		DC->VSSetConstantBuffers(slot, 1, &buffer);
	}
	// Pixel Shader
	void SetPSBuffer(UINT slot)
	{
		MapData();
		DC->PSSetConstantBuffers(slot, 1, &buffer);
	}

protected:
	// GPU �ʿ��� ����ϴ� �����͸� CPU �ʿ��� �����ϰ� ������ �� �ֵ��� �����ϴ� ����
	ShaderBuffer(void* data, UINT dataSize)
		: data(data), dataSize(dataSize)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;				// ���� ��� �뵵
		desc.ByteWidth = dataSize;						// ���� ũ��
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// ���ε� ��� ( CONSTANT BUFFER -> ���� �Ұ����� ���� : �����ϱ� ���� Map ���� �ʿ� )
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU���� ���� ���� ��� ����

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
		CHECK(hr);
	}

private:
	void MapData()
	{
		// ������ ������ ���� ����ü
		D3D11_MAPPED_SUBRESOURCE subResource;
		// ������ ����
		HRESULT hr = DC->Map(
			buffer,						// ������ �׷��� ���ҽ�
			0,							// ���� ���� ����Ʈ ��ġ
			D3D11_MAP_WRITE_DISCARD,	// ���� ���
			0,							// ���� ���ϴ� ���� ���ҽ�
			&subResource				// ���ε� �޸� �ּҸ� ����
		);
		CHECK(hr);
		// ������ ���� 
		memcpy(subResource.pData, data, dataSize);
		// ���� �����
		DC->Unmap(buffer, 0);
	}

private:
	D3D11_BUFFER_DESC desc = { 0 };
	ID3D11Buffer* buffer = nullptr;

	void* data = nullptr;
	UINT dataSize = 0;

};