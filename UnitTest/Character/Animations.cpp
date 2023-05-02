#include "stdafx.h"
#include "Animations.h"

//Animator* Animations::getKnight() {
//  Texture2D* srcTex = new Texture2D(TexturePath + L"Ye_Oldy_Knight_Guy.png");
//
//  Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());
//
//  AnimationClip* Idle =
//      new AnimationClip(L"Idle", srcTex, 4, Vector2(0, 0), Vector2(64, 19),
//                        false, 1.0f / 3.0f);  // 16, 20
//
//  AnimationClip* Run =
//      new AnimationClip(L"Run", srcTex, 6, Vector2(0, 21), Vector2(96, 41),
//                        false, 1.0f / 6.0f);  // 16, 21
//
//  AnimationClip* Jump = new AnimationClip(L"Jump", srcTex, 1, Vector2(0, 42),
//                                          Vector2(16, 63));  // 17, 22
//
//  AnimationClip* Hit = new AnimationClip(L"Hit", srcTex, 1, Vector2(64, 0),
//                                         Vector2(85, 19));  // 22 x 20
//
//  Animator* animator = new Animator();
//
//  animator->AddAnimClip(Idle);
//  animator->AddAnimClip(Run);
//  animator->AddAnimClip(Jump);
//  animator->AddAnimClip(Hit);
//
//  animator->SetCurrentAnimClip(L"Idle");
//
//  SAFE_DELETE(srcTex);
//  return animator;
//}

Animator* Animations::GetEriUpper() {
  Texture2D* srcTex = new Texture2D(TexturePath + L"eri_upper_x2.png");

  AnimationClip* aim_rifle = new AnimationClip(L"aim_rifle", srcTex, 10, Vector2(0, 0), Vector2(919, 125), -1.f, false, false, Vector2(16, -50));

  AnimationClip* reload_rifle = new AnimationClip(L"reload_rifle", srcTex, 5, Vector2(0, 126), Vector2(449, 188), 1.0f / 5.0f,  false, false, Vector2(15, -29));
  AnimationClip* knife1_rifle = new AnimationClip(L"knife1_rifle", srcTex, 6, Vector2(0, 190), Vector2(599, 269), 1.0f / 12.0f, false, false);
  AnimationClip* knife2_rifle = new AnimationClip(L"knife2_rifle", srcTex, 8, Vector2(0, 270), Vector2(831, 341), 1.0f / 12.0f, false, false);
  AnimationClip* throw_rifle = new AnimationClip(L"throw_rifle", srcTex, 5, Vector2(450, 126), Vector2(922, 189), 1.0f / 20.0f, false, false, Vector2(15, -29));

  Animator* animator = new Animator();

  animator->AddAnimClip(aim_rifle);
  animator->AddAnimClip(reload_rifle);
  animator->AddAnimClip(knife1_rifle);
  animator->AddAnimClip(knife2_rifle);
  animator->AddAnimClip(throw_rifle);

  animator->SetCurrentAnimClip(L"aim_rifle");

  SAFE_DELETE(srcTex);
  return animator;
}

Animator* Animations::GetEriLower() {
  Texture2D* srcTex = new Texture2D(TexturePath + L"eri_lower_x2.png");

  AnimationClip* idle = new AnimationClip(L"idle", srcTex, 1, Vector2(0, 0), Vector2(39, 51), -1.0f, false, false);
  AnimationClip* run = new AnimationClip(L"run", srcTex, 12, Vector2(40, 0), Vector2(749, 51), 1.0f / 12.0f, false, true);
  AnimationClip* runBack = new AnimationClip(L"runBack", srcTex, 12, Vector2(40, 0), Vector2(749, 51), 1.0f / 12.0f, true, true);

  AnimationClip* jumpBegin_run = new AnimationClip(L"jumpBegin_run", srcTex, 3, Vector2(0, 53), Vector2(207, 103), 1.0f / 12.0f, false, false, Vector2(10, 0));
  AnimationClip* jumpEnd_run = new AnimationClip(L"jumpEnd_run", srcTex, 3, Vector2(0, 104), Vector2(207, 154), 1.0f / 6.0f, false, false, Vector2(10, 0));

  AnimationClip* jumpBegin_stand = new AnimationClip(L"jumpBegin_stand", srcTex, 6, Vector2(208, 52), Vector2(615, 113), 1.0 / 24.0f, false, false);
  AnimationClip* jumpEnd_stand = new AnimationClip(L"jumpEnd_stand", srcTex, 6, Vector2(208, 52), Vector2(615, 113), 1.0 / 12.0f, true, false);

  AnimationClip* slide = new AnimationClip(L"slide", srcTex, 3, Vector2(0, 155), Vector2(299, 202), 1.0 / 24.0f, false, false);

  Animator* animator = new Animator();

  animator->AddAnimClip(idle);
  animator->AddAnimClip(run);
  animator->AddAnimClip(runBack);
  animator->AddAnimClip(jumpBegin_run);
  animator->AddAnimClip(jumpEnd_run);
  animator->AddAnimClip(jumpBegin_stand);
  animator->AddAnimClip(jumpEnd_stand);
  animator->AddAnimClip(slide);

  animator->SetCurrentAnimClip(L"idle");

  SAFE_DELETE(srcTex);
  return animator;
}

