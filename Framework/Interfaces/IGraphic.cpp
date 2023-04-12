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

void AnimatedGraphic::getAnimator(Animator** animator) {
  *(animator) = this->animator;
}

TexturedGraphic::TexturedGraphic(GameObject* object, std::wstring path)
: IGraphic(object) {
  textureRect = new TextureRect(object->getPosition(), object->getSize(),
                                object->getRotation(), path);
}

TexturedGraphic::~TexturedGraphic() {
  SAFE_DELETE(textureRect);
}

void TexturedGraphic::update() { textureRect->Update(); }

void TexturedGraphic::render() { textureRect->Render(); }
