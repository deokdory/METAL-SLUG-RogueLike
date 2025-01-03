#include "Framework.h"
#include "States.h"
#pragma region static Init

D3D11_RASTERIZER_DESC     States::rsDesc;
D3D11_DEPTH_STENCIL_DESC  States::dsDesc;
D3D11_SAMPLER_DESC        States::spDesc;
D3D11_BLEND_DESC          States::blDesc;

#pragma endregion

void States::Create() {
  CreateRasterizerDesc();
  CreateDepthStencilDesc();
  CreateSampleDesc();
  CreateBlendDesc();
}

#pragma region GetDesc
void States::GetRasterizerDesc(D3D11_RASTERIZER_DESC* desc) {
  std::memcpy(desc, &rsDesc, sizeof(D3D11_RASTERIZER_DESC));
}

void States::GetDepthStencilDesc(D3D11_DEPTH_STENCIL_DESC* desc) {
  std::memcpy(desc, &dsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
}

void States::GetSamplerDesc(D3D11_SAMPLER_DESC* desc) {
  std::memcpy(desc, &spDesc, sizeof(D3D11_SAMPLER_DESC));
}

void States::GetBlendDesc(D3D11_BLEND_DESC* desc) {
  std::memcpy(desc, &blDesc, sizeof(D3D11_BLEND_DESC));
}
#pragma endregion

#pragma region CreateState
void States::CreateRasterizerState(D3D11_RASTERIZER_DESC* desc,
                                   ID3D11RasterizerState** currState) {
  HRESULT hr = DEVICE->CreateRasterizerState(desc, currState);
  CHECK(hr);
}

void States::CreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC* desc,
                                     ID3D11DepthStencilState** currState) {
  HRESULT hr = DEVICE->CreateDepthStencilState(desc, currState);
  CHECK(hr);
}

void States::CreateSamplerState(D3D11_SAMPLER_DESC* desc,
                               ID3D11SamplerState** currState) {
  HRESULT hr = DEVICE->CreateSamplerState(desc, currState);
  CHECK(hr);
}

void States::CreateBlendState(D3D11_BLEND_DESC* desc, ID3D11BlendState** currState) {
  HRESULT hr = DEVICE->CreateBlendState(desc, currState);
  CHECK(hr);
}
#pragma endregion

#pragma region CreateDesc
void States::CreateRasterizerDesc() { 
  ZERO_MEMORY(rsDesc);
   rsDesc.FillMode = D3D11_FILL_SOLID;      // �ٰ����� ä��� ���
   rsDesc.CullMode = D3D11_CULL_BACK;       // �ĸ� �ø� ��� ����
   rsDesc.FrontCounterClockwise = false;    // ���� �� ���� �ð� �������� ����

   rsDesc.DepthBias = 0;                    // ���� ���̾ ��
   rsDesc.DepthBiasClamp = .0f;             // ���� ���̾ Ŭ���� ��
   rsDesc.SlopeScaledDepthBias = .0f;       // ��絵�� ���� ���� ���̾ ��
   rsDesc.ScissorEnable = false;            // ���� �׽�Ʈ ��� ���� ( ������ ����� Ư�� ������ �������ϴ� �뵵 )
   rsDesc.MultisampleEnable = false;        // ��Ƽ ���ø� ��� ���� ( �ȼ� ����� �ε巯���� �������Ѽ� �̹��� ǰ�� ���)
   rsDesc.AntialiasedLineEnable = false;    // �� ��Ƽ�ٸ���� ��� ���� ( ���� ��� �ε巴�� )
}

void States::CreateDepthStencilDesc() { 
  ZERO_MEMORY(dsDesc);
  dsDesc.DepthEnable = true;                                      // ���� �׽�Ʈ ��� ����
  dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;             // ���� ������ ��� ��Ʈ�� ���� ���� �۾��� ���
  dsDesc.DepthFunc = D3D11_COMPARISON_LESS;                       // ���� �׽�Ʈ �Լ��� LESS�� ����                

  dsDesc.StencilEnable = true;                                    // ���ٽ� �׽�Ʈ ��� ����
  dsDesc.StencilReadMask = 0xff;                                  // ���ٽ� ���ۿ��� ���� �� �ִ� ��Ʈ 
  dsDesc.StencilWriteMask = 0xff;                                 // ���ٽ� �׽�Ʈ�� ����ϵ��� ����
                                                                   
  dsDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;    // ���� ���� ���ٽ� ���� �۾� ����
  dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;    // ���� ���� ���ٽ� ���� ���� �۾� ����
  dsDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;    // ���� ���� ���ٽ� �н� �۾� ����
  dsDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;  // ���� ���� ���ٽ� �Լ� ����
                                                                   
  dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;          // �ĸ� ���� ���ٽ� ���� �۾� ����
  dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;     // �ĸ� ���� ���ٽ� ���� ���� �۾� ����
  dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;          // �ĸ� ���� ���ٽ� �н� �۾� ����
  dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;          // �ĸ� ���� ���ٽ� �Լ� ����
}