Animator* Animations::GetSoldierSample()
{
  Texture2D* srcTex = new Texture2D(TexturePath + L"enemy_soldier_sample.png");

  AnimationClip* idle = new AnimationClip(L"idle", srcTex, 6, { 0, 0 }, { 335, 77 }, 1.0 / 6.0f, false);
  AnimationClip* die = new AnimationClip(L"die", srcTex, 11, { 0, 78 }, { 725, 153 }, 1.0 / 12.0f, false, false);

  Animator* animator = new Animator();

  animator->AddAnimClip(idle);
  animator->AddAnimClip(die);

  animator->SetCurrentAnimClip(L"idle");

  return animator;
}

//Animator* Animations::GetEriUpper() {
//  Texture2D* srcTex = new Texture2D(TexturePath + L"eri_upper.png");
//
//  AnimationClip* aim_rifle = new AnimationClip(L"aim_rifle", srcTex, 10, Vector2(0, 0), Vector2(459, 62), false, 1.0f / 12.0f, Vector2(8, 0));
//  AnimationClip* reload_rifle = new AnimationClip(L"reload_rifle", srcTex, 5, Vector2(0, 63), Vector2(224, 93), false, 1.0f / 5.0f);
//  AnimationClip* knife1_rifle = new AnimationClip(L"knife1_rifle", srcTex, 6, Vector2(0, 95), Vector2(299, 134), false, 1.0f / 12.0f);
//  AnimationClip* knife2_rifle = new AnimationClip(L"knife2_rifle", srcTex, 8, Vector2(0, 135), Vector2(415, 170), false, 1.0f / 12.0f);
//  AnimationClip* throw_rifle = new AnimationClip(L"throw_rifle", srcTex, 5, Vector2(225, 63), Vector2(459, 94), false, 1.0f / 12.0f);
//
//  Animator* animator = new Animator();
//
//  animator->AddAnimClip(aim_rifle);
//  animator->AddAnimClip(reload_rifle);
//  animator->AddAnimClip(knife1_rifle);
//  animator->AddAnimClip(knife2_rifle);
//  animator->AddAnimClip(throw_rifle);
//
//  animator->SetCurrentAnimClip(L"aimRifle");
//
//  SAFE_DELETE(srcTex);
//  return animator;
//}

//Animator* Animations::GetEriLower() {
//  Texture2D* srcTex = new Texture2D(TexturePath + L"eri_lower.png");
//
//  AnimationClip* idle = new AnimationClip(L"idle", srcTex, 1, Vector2(0, 0), Vector2(19, 25), false, -1.0f);
//  AnimationClip* run = new AnimationClip(L"run", srcTex, 12, Vector2(20, 0), Vector2(374, 25), false, 1.0f / 12.0f);
//
//  AnimationClip* jumpBegin_run = new AnimationClip(L"jumpBegin_run", srcTex, 3, Vector2(0, 26), Vector2(103, 50), false, 1.0f / 3.0f);
//  AnimationClip* jumpEnd_run = new AnimationClip(L"jumpEnd_run", srcTex, 3, Vector2(0, 51), Vector2(103, 76), false, 1.0f / 3.0f);
//
//  AnimationClip* jumpBegin_stand = new AnimationClip(L"jumpBegin_stand", srcTex, 3, Vector2(103, 26), Vector2(204, 56), false, 1.0 / 3.0f);
//  AnimationClip* jumpEnd_stand = new AnimationClip(L"jumpEnd_stand", srcTex, 3, Vector2(103, 57), Vector2(204, 88), false, 1.0 / 3.0f);
//
//  Animator* animator = new Animator();
//
//  animator->AddAnimClip(idle);
//  animator->AddAnimClip(run);
//  animator->AddAnimClip(jumpBegin_run);
//  animator->AddAnimClip(jumpEnd_run);
//  animator->AddAnimClip(jumpBegin_stand);
//  animator->AddAnimClip(jumpEnd_stand);
//
//  animator->SetCurrentAnimClip(L"idle");
//
//  SAFE_DELETE(srcTex);
//  return animator;
//}
