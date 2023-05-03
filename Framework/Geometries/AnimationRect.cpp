#include "Framework.h"
#include "AnimationRect.h"

#include "Utilities/Animator.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size) 
  : TextureRect(position, size, .0f) {

  SetShader(ShaderPath + L"Animation.hlsl");

  //animator = new Animator();
}

AnimationRect::~AnimationRect() {}

void AnimationRect::Update() { 
  //animator->Update();


  if (bFliped) {
    MapVertexBuffer();
    {
      vertices[0].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
      vertices[0].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

      vertices[1].uv.x = animator->GetCurrentFrame().x;
      vertices[1].uv.y = animator->GetCurrentFrame().y;

      vertices[2].uv.x = animator->GetCurrentFrame().x;
      vertices[2].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

      vertices[3].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
      vertices[3].uv.y = animator->GetCurrentFrame().y;
    }
    UnmapVertexBuffer();
  }
  else {
    MapVertexBuffer();
    {
      vertices[0].uv.x = animator->GetCurrentFrame().x;
      vertices[0].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

      vertices[1].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
      vertices[1].uv.y = animator->GetCurrentFrame().y;

      vertices[2].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
      vertices[2].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

      vertices[3].uv.x = animator->GetCurrentFrame().x;
      vertices[3].uv.y = animator->GetCurrentFrame().y;
    }
    UnmapVertexBuffer();
  }

  __super::Update();
}

void AnimationRect::Render() { 
  shaderResourceView = animator->GetCurrentSRV();
  __super::Render();
  //DC->PSSetSamplers(0, 1, &point[0]);
  //DC->OMSetBlendState(bPoint[0], nullptr, (UINT)0xFFFFFFFFFF);
}