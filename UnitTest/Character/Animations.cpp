#include "stdafx.h"
#include "Animations.h"

Animator* Animations::getKnight() {
  Texture2D* srcTex = new Texture2D(TexturePath + L"Ye_Oldy_Knight_Guy.png");

  Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

  AnimationClip* Idle =
      new AnimationClip(L"Idle", srcTex, 4, Vector2(0, 0), Vector2(64, 19),
                        false, 1.0f / 3.0f);  // 16, 20

  AnimationClip* Run =
      new AnimationClip(L"Run", srcTex, 6, Vector2(0, 21), Vector2(96, 41),
                        false, 1.0f / 6.0f);  // 16, 21

  AnimationClip* Jump = new AnimationClip(L"Jump", srcTex, 1, Vector2(0, 42),
                                          Vector2(16, 63));  // 17, 22

  AnimationClip* Hit = new AnimationClip(L"Hit", srcTex, 1, Vector2(64, 0),
                                         Vector2(85, 19));  // 22 x 20

  Animator* animator = new Animator();

  animator->AddAnimClip(Idle);
  animator->AddAnimClip(Run);
  animator->AddAnimClip(Jump);
  animator->AddAnimClip(Hit);

  animator->SetCurrentAnimClip(L"Idle");

  SAFE_DELETE(srcTex);
  return animator;
}

Animator* Animations::getEriUpperTest() {
  //Texture2D* srcTex = new Texture2D(TexturePath + L"upper_aim_rifle.png");
  Texture2D* srcTex = new Texture2D(TexturePath + L"eri_test.png");

  AnimationClip* aimRifle =
      new AnimationClip(L"aimRifle", srcTex, 10, Vector2(0, 0),
                        Vector2(459, 62), false, 1.0f / 3.0f);

  Animator* animator = new Animator();

  animator->AddAnimClip(aimRifle);

  animator->SetCurrentAnimClip(L"aimRifle");
  // animator->SetCurrentFrame(4);

  SAFE_DELETE(srcTex);
  return animator;
}

Animator* Animations::getEriLowerTest() {
  Texture2D* srcTex = new Texture2D(TexturePath + L"eri_test.png");

  AnimationClip* idle = new AnimationClip(L"idle", srcTex, 1, Vector2(0, 30),
                                          Vector2(19, 53), false, -1.0f);
  AnimationClip* run =
      new AnimationClip(L"run", srcTex, 12, Vector2(0, 208), Vector2(360, 234),
                        false, 1.0f / 12.0f);

  AnimationClip* jumpBeginRunning =
      new AnimationClip(L"jumpBeginRunning", srcTex, 3, Vector2(0, 54),
                        Vector2(104, 79), false, 1.0f / 3.0f);

  AnimationClip* jumpEndRunning =
      new AnimationClip(L"jumpEndRunning", srcTex, 3, Vector2(0, 80),
                        Vector2(104, 105), false, 1.0f / 3.0f);

  Animator* animator = new Animator();

  animator->AddAnimClip(idle);
  animator->AddAnimClip(run);
  animator->AddAnimClip(jumpBeginRunning);
  animator->AddAnimClip(jumpEndRunning);

  animator->SetCurrentAnimClip(L"run");

  SAFE_DELETE(srcTex);
  return animator;
}
