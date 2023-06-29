#pragma once

class States {
 public:
  static void Create();

  static void GetRasterizerDesc(D3D11_RASTERIZER_DESC* desc);
  static void GetDepthStencilDesc(D3D11_DEPTH_STENCIL_DESC* desc);
  static void GetSamplerDesc(D3D11_SAMPLER_DESC* desc);
  static void GetBlendDesc(D3D11_BLEND_DESC* desc);

  static void CreateRasterizerState(D3D11_RASTERIZER_DESC* desc,
                                   ID3D11RasterizerState** currState);

  static void CreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC* desc,
                                     ID3D11DepthStencilState** currState);

  static void CreateSamplerState(D3D11_SAMPLER_DESC* desc,
                               ID3D11SamplerState** currState);

  static void CreateBlendState(D3D11_BLEND_DESC* desc, ID3D11BlendState** currState);

  private:
  static void CreateRasterizerDesc();
  static void CreateDepthStencilDesc();
  static void CreateSampleDesc();
  static void CreateBlendDesc();

  static D3D11_RASTERIZER_DESC rsDesc;
  static D3D11_DEPTH_STENCIL_DESC dsDesc;
  static D3D11_SAMPLER_DESC spDesc;
  static D3D11_BLEND_DESC blDesc;

};