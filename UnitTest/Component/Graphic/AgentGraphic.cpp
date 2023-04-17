#include "stdafx.h"
#include "AgentGraphic.h"

#include "Geometries/TextureRect.h"
#include "Geometries/AnimationRect.h"

#include "Game/GameObject.h"

AgentGraphic::AgentGraphic(GameObject* object)
  : IGraphic(object) {}

AgentGraphic::~AgentGraphic() {
  SAFE_DELETE(upperRect);
  SAFE_DELETE(lowerRect);

  SAFE_DELETE(upperAnim);
  SAFE_DELETE(lowerAnim);
}

void AgentGraphic::Update() {

  auto objPos = object->GetPosition();
  auto objSize = object->GetSize();

  Vector2 lowerSize, lowerRepos;
  Vector2 upperSize, upperRepos;

  Vector3 lowerPos, upperPos;

  lowerSize = lowerRepos = upperSize = upperRepos = Values::ZeroVec2;
  lowerPos = upperPos = Values::ZeroVec3;

  if (lowerAnim && lowerRect) {
    lowerAnim->Update();

    lowerSize = lowerAnim->GetFrameSize();
    lowerRepos = lowerAnim->GetReposition();

    lowerPos = Vector3(objPos.x, objPos.y - objSize.y / 2 + lowerSize.y / 2, objPos.z) + Vector3(lowerRepos.x, lowerRepos.y, 0);

    lowerRect->SetPosition(lowerPos);
    lowerRect->SetSize({ lowerSize.x, lowerSize.y, 0.0f });

    lowerRect->Update();
  }

  if (upperAnim && upperRect) {
    upperAnim->Update();

    upperSize = upperAnim->GetFrameSize();
    upperRepos = upperAnim->GetReposition();

    if (lowerPos != Values::ZeroVec2)
      upperPos = Vector3(objPos.x, lowerPos.y + lowerSize.y / 2 + upperSize.y / 2, objPos.z)
      + Vector3(upperRepos.x, upperRepos.y, 0);
    else
      upperPos = Vector3(objPos.x, objPos.y + objSize.y / 2 - upperSize.y / 2, objPos.z)
      + Vector3(upperRepos.x, upperRepos.y, 0);

    upperRect->SetPosition(upperPos);
    upperRect->SetSize({ upperSize.x, upperSize.y, 0.0f });

    upperRect->Update();
  }
}

void AgentGraphic::Render() {
  if (lowerRect) lowerRect->Render();
  if (upperRect) upperRect->Render();
}

void AgentGraphic::SetResource(Animator* animator, Slot slot) {
  switch (slot)
  {
  case NONE:
  case LOWER:
    lowerRect = new AnimationRect(object->GetPosition(), object->GetSize());
    lowerAnim = animator;

    lowerAnim->SetCurrentAnimClip(L"idle");
    lowerRect->SetAnimator(animator);
    break;
  case UPPER:
    upperRect = new AnimationRect(object->GetPosition(), object->GetSize());
    upperAnim = animator;

    upperAnim->SetCurrentAnimClip(L"aim_rifle");
    upperRect->SetAnimator(animator);
    break;
  default:
    break;
  }
}

void AgentGraphic::SetCurrentAnimation(std::wstring name, Slot slot)
{
  switch (slot)
  {
  case NONE:
    break;
  case LOWER:
    lowerAnim->SetCurrentAnimClip(name);
    break;
  case UPPER:
    upperAnim->SetCurrentAnimClip(name);
    break;
  case MERGED:
    lowerAnim->SetCurrentAnimClip(name);
    upperAnim->SetCurrentAnimClip(name);
    break;
  default:
    break;
  }
}

void AgentGraphic::SetCurrentFrame(UINT index, Slot slot)
{
  switch (slot)
  {
  case NONE:
    break;
  case LOWER:
    lowerAnim->SetCurrentFrame(index);
    break;
  case UPPER:
    upperAnim->SetCurrentFrame(index);
    break;
  case MERGED:
    lowerAnim->SetCurrentFrame(index);
    upperAnim->SetCurrentFrame(index);
    break;
  default:
    break;
  }
}

Matrix AgentGraphic::GetWorld(Slot slot)
{
  switch (slot)
  {
  case IGraphic::NONE:
    break;
  case IGraphic::LOWER:
    return lowerRect->GetWorld();
    break;
  case IGraphic::UPPER:
    return upperRect->GetWorld();
    break;
  case IGraphic::MERGED:
    break;
  default:
    break;
  }
}
