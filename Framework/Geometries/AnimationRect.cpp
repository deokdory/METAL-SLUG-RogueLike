#include "Framework.h"
#include "AnimationRect.h"

#include "Utilities/Animator.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size) 
  : TextureRect(position, size, .0f) {
  SetShader(ShaderPath + L"Animation.hlsl");

  //animator = new Animator();

  // Sampler
  {
    // 선형 보간
    D3D11_SAMPLER_DESC desc;
    States::GetSamplerDesc(&desc);
    States::CreateSamplerState(&desc, &point[0]);

    // Point Sampling
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    States::CreateSamplerState(&desc, &point[1]);
  }

  // Blende
  {
    // 블렌드 비활성화
    D3D11_BLEND_DESC desc;
    States::GetBlendDesc(&desc);
    States::CreateBlendState(&desc, &bPoint[0]);

    // 활성화
    desc.RenderTarget[0].BlendEnable = true;
    States::CreateBlendState(&desc, &bPoint[1]);
  }
}

AnimationRect::~AnimationRect() {}

void AnimationRect::Update() { 
  //animator->Update();

  if (bFliped) {
    MapVertexBuffer();
    {
      vertices[0].uv.x = 
          animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
      vertices[0].uv.y =
          animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

      vertices[1].uv.x =
          animator->GetCurrentFrame().x;
      vertices[1].uv.y = animator->GetCurrentFrame().y;

      vertices[2].uv.x =
          animator->GetCurrentFrame().x;
      vertices[2].uv.y =
          animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

      vertices[3].uv.x = 
          animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
      vertices[3].uv.y = animator->GetCurrentFrame().y;
    }
    UnmapVertexBuffer();
  } else {
    MapVertexBuffer();
    {
      vertices[0].uv.x = animator->GetCurrentFrame().x;
      vertices[0].uv.y =
          animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

      vertices[1].uv.x =
          animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
      vertices[1].uv.y = animator->GetCurrentFrame().y;

      vertices[2].uv.x =
          animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
      vertices[2].uv.y =
          animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

      vertices[3].uv.x = animator->GetCurrentFrame().x;
      vertices[3].uv.y = animator->GetCurrentFrame().y;
    }
    UnmapVertexBuffer();
  }
  __super::Update();
}

void AnimationRect::Render() { 
  shaderResourceView = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &point[1]);
  DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFFFF);
  __super::Render();
  //DC->PSSetSamplers(0, 1, &point[0]);
  //DC->OMSetBlendState(bPoint[0], nullptr, (UINT)0xFFFFFFFFFF);
}