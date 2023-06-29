#pragma once
  
class AnimationClip {
 public:
  friend class Animator;

  AnimationClip(std::wstring clipName, Texture2D* srcTex, UINT frameCount,
                Vector2 startPos, Vector2 endPos, float playRate = 1.f / 15.f,
                bool bReversed = false, bool bLoop = true, Vector2 reposition = Values::ZeroVec2);

 protected:
  std::wstring clipName = L"";
  std::vector<Vector2> keyframes;

  UINT frameCount = 0;

  ID3D11ShaderResourceView* srv = nullptr;

  Vector2 texelFrameSize = Values::ZeroVec2;
  Vector2 frameSize = Values::ZeroVec2;
  Vector2 reposition = Values::ZeroVec2;

  float playRate = 0.f;

  bool bReversed = false;
  bool bLoop = true;
};

class Animator {
 public:
  Animator();
  ~Animator();

  void Update();

  std::wstring GetCurrentAnimClipName() { return currentClip->clipName; }

  Vector2 GetCurrentFrame() { return currentFrame; }
  Vector2 GetTexelFrameSize() { return currentClip->texelFrameSize; }

  Vector2 GetFrameSize() { return currentClip->frameSize; }
  Vector2 GetReposition() { return currentClip->reposition; }

  ID3D11ShaderResourceView* GetCurrentSRV() { return currentClip->srv; }

  void AddAnimClip(AnimationClip* animClip);
  void SetCurrentAnimClip(std::wstring clipName);

  void SetCurrentFrame(UINT index);

  bool GetIsFinish() { return isFinish; }

 private:
  bool CheckExist(std::wstring clipName) 
  {
    return animClips.find(clipName) != animClips.end();
  }

 private:
  std::unordered_map<std::wstring, AnimationClip*> animClips;

  AnimationClip* currentClip = nullptr;
  UINT currentFrameIndex = 0;
  Vector2 currentFrame = Values::ZeroVec2;

  double elapsedTime = 0.0;
  bool isFinish = false;
};