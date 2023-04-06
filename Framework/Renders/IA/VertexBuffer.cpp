#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer() { SAFE_RELEASE(buffer); }

// Input Assembler
void VertexBuffer::SetIA() {
  // 입력 어셈블러에 정점 버퍼를 입력하는 함수
  DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
