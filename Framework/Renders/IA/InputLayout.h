// ���� �������� ���̾ƿ��� �����ϰ� �����ϴ� ����

#pragma once

class InputLayout {
 public:
  ~InputLayout();

  void Create(D3D11_INPUT_ELEMENT_DESC* desc, UINT count, ID3DBlob* blob);

  void SetIA();
 private:
  ID3D11InputLayout* inputLayout = nullptr;
};

/*
InputLayout
- ���� ������ ������ ������ ����
- ���� �������� �� ���(��ġ, ����, �ؽ��� ��ǥ ��)�� ����, ũ��, ���� ���� ����
- IA�ܰ迡�� ���� ���̴��� �����͸� �����ϱ� ���� ���� �����͸� �ùٸ���
�ؼ��ϴµ� ���

*/