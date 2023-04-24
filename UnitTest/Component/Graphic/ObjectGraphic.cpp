#include "stdafx.h"
#include "ObjectGraphic.h"

#include "Game/GameObject.h"

ObjectGraphic::ObjectGraphic(GameObject* object)
  : object(object)
{
  
}

ObjectGraphic::~ObjectGraphic() {}

void ObjectGraphic::Update()
{
  for (AnimationRect* animRect : animRects)
  {
    if (animRect != nullptr)
    {
      if (object->GetFliped()) animRect->SetIsFliped(true);
      else animRect->SetIsFliped(false);

      animRect->SetPosition(object->GetPosition());
      animRect->SetSize(object->GetSize());
      animRect->SetRotation(object->GetRotation());

      animRect->Update();
    }
  }
}

void ObjectGraphic::Render()
{
  for (AnimationRect* animRect : animRects)
  {
    if (animRect != nullptr) animRect->Render();
  }
}

Vector3 ObjectGraphic::GetRectPosition(Type type, Slot slot)
{
  switch (type)
  {
  case ObjectGraphic::Type::TEXTURE:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      if(texRects[0] != nullptr) return texRects[0]->GetPosition();
    case ObjectGraphic::Slot::LOWER:
      if(texRects[1] != nullptr) return texRects[1]->GetPosition();
    case ObjectGraphic::Slot::UPPER:
      if(texRects[2] != nullptr) return texRects[2]->GetPosition();
    default:
      return Values::ZeroVec3;
    }
  case ObjectGraphic::Type::ANIMATION:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      if (animRects[0] != nullptr) return animRects[0]->GetPosition();
    case ObjectGraphic::Slot::LOWER:
      if(animRects[0] != nullptr) return animRects[0]->GetPosition();
    case ObjectGraphic::Slot::UPPER:
      if(animRects[0] != nullptr) return animRects[0]->GetPosition();
    default:
      return Values::ZeroVec3;
    }
  default:
    return Values::ZeroVec3;
  }
}

Vector3 ObjectGraphic::GetRectSize(Type type, Slot slot)
{
  switch (type)
  {
  case ObjectGraphic::Type::TEXTURE:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      if (texRects[0] != nullptr) return texRects[0]->GetSize();
    case ObjectGraphic::Slot::LOWER:
      if (texRects[1] != nullptr) return texRects[1]->GetSize();
    case ObjectGraphic::Slot::UPPER:
      if (texRects[2] != nullptr) return texRects[2]->GetSize();
    default:
      return Values::ZeroVec3;
    }
  case ObjectGraphic::Type::ANIMATION:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      if (animRects[0] != nullptr) return animRects[0]->GetSize();
    case ObjectGraphic::Slot::LOWER:
      if (animRects[0] != nullptr) return animRects[0]->GetSize();
    case ObjectGraphic::Slot::UPPER:
      if (animRects[0] != nullptr) return animRects[0]->GetSize();
    default:
      return Values::ZeroVec3;
    }
  default:
    return Values::ZeroVec3;
  }
}

Matrix ObjectGraphic::GetRectWorld(Type type, Slot slot)
{
  switch (type)
  {
  case ObjectGraphic::Type::TEXTURE:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      if (texRects[0] != nullptr) return texRects[0]->GetWorld();
    case ObjectGraphic::Slot::LOWER:
      if (texRects[1] != nullptr) return texRects[1]->GetWorld();
    case ObjectGraphic::Slot::UPPER:
      if (texRects[2] != nullptr) return texRects[2]->GetWorld();
    default:
      return Values::ZeroVec3;
    }
  case ObjectGraphic::Type::ANIMATION:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      if (animRects[0] != nullptr) return animRects[0]->GetWorld();
    case ObjectGraphic::Slot::LOWER:
      if (animRects[0] != nullptr) return animRects[0]->GetWorld();
    case ObjectGraphic::Slot::UPPER:
      if (animRects[0] != nullptr) return animRects[0]->GetWorld();
    default:
      return Values::ZeroVec3;
    }
  default:
    return Values::ZeroVec3;
  }
}

