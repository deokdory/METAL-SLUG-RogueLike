#pragma once

class RenderTexture {
  public:
  RenderTexture();
   ~RenderTexture();

   void RenderToTexture();
   ID3D11ShaderResourceView* GetSRV() { return shaderResourceView; }

   private:
   ID3D11Texture2D* mTexture = nullptr;
   ID3D11ShaderResourceView* shaderResourceView = nullptr;
   ID3D11RenderTargetView* mRtv = nullptr;

};