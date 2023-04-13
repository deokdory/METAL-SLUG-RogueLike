#include "Framework.h"
#include "IGraphic.h"

#include "Geometries/TextureRect.h"
#include "Geometries/AnimationRect.h"

#include "Game/GameObject.h"

IGraphic::IGraphic(GameObject* object) : object(object) {}

IGraphic::~IGraphic() {}

AnimatedGraphic::AnimatedGraphic(GameObject* object, Animator* animator) 
: IGraphic(object), animator(animator) {
  animRect = new AnimationRect(object->getPosition(), object->getSize());
  animRect->SetAnimator(animator);
}

AnimatedGraphic::~AnimatedGraphic() {
  SAFE_DELETE(animator);
  SAFE_DELETE(animRect);
}

void AnimatedGraphic::update() {
    animRect->SetPosition(object->getPosition());
    animRect->SetSize(object->getSize());
    animRect->SetRotation(object->getRotation());

    animRect->Update();
    animator->Update();
}

void AnimatedGraphic::render() { 
  animRect->Render(); }

TexturedGraphic::TexturedGraphic(GameObject* object, std::wstring path)
: IGraphic(object) {
  textureRect = new TextureRect(object->getPosition(), object->getSize(),
                                object->getRotation(), path);
}

TexturedGraphic::~TexturedGraphic() {
  SAFE_DELETE(textureRect);
}

void TexturedGraphic::update() { 
  textureRect->SetPosition(object->getPosition());
  textureRect->SetSize(object->getSize());
  textureRect->SetRotation(object->getRotation());

  textureRect->Update(); 
}

void TexturedGraphic::render() { textureRect->Render(); }

AgentGraphic::AgentGraphic(GameObject* object, Animator* lowerAnim,
                           Animator* upperAnim)
    : IGraphic(object), lowerAnim(lowerAnim), upperAnim(upperAnim) {

  auto objPos = object->getPosition();

  auto lowerSize = lowerAnim->GetFrameSize();
  auto upperSize = upperAnim->GetFrameSize();

  auto lowerRepos = lowerAnim->GetReposition();
  auto upperRepos = upperAnim->GetReposition();

  auto lowerPos = Vector3(objPos.x, objPos.y - lowerSize.y / 2, objPos.z) +
                  Vector3(lowerRepos.x, lowerRepos.y, 0.f);

  lowerRect = new AnimationRect(lowerPos, {lowerSize.x, lowerSize.y, 0.0f});

  auto upperPos = Vector3(objPos.x, objPos.y + upperSize.y / 2, objPos.z) +
                  Vector3(upperRepos.x, upperRepos.y, 0.f);

  upperRect = new AnimationRect(upperPos, {upperSize.x, upperSize.y, 0.0f});

  lowerRect->SetAnimator(lowerAnim);
  upperRect->SetAnimator(upperAnim);
}

AgentGraphic::~AgentGraphic() {
  SAFE_DELETE(upperRect);
  SAFE_DELETE(lowerRect);

  SAFE_DELETE(upperAnim);
  SAFE_DELETE(lowerAnim);
}

void AgentGraphic::update() {

  if (lowerAnim != nullptr && upperAnim != nullptr) {

    auto objPos = object->getPosition();
    auto objSize = object->getSize();

    auto lowerSize = lowerAnim->GetFrameSize();
    auto upperSize = upperAnim->GetFrameSize();

    auto totalSize = lowerSize + upperSize;

    auto lowerRepos = lowerAnim->GetReposition();
    auto upperRepos = upperAnim->GetReposition();

    auto lowerPos =
        Vector3(objPos.x, objPos.y - objSize.y / 2 + lowerSize.y / 2,
                objPos.z) +
        Vector3(lowerRepos.x, lowerRepos.y, 0.f);

    auto upperPos =
        Vector3(objPos.x, lowerPos.y + lowerSize.y / 2 + upperSize.y / 2,
                objPos.z) +
        Vector3(lowerRepos.x, lowerRepos.y, 0.f);

    lowerAnim->Update();
    upperAnim->Update();

    lowerRect->SetPosition(lowerPos);
    lowerRect->SetSize({lowerSize.x, lowerSize.y, 0.0f});

    upperRect->SetPosition(upperPos);
    upperRect->SetSize({upperSize.x, upperSize.y, 0.0f});

    lowerRect->Update();
    upperRect->Update();
  }
}

void AgentGraphic::render() {
  lowerRect->Render();
  upperRect->Render();
}