void States::CreateSampleDesc() { 
  ZERO_MEMORY(spDesc);

   spDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;  // ���� ���͸��� ����Ͽ� �ؽ��ĸ� ���ø� ( �ؽ��� ���ø� ��� ����? )
   spDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;     // U ��ǥ�� ���� �ؽ��� ��ǥ�� ���� ( ��ǥ ó�� ���? )
   spDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;     // V ��ǥ�� ���� �ؽ��� ��ǥ�� ����
   spDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;     // W ��ǥ�� ���� �ؽ��� ��ǥ�� ����
   spDesc.MaxAnisotropy = 1;                         // �ƴϼ���Ʈ���� ���͸����� ��� ( ���� ��� �� �� )
   spDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;  // �� ���ø����� ��� ( ���� ��� ���� )
   spDesc.MinLOD = FLT_MIN;                          // �ؽ����� �ּ� LOD ���� ����
   spDesc.MaxLOD = FLT_MAX;                          // �ؽ����� �ִ� LOD ���� ���� 
}

void States::CreateBlendDesc() {
  ZERO_MEMORY(blDesc);

  blDesc.AlphaToCoverageEnable = false;                         // Alpha to Coverage ��� ����
  blDesc.IndependentBlendEnable = false;                        // �������� ���� ��� ����
                                                                 
  blDesc.RenderTarget[0].BlendEnable = false;                   // ���� Ÿ�ٿ� ���� ���� ��� ����
  blDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;      // �ҽ� ���� ���� ���� �μ��� ����
  blDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // ������ ���� ���� ���� �μ��� ����
  blDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;          // ���� ���� ���� ������ ����
                                                                 
  blDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;       // �ҽ� ���Ŀ� ���� ���� �μ��� ����
  blDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;     // ������ ���Ŀ� ���� ���� �μ��� ����
  blDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;     // ���Ŀ� ���� ���� ������ ����

  blDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;  // ��� ���� ä���� ���� Ÿ�ٿ� ���
}
#pragma endregion

/*
Depth
- 3D �׷��ȿ��� �ȼ��� ���̸� ��Ÿ���� ��
- ���� ���� ���۶�� 2D �̹��� ���ۿ� ����
- ���� ���۴� �� �ȼ��� ���� ���� ���� ����, �� ���� ������ �߿� �׽�Ʈ �� ������Ʈ
- ���� ���۸� ����ϸ� 3D ��鿡�� ��ü���� �ùٸ� ������ ���������� �� �� ����

Depth Test
- ������ ���θ� �����ϱ� ���� �������� �ȼ��� ���� ���� �˻�
- ���� �׽�Ʈ�� ����ڰ� ������ ���� �Լ��� ����Ͽ� �������� �ȼ��� ���� ���� ���� ��
- �����ϸ� ������, �����ϸ� �ɷ���

Stencil
- ���� ���ۿ� �Բ� ���Ǵ� 2D �̹��� ����
- �� �ȼ��� ���� ���ٽ� ���� �����ϸ�, �� ���� ������ �߿� �׽�Ʈ �� ������Ʈ
- �پ��� ������ ������� ���
  ex) �׸��� �ҷ�, Ŭ���� ���, ��Ż ������ ��

Stencil Test
- ������ ���θ� �����ϱ� ���� �������� �ȼ��� ���ٽ� ���� �˻�
- ����ڰ� ������ ���ٽ� �Լ��� ����ϸ� �������� �ȼ��� ���ٽ� ���� ���ٽ� ������ ���� ��
- ���ٽ� �׽�Ʈ�� �����ϸ� �ȼ��� ������, �����ϸ� �ɷ���

Blending
- �������� �ȼ��� ������ �����ϴ� ��� �� �ϳ�
- �������� �ȼ��� ����� ���� Ÿ���� ���� ������ �����ϴ� ����
*/

/*
Alpha to Coverage
- ��Ƽ ���ø� ��Ƽ�ٸ����(MSAA)�� ��� �� ���� ���� Ŀ������ ����ũ�� ��ȯ�Ͽ� ���� �����ϴ� ���
- ������ ��ü�� �����ڸ��� �� �ε巴�� ó���� �� ����

Independent Blend
- ���� ���� Ÿ�ٿ� ���� ���� �ٸ� ���� ���¸� ������ �� �ֵ��� �ϴ� ���
*/