bool ObjectGraphic::InitTexture(std::wstring path, Slot slot)
{
  switch (slot)
  {
  case ObjectGraphic::Slot::NORMAL:
    if (texRects[0] != nullptr)
    {
      texRects[0] = new TextureRect(object->GetPosition(), object->GetSize(), 0);
      return true;
    }
  case ObjectGraphic::Slot::LOWER:
    if (texRects[1] != nullptr)
    {
      texRects[1] = new TextureRect(object->GetPosition(), object->GetSize(), 0);
      return true;
    }
  case ObjectGraphic::Slot::UPPER:
    if (texRects[2] != nullptr)
    {
      texRects[2] = new TextureRect(object->GetPosition(), object->GetSize(), 0);
      return true;
    }
  default:
    return false;
  }
}

bool ObjectGraphic::InitAnimation(Animator* animator, Slot slot)
{
  switch (slot)
  {
  case ObjectGraphic::Slot::NORMAL:
    if (animRects[0] != nullptr && animators[0] != nullptr)
    {
      animators[0] = animator;
      animRects[0] = new AnimationRect(object->GetPosition(), object->GetSize());
      return true;
    }
  case ObjectGraphic::Slot::LOWER:
    if (animRects[1] != nullptr && animators[1] != nullptr)
    {
      animators[1] = animator;
      animRects[1] = new AnimationRect(object->GetPosition(), object->GetSize());
      return true;
    }
  case ObjectGraphic::Slot::UPPER:
    if (animRects[2] != nullptr && animators[2] != nullptr)
    {
      animators[2] = animator;
      animRects[2] = new AnimationRect(object->GetPosition(), object->GetSize());
      return true;
    }
  default:
    return false;
  }
}

void ObjectGraphic::DeleteGraphic(Type type, Slot slot)
{
  switch (type)
  {
  case ObjectGraphic::Type::TEXTURE:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      SAFE_DELETE(texRects[0]);
      break;
    case ObjectGraphic::Slot::LOWER:
      SAFE_DELETE(texRects[1]);
      break;
    case ObjectGraphic::Slot::UPPER:
      SAFE_DELETE(texRects[2]);
      break;
    default:
      break;
    }
  case ObjectGraphic::Type::ANIMATION:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      SAFE_DELETE(animRects[0]);
      break;
    case ObjectGraphic::Slot::LOWER:
      SAFE_DELETE(animRects[1]);
      break;
    case ObjectGraphic::Slot::UPPER:
      SAFE_DELETE(animRects[2]);
      break;
    default:
      break;
    }
  default:
    break;
  }
}

void ObjectGraphic::SetCurrentAnimation(std::wstring name, Slot slot)
{
  switch (slot)
  {
  case ObjectGraphic::Slot::NORMAL:
    if (animators[0] != nullptr) animators[0]->SetCurrentAnimClip(name);
  case ObjectGraphic::Slot::LOWER:
    if (animators[1] != nullptr) animators[1]->SetCurrentAnimClip(name);
  case ObjectGraphic::Slot::UPPER:
    if (animators[2] != nullptr) animators[2]->SetCurrentAnimClip(name);
  default:
    break;
  }
}

void ObjectGraphic::SetCurrentFrame(UINT index, Slot slot)
{
  switch (slot)
  {
  case ObjectGraphic::Slot::NORMAL:
    if (animators[0] != nullptr) animators[0]->SetCurrentFrame(index);
  case ObjectGraphic::Slot::LOWER:
    if (animators[1] != nullptr) animators[1]->SetCurrentFrame(index);
  case ObjectGraphic::Slot::UPPER:
    if (animators[2] != nullptr) animators[2]->SetCurrentFrame(index);
  default:
    break;
  }
}

Animator* ObjectGraphic::GetAnimator(Slot slot)
{
  switch (slot)
  {
  case ObjectGraphic::Slot::NORMAL:
    if (animators[0] != nullptr) return animators[0];
  case ObjectGraphic::Slot::LOWER:
    if (animators[1] != nullptr) return animators[1];
  case ObjectGraphic::Slot::UPPER:
    if (animators[2] != nullptr) return animators[2];
  default:
    return nullptr;
  }
}
