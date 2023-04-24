#include "stdafx.h"
#include "AnimatedGraphic.h"

//#include "Geometries/TextureRect.h"
//#include "Geometries/AnimationRect.h"

#include "Game/GameObject.h"

AnimatedGraphic::AnimatedGraphic(GameObject* object)
  : ObjectGraphic(object) {}

AnimatedGraphic::~AnimatedGraphic() {
  SAFE_DELETE(animRect);
  SAFE_DELETE(animator);
}

void AnimatedGraphic::Update() {

  if (animRect && animator) {

    if (object->GetFliped()) animRect->SetIsFliped(true);
    else animRect->SetIsFliped(false);

    animRect->SetPosition(object->GetPosition());
    animRect->SetSize(object->GetSize());
    animRect->SetRotation(object->GetRotation());

    animRect->Update();
    animator->Update();

  }
}

void AnimatedGraphic::Render() {
  if (animRect) animRect->Render();
}

void AnimatedGraphic::SetResource(class Animator* animator, Slot slot) {

  SAFE_DELETE(animRect);
  SAFE_DELETE(this->animator);

  animRect = new AnimationRect(object->GetPosition(), object->GetSize());
  this->animator = animator;

  this->animator->SetCurrentAnimClip(L"idle");
  animRect->SetAnimator(animator);

}

void AnimatedGraphic::SetCurrentAnimation(std::wstring name, Slot slot)
{
  animator->SetCurrentAnimClip(name);
}

void AnimatedGraphic::SetCurrentFrame(UINT index, Slot slot)
{
  animator->SetCurrentFrame(index);
}

Matrix AnimatedGraphic::GetRectWorld(Slot slot)
{
  return animRect->GetRectWorld();
}

Vector3 AnimatedGraphic::GetRectSize(Slot slot)
{
  return animRect->GetSize();
}