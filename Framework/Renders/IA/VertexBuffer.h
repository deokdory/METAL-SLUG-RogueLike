#pragma once

class VertexBuffer
{
public:
	~VertexBuffer();

	// ���� �ڷ������� ��� ������ �𸣱� ������ ���ø� ���
	// (Color Vertex, Texture Vertex ��)
	template<typename transMatrix>
	void Create(const vector<transMatrix>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT)
	{
		stride = sizeof(transMatrix);		// ���� ũ�� ����
		count = vertices.size();	// ���� ���� ����

		D3D11_BUFFER_DESC desc;							// ���� ���� ���� ����ü ����
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));	// ����ü �ʱ�ȭ

		{
			desc.Usage = usage;							// ������ ��� �뵵 ���� 
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ������ ���� ( ���⼭�� ���� ���۷� ����� )
			desc.ByteWidth = stride * count;			// ���� ũ��

			// CPU ���� ����
			switch (usage)
			{
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
		}
		// Buffer ����
		{
			D3D11_SUBRESOURCE_DATA subData;							// ���� �����͸� ���� ����ü
			ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));	// ����ü �ʱ�ȭ
	
			subData.pSysMem = vertices.data();						// ���� �����͸� �Ҵ��� �޸𸮿� ����

			HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);	// ���� ���� ����
			CHECK(hr);	// ���� ���� �� ��
		}
	}

	ID3D11Buffer* GetResource() { return buffer; }

	UINT GetStride() { return stride; }
	UINT GetOffset() { return offset; }
	UINT GetCount() { return count; }

	void SetIA();
private:
	ID3D11Buffer* buffer = nullptr;

	UINT stride = 0;	// ���� ���� ������ �� ������ �޸� �� size
	UINT offset = 0;	// �� ���� �� �������� �޸� ���� ��ġ ( Position, UV, Color �� )
	UINT count = 0;		// ���� ���۰� ���� ������ ����
};
/*
								GPU					CPU
D3D11_USAGE_DEFAULT	= 0,		�б�, ����			���� �Ұ� 
D3D11_USAGE_IMMUTABLE = 1,		�б�			   		���� �Ұ�
D3D11_USAGE_DYNAMIC	= 2,		�б�			   		����(Map���) (����)
D3D11_USAGE_STAGING	= 3			GPU�޸𸮿��� CPU�޸𸮷� ���� ��� (CopyResource) (��û ����)

*/