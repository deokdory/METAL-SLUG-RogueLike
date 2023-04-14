#include "Framework.h"
#include "IGraphic.h"

#include "Geometries/TextureRect.h"
#include "Geometries/AnimationRect.h"

#include "Game/GameObject.h"

IGraphic::IGraphic(GameObject* object) : object(object) {}

IGraphic::~IGraphic() {}

AnimatedGraphic::AnimatedGraphic(GameObject* object)
: IGraphic(object) {}

AnimatedGraphic::~AnimatedGraphic() {
  SAFE_DELETE(animRect);
  SAFE_DELETE(animator);
}

void AnimatedGraphic::update() {

  if (animRect && animator) {

    animRect->SetPosition(object->getPosition());
    animRect->SetSize(object->getSize());
    animRect->SetRotation(object->getRotation());

    animRect->Update();
    animator->Update();

  }
}

void AnimatedGraphic::render() { 
  if (animRect) animRect->Render();
}

void AnimatedGraphic::setResource(Animator* animator, UINT slot) {
  SAFE_DELETE(animRect);
  SAFE_DELETE(this->animator);

  animRect = new AnimationRect(object->getPosition(), object->getSize());
  this->animator = animator;

  this->animator->SetCurrentAnimClip(L"idle");
  animRect->SetAnimator(animator);
}

TexturedGraphic::TexturedGraphic(GameObject* object)
: IGraphic(object) {}

TexturedGraphic::~TexturedGraphic() {
  SAFE_DELETE(textureRect);
}

void TexturedGraphic::update() { 
  if (textureRect) {
    textureRect->SetPosition(object->getPosition());
    textureRect->SetSize(object->getSize());
    textureRect->SetRotation(object->getRotation());

    textureRect->Update();
  }
}

void TexturedGraphic::render() { if(textureRect) textureRect->Render(); }

void TexturedGraphic::setResource(std::wstring path) {
  SAFE_DELETE(textureRect);
  textureRect = new TextureRect(object->getPosition(), object->getSize(),
                                object->getRotation(), path);
}

AgentGraphic::AgentGraphic(GameObject* object)
    : IGraphic(object) {}

AgentGraphic::~AgentGraphic() {
  SAFE_DELETE(upperRect);
  SAFE_DELETE(lowerRect);

  SAFE_DELETE(upperAnim);
  SAFE_DELETE(lowerAnim);
}

void AgentGraphic::update() {

  auto objPos = object->getPosition();
  auto objSize = object->getSize();

  if (lowerAnim && lowerRect) {
    lowerAnim->Update();

    auto lowerSize = lowerAnim->GetFrameSize();
    auto lowerRepos = lowerAnim->GetReposition();

    auto lowerPos =
        Vector3(objPos.x, objPos.y - objSize.y / 2 + lowerSize.y / 2, objPos.z);
    lowerRect->SetPosition(lowerPos);
    lowerRect->SetSize({lowerSize.x, lowerSize.y, 0.0f});

    lowerRect->Update();
  }

  if (upperAnim && upperRect) {
    upperAnim->Update();

    auto upperSize = upperAnim->GetFrameSize();
    auto upperRepos = upperAnim->GetReposition();

    auto upperPos =
        Vector3(objPos.x, objPos.y + objSize.y / 2 - upperSize.y / 2, objPos.z);
    upperRect->SetPosition(upperPos);
    upperRect->SetSize({upperSize.x, upperSize.y, 0.0f});

    upperRect->Update();
  }
}

void AgentGraphic::render() {
  if(lowerRect) lowerRect->Render();
  if(upperRect) upperRect->Render();
}

void AgentGraphic::setResource(Animator* animator, UINT slot) { 
  switch (slot) {
    case LOWER: {
      SAFE_DELETE(lowerRect);
      SAFE_DELETE(lowerAnim);

      lowerRect = new AnimationRect(object->getPosition(), object->getSize());
      lowerAnim = animator;

      lowerAnim->SetCurrentAnimClip(L"idle");
      lowerRect->SetAnimator(animator);
      break;
    }

    case UPPER: {
      SAFE_DELETE(upperRect);
      SAFE_DELETE(upperAnim);

      upperRect = new AnimationRect(object->getPosition(), object->getSize());
      upperAnim = animator;

      upperAnim->SetCurrentAnimClip(L"idle");
      upperRect->SetAnimator(animator);
      break;
    }
  }
}
