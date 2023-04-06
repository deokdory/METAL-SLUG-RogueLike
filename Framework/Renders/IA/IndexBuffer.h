// 버텍스를 시계방향으로 연결해야 보임 ( 반대편에선 안 보임 반시계방향이라 )
// 그 순서를 정해주기 위한 인덱스 버퍼
#pragma once

class IndexBuffer {
 public:
  ~IndexBuffer();

  void Create(const vector<uint>& indices,
              const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

  ID3D11Buffer* GetResource() { return buffer; }
  uint GetStride() { return stride; }
  uint GetOffset() { return offset; }
  uint GetCount() { return count; }

  void SetIA();
   private:
  ID3D11Buffer* buffer = nullptr;

  uint stride = 0;
  uint offset = 0;
  uint count = 0;
};