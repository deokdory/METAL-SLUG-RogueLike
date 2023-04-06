// GPU에서 사용하는 데이터를 CPU에서 생성하고 수정할 수 있도록 버퍼를 제공하는 역할
// 버퍼 -> 정보 덩어리

#pragma once
#include "Framework.h"

class ShaderBuffer {
public:
	// Vertex Shader Buffer
	void SetVSBuffer(uint slot)
	{
		MapData();
		DC->VSSetConstantBuffers(slot, 1, &buffer);
	}
	// Pixel Shader
	void SetPSBuffer(uint slot)
	{
		MapData();
		DC->PSSetConstantBuffers(slot, 1, &buffer);
	}

protected:
	// GPU 쪽에서 사용하는 데이터를 CPU 쪽에서 생성하고 수정할 수 있도록 제공하는 버퍼
	ShaderBuffer(void* data, uint dataSize)
		: data(data), dataSize(dataSize)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;				// 버퍼 사용 용도
		desc.ByteWidth = dataSize;						// 버퍼 크기
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// 바인딩 대상 ( CONSTANT BUFFER -> 수정 불가능한 버퍼 : 수정하기 위해 Map 과정 필요 )
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU에서 버퍼 접근 방식 설정

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
		CHECK(hr);
	}

private:
	void MapData()
	{
		// 데이터 매핑을 위한 구조체
		D3D11_MAPPED_SUBRESOURCE subResource;
		// 데이터 매핑
		HRESULT hr = DC->Map(
			buffer,						// 매핑할 그래픽 리소스
			0,							// 매핑 시작 바이트 위치
			D3D11_MAP_WRITE_DISCARD,	// 매핑 방법
			0,							// 매핑 원하는 하위 리소스
			&subResource				// 매핑된 메모리 주소를 전달
		);
		CHECK(hr);
		// 데이터 복사 
		memcpy(subResource.pData, data, dataSize);
		// 버퍼 언매핑
		DC->Unmap(buffer, 0);
	}

private:
	D3D11_BUFFER_DESC desc = { 0 };
	ID3D11Buffer* buffer = nullptr;

	void* data = nullptr;
	uint dataSize = 0;

};