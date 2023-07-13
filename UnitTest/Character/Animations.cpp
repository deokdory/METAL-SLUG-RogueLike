#include "stdafx.h"
#include "Animations.h"

Animator* Animations::GetEriUpper() {
  Texture2D* srcTex = new Texture2D(TexturePath + L"eri_upper_x2.png");

  AnimationClip* aim_rifle = new AnimationClip(L"aim_rifle", srcTex, 10, Vector2(0, 0), Vector2(919, 125), -1.f, false, false, Vector2(16, -52));

  AnimationClip* reload_rifle = new AnimationClip(L"reload_rifle", srcTex, 5, Vector2(0, 128), Vector2(449, 183), 1.0f / 5.0f,  false, false, Vector2(15, -29));
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

  AnimationClip* jumpBegin_stand = new AnimationClip(L"jumpBegin_stand", srcTex, 6, Vector2(208, 52), Vector2(615, 113), 1.0f / 24.0f, false, false);
  AnimationClip* jumpEnd_stand = new AnimationClip(L"jumpEnd_stand", srcTex, 6, Vector2(208, 52), Vector2(615, 113), 1.0f / 12.0f, true, false);

  AnimationClip* slide = new AnimationClip(L"slide", srcTex, 3, Vector2(0, 155), Vector2(299, 202), 1.0f / 24.0f, false, false);

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

Animator* Animations::GetSoldierKnife()
{
  Texture2D* srcTex = new Texture2D(TexturePath + L"enemy_soldier_sample.png");

  AnimationClip* idle = new AnimationClip(L"idle", srcTex, 6, { 0, 0 }, { 336, 77 }, 1.0f / 6.0f, false);
  AnimationClip* hit = new AnimationClip(L"hit", srcTex, 4, { 337, 0 }, { 600, 77 }, 1.0 / 24.0f, false, false);
  AnimationClip* die = new AnimationClip(L"die", srcTex, 11, { 0, 80 }, { 725, 153 }, 1.0f / 18.0f, false, false);
  AnimationClip* scream = new AnimationClip(L"scream", srcTex, 11, { 0, 155 }, { 989, 242 }, 1.0f / 18.0f, false, false);
  AnimationClip* run = new AnimationClip(L"run", srcTex, 10, { 0, 243 }, { 699, 324 }, 1.0f / 12.0f, true);

  AnimationClip* knife1 = new AnimationClip(L"knife1", srcTex, 12, { 0, 325 }, { 1367, 402 }, 1.0f / 32.0f, false, false, Vector2(20, 0));
  AnimationClip* knife2 = new AnimationClip(L"knife2", srcTex, 12, { 0, 403 }, { 1367, 481 }, 1.0f / 32.0f, false, false, Vector2(20, 0));

  AnimationClip* knifeReverse = new AnimationClip(L"knifeReverse", srcTex, 12, { 0, 325 }, { 1367, 402 }, 1.0f / 24.0f, true, false, Vector2(20, 0));


  Animator* animator = new Animator();

  animator->AddAnimClip(idle);
  animator->AddAnimClip(hit);
  animator->AddAnimClip(die);
  animator->AddAnimClip(scream);
  animator->AddAnimClip(run);
  animator->AddAnimClip(knife1);
  animator->AddAnimClip(knife2);
  animator->AddAnimClip(knifeReverse);

  animator->SetCurrentAnimClip(L"idle");

  SAFE_DELETE(srcTex);
  return animator;
}

Animator* Animations::GetSoldierBazooka()
{
  Texture2D* srcTex = new Texture2D(TexturePath + L"enemy_soldier_bzk.png");
  Texture2D* knifeSrcTex = new Texture2D(TexturePath + L"enemy_soldier_sample.png");

  Animator* animator = new Animator();

  animator->AddAnimClip(new AnimationClip(L"idle", srcTex, 6, { 0, 0 }, { 563, 95 }, 1.0f / 6.0f, false, true));
  animator->AddAnimClip(new AnimationClip(L"hit", srcTex, 4, { 564, 0 }, { 939, 95 }, 1.0f / 24.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"run", srcTex, 6, { 0, 96 }, { 1011, 183 }, 1.0f / 12.0f, false, true));
  animator->AddAnimClip(new AnimationClip(L"scream", srcTex, 6, { 0, 185 }, { 989, 271 }, 1.0f / 18.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"die", knifeSrcTex, 11, { 0, 80 }, { 725, 153 }, 1.0f / 18.0f, false, false));

  animator->AddAnimClip(new AnimationClip(L"aimPreUp", srcTex, 3, { 0, 272 }, { 329, 389 }, 1.0f / 24.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"aimPreUpReverse", srcTex, 3, { 0, 272 }, { 329, 389 }, 1.0f / 24.0f, true, false));

  animator->AddAnimClip(new AnimationClip(L"aimFront", srcTex, 1, { 330, 272 }, { 659, 389 }, 1.0f / 24.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"aimUp30", srcTex, 3, { 330, 272 }, { 549, 389 }, 1.0f / 24.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"aimUp45", srcTex, 3, { 330, 272 }, { 659, 389 }, 1.0f / 24.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"aimUp70", srcTex, 4, { 330, 272 }, { 769, 389 }, 1.0f / 24.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"aimUp90", srcTex, 5, { 330, 272 }, { 879, 389 }, 1.0f / 24.0f, false, false));

  animator->AddAnimClip(new AnimationClip(L"aimUp30reverse", srcTex, 2, { 330, 272 }, { 549, 389 }, 1.0f / 24.0f, true, false));
  animator->AddAnimClip(new AnimationClip(L"aimUp45reverse", srcTex, 3, { 330, 272 }, { 659, 389 }, 1.0f / 24.0f, true, false));
  animator->AddAnimClip(new AnimationClip(L"aimUp70reverse", srcTex, 4, { 330, 272 }, { 769, 389 }, 1.0f / 24.0f, true, false));
  animator->AddAnimClip(new AnimationClip(L"aimUp90reverse", srcTex, 5, { 330, 272 }, { 879, 389 }, 1.0f / 24.0f, true, false));

  animator->AddAnimClip(new AnimationClip(L"aimPreDown", srcTex, 3, { 0, 390 }, { 329, 495 }, 1.0f / 24.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"aimPreDownReverse", srcTex, 3, { 0, 390 }, { 329, 495 }, 1.0f / 24.0f, true, false));

  animator->AddAnimClip(new AnimationClip(L"aimDown30", srcTex, 1, { 330, 390 }, { 439, 495 }, 1.0f / 24.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"aimDown45", srcTex, 2, { 330, 390 }, { 549, 495 }, 1.0f / 24.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"aimDown70", srcTex, 3, { 330, 390 }, { 659, 495 }, 1.0f / 24.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"aimDown90", srcTex, 4, { 330, 390 }, { 769, 495 }, 1.0f / 24.0f, false, false));

  animator->AddAnimClip(new AnimationClip(L"aimDown45reverse", srcTex, 2, { 330, 390 }, { 549, 495 }, 1.0f / 24.0f, true, false));
  animator->AddAnimClip(new AnimationClip(L"aimDown70reverse", srcTex, 3, { 330, 390 }, { 659, 495 }, 1.0f / 24.0f, true, false));
  animator->AddAnimClip(new AnimationClip(L"aimDown90reverse", srcTex, 4, { 330, 390 }, { 769, 495 }, 1.0f / 24.0f, true, false));

  animator->AddAnimClip(new AnimationClip(L"fireFront", srcTex, 3, { 880, 272 }, { 1209, 389 }, 1.0f / 12.0f, false, false));

  animator->AddAnimClip(new AnimationClip(L"fireUp30", srcTex, 3, { 0, 602 }, { 329, 719 }, 1.0f / 12.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"fireUp45", srcTex, 3, { 330,602 }, { 659, 719 }, 1.0f / 12.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"fireUp70", srcTex, 3, { 660,602 }, { 989, 719 }, 1.0f / 12.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"fireUp90", srcTex, 3, { 990,602 }, { 1319, 719 }, 1.0f / 12.0f, false, false));

  animator->AddAnimClip(new AnimationClip(L"fireDown30", srcTex, 3, { 0, 496 }, { 329, 601 }, 1.0f / 12.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"fireDown45", srcTex, 3, { 330, 496 }, { 659, 601 }, 1.0f / 12.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"fireDown70", srcTex, 3, { 660, 496 }, { 989, 601 }, 1.0f / 12.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"fireDown90", srcTex, 3, { 990, 496 }, { 1319, 601 }, 1.0f / 12.0f, false, false));

  animator->AddAnimClip(new AnimationClip(L"jump", srcTex, 6, { 0, 720 }, { 575, 807 }, 1.0f / 12.0f, false, false));
  animator->AddAnimClip(new AnimationClip(L"land", srcTex, 2, { 576, 720 }, { 751, 807 }, 1.0f / 12.0f, false, false));

  animator->SetCurrentAnimClip(L"idle");

  SAFE_DELETE(srcTex);
  SAFE_DELETE(knifeSrcTex);

  return animator;
}

Animator* Animations::GetElevator()
{
  Texture2D* srcTex = new Texture2D(TexturePath + L"elevator.png");

  AnimationClip* idle = new AnimationClip(L"idle", srcTex, 6, { 0, 0 }, { 1908, 192 }, 1.0f / 15.0f, false);
  Animator* animator = new Animator();
  animator->AddAnimClip(idle);
  animator->SetCurrentAnimClip(L"idle");

  SAFE_DELETE(srcTex);
  return animator;
}