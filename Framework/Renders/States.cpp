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
                                   ID3D11RasterizerState** state) {
  HRESULT hr = DEVICE->CreateRasterizerState(desc, state);
  CHECK(hr);
}

void States::CreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC* desc,
                                     ID3D11DepthStencilState** state) {
  HRESULT hr = DEVICE->CreateDepthStencilState(desc, state);
  CHECK(hr);
}

void States::CreateSamplerState(D3D11_SAMPLER_DESC* desc,
                               ID3D11SamplerState** state) {
  HRESULT hr = DEVICE->CreateSamplerState(desc, state);
  CHECK(hr);
}

void States::CreateBlendState(D3D11_BLEND_DESC* desc, ID3D11BlendState** state) {
  HRESULT hr = DEVICE->CreateBlendState(desc, state);
  CHECK(hr);
}
#pragma endregion

#pragma region CreateDesc
void States::CreateRasterizerDesc() { 
  ZERO_MEMORY(rsDesc);
   rsDesc.FillMode = D3D11_FILL_SOLID;      // 다각형의 채우기 모드
   rsDesc.CullMode = D3D11_CULL_BACK;       // 후면 컬링 사용 설정
   rsDesc.FrontCounterClockwise = false;    // 전면 면 방향 시계 방향으로 설정

   rsDesc.DepthBias = 0;                    // 깊이 바이어스 값
   rsDesc.DepthBiasClamp = .0f;             // 깊이 바이어스 클램프 값
   rsDesc.SlopeScaledDepthBias = .0f;       // 경사도에 따른 깊이 바이어스 값
   rsDesc.ScissorEnable = false;            // 가위 테스트 사용 설정 ( 렌더링 대상의 특정 영역만 렌더링하는 용도 )
   rsDesc.MultisampleEnable = false;        // 멀티 샘플링 사용 설정 ( 픽셀 경계의 부드러움을 증가시켜서 이미지 품질 향상)
   rsDesc.AntialiasedLineEnable = false;    // 선 안티앨리어싱 사용 설정 ( 선의 경계 부드럽게 )
}

void States::CreateDepthStencilDesc() { 
  ZERO_MEMORY(dsDesc);
  dsDesc.DepthEnable = true;                                      // 깊이 테스트 사용 설정
  dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;             // 깊이 버퍼의 모든 비트에 대해 쓰기 작업을 허용
  dsDesc.DepthFunc = D3D11_COMPARISON_LESS;                       // 깊이 테스트 함수를 LESS로 설정                

  dsDesc.StencilEnable = true;                                    // 스텐실 테스트 사용 설정
  dsDesc.StencilReadMask = 0xff;                                  // 스텐실 버퍼에서 읽을 수 있는 비트 
  dsDesc.StencilWriteMask = 0xff;                                 // 스텐실 테스트를 사용하도록 설정
                                                                   
  dsDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;    // 전면 면의 스텐실 실패 작업 설정
  dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;    // 전면 면의 스텐실 깊이 실패 작업 설정
  dsDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;    // 전면 면의 스텐실 패스 작업 설정
  dsDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;  // 전면 면의 스텐실 함수 설정
                                                                   
  dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;          // 후면 면의 스텐실 실패 작업 설정
  dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;     // 후면 면의 스텐실 깊이 실패 작업 설정
  dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;          // 후면 면의 스텐실 패스 작업 설정
  dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;          // 후면 면의 스텐실 함수 설정
}

void States::CreateSampleDesc() { 
  ZERO_MEMORY(spDesc);

   spDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;  // 선형 필터링을 사용하여 텍스쳐를 샘플링 ( 텍스쳐 샘플링 방식 설정? )
   spDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;     // U 좌표에 대해 텍스쳐 좌표를 래핑 ( 좌표 처리 방식? )
   spDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;     // V 좌표에 대해 텍스쳐 좌표를 래핑
   spDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;     // W 좌표에 대해 텍스쳐 좌표를 래핑
   spDesc.MaxAnisotropy = 1;                         // 아니소프트로피 필터링에서 사용 ( 현재 사용 안 함 )
   spDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;  // 비교 샘플링에서 사용 ( 현재 사용 안함 )
   spDesc.MinLOD = FLT_MIN;                          // 텍스쳐의 최소 LOD 레벨 생성
   spDesc.MaxLOD = FLT_MAX;                          // 텍스쳐의 최대 LOD 레벨 생성 
}

void States::CreateBlendDesc() {
  ZERO_MEMORY(blDesc);

  blDesc.AlphaToCoverageEnable = false;                         // Alpha to Coverage 사용 여부
  blDesc.IndependentBlendEnable = false;                        // 독립적인 블렌드 사용 여부
                                                                 
  blDesc.RenderTarget[0].BlendEnable = false;                   // 렌더 타겟에 대한 블렌딩 사용 여부
  blDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;      // 소스 색상에 대한 블렌드 인수를 설정
  blDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // 목적지 색상에 대한 블렌드 인수를 설정
  blDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;          // 색상에 대한 블렌드 연산을 설정
                                                                 
  blDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;       // 소스 알파에 대한 블렌드 인수를 설정
  blDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;     // 목적지 알파에 대한 블렌드 인수를 설정
  blDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;     // 알파에 대한 블렌드 연산을 설정

  blDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;  // 모든 색상 채널을 렌더 타겟에 기록
}
#pragma endregion

/*
Depth
- 3D 그래픽에서 픽셀의 깊이를 나타내는 값
- 보통 깊이 버퍼라는 2D 이미지 버퍼에 저장
- 깊이 버퍼는 각 픽셀에 대한 깊이 값을 설정, 이 값은 렌더링 중에 테스트 및 업데이트
- 깊이 버퍼를 사용하면 3D 장면에서 물체들이 올바른 순서로 겹쳐지도록 할 수 있음

Depth Test
- 렌더링 여부를 결정하기 위해 렌더링된 픽셀의 깊이 값을 검사
- 깊이 테스트는 사용자가 정의한 깊이 함수를 사용하여 렌더링된 픽셀의 깊이 버퍼 값을 비교
- 성공하면 렌더링, 실패하면 걸러짐

Stencil
- 깊이 버퍼와 함께 사용되는 2D 이미지 버퍼
- 각 픽셀에 대해 스텐실 값을 저장하며, 이 값은 렌더링 중에 테스트 및 업데이트
- 다양한 렌더링 기술에서 사용
  ex) 그림자 불륨, 클리핑 평면, 포탈 렌더링 등

Stencil Test
- 렌더링 여부를 결정하기 위해 렌더링된 픽셀의 스텐실 값을 검사
- 사용자가 정의한 스텐실 함수를 사용하며 렌더링된 픽셀의 스텐실 값과 스텐실 버퍼의 값을 비교
- 스텐실 테스트에 성공하면 픽셀이 렌더링, 실패하면 걸러짐

Blending
- 렌더링된 픽셀의 색상을 결정하는 방법 중 하나
- 렌더링된 픽셀의 색상과 렌더 타겟의 현재 색상을 결합하는 과정
*/

/*
Alpha to Coverage
- 멀티 샘플링 안티앨리어싱(MSAA)을 사용 시 알파 값을 커버리지 마스크로 변환하여 투명도 구현하는 기술
- 투명한 객체의 가장자리를 더 부드럽게 처리할 수 있음

Independent Blend
- 여러 렌더 타겟에 대해 각각 다른 블렌드 상태를 설정할 수 있도록 하는 기능
*/