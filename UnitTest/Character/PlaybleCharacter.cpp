#include "stdafx.h"
#include "PlaybleCharacter.h"

PlaybleCharacter::PlaybleCharacter(Vector3 position, Vector3 size) 
: Character(position, size) {
  
  // Animator Init
  {
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

    animator->AddAnimClip(Idle);
    animator->AddAnimClip(Run);
    animator->AddAnimClip(Jump);
    animator->AddAnimClip(Hit);

    animator->SetCurrentAnimClip(L"Idle");

    animRect->SetAnimator(animator);

    SAFE_DELETE(srcTex);
  }

  movement = new IPlayerMovement(this);
}

PlaybleCharacter::~PlaybleCharacter() {}

void PlaybleCharacter::update() {
  movement->update();
  __super::update();
}

void PlaybleCharacter::render() { __super::render(); }
