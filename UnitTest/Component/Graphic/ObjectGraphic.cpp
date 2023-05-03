#include "stdafx.h"
#include "ObjectGraphic.h"

#include "Game/GameObject.h"

ObjectGraphic::ObjectGraphic(GameObject* object)
  : object(object)
{

//  for (int i = 0; i < 3; i++) texRects[i] = nullptr;
//  for (int i = 0; i < 3; i++) animators[i] = nullptr;
//  for (int i = 0; i < 3; i++) animRects[i] = nullptr;

  texRects.assign(3, nullptr);
  animators.assign(3, nullptr);
  animRects.assign(3, nullptr);

  for (int i = 0; i < 3; i++)
  {
    texVisible[i] = animVisible[i] = true;
  }
}

ObjectGraphic::~ObjectGraphic() {
  for (int i = 0; i < 3; i++)
  {
    SAFE_DELETE(animators[i]);
    SAFE_DELETE(animRects[i]);
    SAFE_DELETE(texRects[i]);
  }
  animators.clear();
  animRects.clear();
  texRects.clear();
}

void ObjectGraphic::Update()
{

  float globalSpeed = Time::Get()->GetGlobalSpeed();

  // Textures
  for (int i = 0; i < 3; i++)
  {
    if (texRects[i] != nullptr && texVisible[i])
    {
      texRects[i]->SetPosition(object->GetPosition());
      texRects[i]->SetSize(object->GetSize());

      if (object->GetRotation() != 0) texRects[i]->SetRotation(object->GetRotation());

      texRects[i]->Update();
    }
  }

  // Animation Basic
  Vector3 objPos = object->GetPosition();
  Vector3 objSize = object->GetSize();

  Vector2 lowerSize, lowerRepos;
  lowerSize = lowerRepos = Values::ZeroVec2;

  Vector3 lowerPos = objPos;
  lowerPos.y -= objSize.y / 2;

  // NORMAL
  if (animRects[0] != nullptr && animators[0] != nullptr && animVisible[0])
  {
    animators[0]->Update();

    Vector3 normalSize = animators[0]->GetFrameSize();
    Vector3 normalRepos = animators[0]->GetReposition();

    if (object->GetIsFliped())
    {
      animRects[0]->SetIsFliped(true);
      normalRepos.x *= -1;
    }
    else animRects[0]->SetIsFliped(false);

    Vector3 normalPos = objPos;
    normalPos.y -= objSize.y / 2;

    normalPos += Vector3(normalRepos.x, normalRepos.y, 0);

    animRects[0]->SetPosition(normalPos);
    animRects[0]->SetSize({ normalSize.x, normalSize.y, 0.0f });

    animRects[0]->Update();
  }


  // LOWER
  if (animRects[1] != nullptr && animators[1] != nullptr && animVisible[1])
  {
    animators[1]->Update();

    lowerSize = animators[1]->GetFrameSize();
    lowerRepos = animators[1]->GetReposition();

    if (object->GetIsFliped())
    {
      animRects[1]->SetIsFliped(true);
      lowerRepos.x *= -1;
    }
    else animRects[1]->SetIsFliped(false);

    lowerPos += Vector3(lowerRepos.x, lowerRepos.y, 0);

    animRects[1]->SetPosition(lowerPos);
    animRects[1]->SetSize({ lowerSize.x, lowerSize.y, 0.0f });

    animRects[1]->Update();
  }

  Vector2 upperSize, upperRepos;
  upperSize = upperRepos = Values::ZeroVec2;

  Vector3 upperPos = objPos;
  upperPos.y -= objSize.y / 2;

  // UPPER
  if (animRects[2] != nullptr && animators[2] != nullptr && animVisible[2])
  {
    animators[2]->Update();

    upperSize = animators[2]->GetFrameSize();
    upperRepos = animators[2]->GetReposition();

    if (object->GetIsFliped())
    {
      animRects[2]->SetIsFliped(true);
      upperRepos.x *= -1;
    }
    else animRects[2]->SetIsFliped(false);

    if (animRects[1] != nullptr && animators[1] != nullptr)
    {
      upperPos.y += lowerSize.y;
    }
    upperPos += Vector3(upperRepos.x, upperRepos.y, 0);

    animRects[2]->SetPosition(upperPos);
    animRects[2]->SetSize({ upperSize.x, upperSize.y, 0.0f });

    animRects[2]->Update();
  }

  // OPACITY
  {
    float opacity = 0.0f;

    for (int i = 0; i < 3; i++)
    {
      if (texFading[i])
      {
        opacity = texRects[i]->TextureRect::GetOpacity();
        if (opacity > 0.0f) opacity -= Time::Get()->WorldDelta() * texFadeSpeed[i];
        else
        {
          opacity = 0.0f;
          texFading[i] = false;
          texFadeSpeed[i] = 0.0f;
        }
        texRects[i]->TextureRect::SetOpacity(opacity);
      }
    }

    for (int i = 0; i < 3; i++)
    {
      if (animFading[i])
      {
        opacity = animRects[i]->TextureRect::GetOpacity();
        if (opacity > 0.0f) opacity -= Time::Get()->WorldDelta() * animFadeSpeed[i];
        else
        {
          opacity = 0.0f;
          animFading[i] = false;
          animFadeSpeed[i] = 0.0f;
        }
        animRects[i]->TextureRect::SetOpacity(opacity);
      }
    }

  }
}

void ObjectGraphic::Render()
{
  for (int i = 0; i < 3; i++)
  {
    if (texRects[i] != nullptr && texVisible[i]) texRects[i]->Render();
  }

  for (int i = 0; i < 3; i++)
  {
    if (animRects[i] != nullptr && animVisible[i]) animRects[i]->Render();
  }
}

void ObjectGraphic::SetVisible(bool visible, Type type, Slot slot)
{
  switch (type)
  {
  case ObjectGraphic::Type::TEXTURE:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      texVisible[0] = visible;
      break;
    case ObjectGraphic::Slot::LOWER:
      texVisible[1] = visible;
      break;
    case ObjectGraphic::Slot::UPPER:
      texVisible[2] = visible;
      break;
    default:
      break;
    }
    break;
  case ObjectGraphic::Type::ANIMATION:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      animVisible[0] = visible;
      break;
    case ObjectGraphic::Slot::LOWER:
      animVisible[1] = visible;
      break;
    case ObjectGraphic::Slot::UPPER:
      animVisible[2] = visible;
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

bool ObjectGraphic::InitTexture(std::wstring path, Slot slot )
{
  switch (slot)
  {
  case ObjectGraphic::Slot::NORMAL:
    if (texRects[0] == nullptr)
    {
      texRects[0] = new TextureRect(object->GetPosition(), object->GetSize(), 0, path);
      return true;
    }
    return false;
  case ObjectGraphic::Slot::LOWER:
    if (texRects[1] == nullptr)
    {
      texRects[1] = new TextureRect(object->GetPosition(), object->GetSize(), 0, path);
      return true;
    }
    return false;
  case ObjectGraphic::Slot::UPPER:
    if (texRects[2] == nullptr)
    {
      texRects[2] = new TextureRect(object->GetPosition(), object->GetSize(), 0, path);
      return true;
    }
    return false;
  default:
    return false;
  }
}

bool ObjectGraphic::InitAnimation(Animator* animator, Slot slot)
{
  switch (slot)
  {
  case ObjectGraphic::Slot::NORMAL:
    if (animRects[0] == nullptr && animators[0] == nullptr)
    {
      animators[0] = animator;
      animRects[0] = new AnimationRect(object->GetPosition(), object->GetSize());
      animRects[0]->SetAnchorPoint(MID_BOT);
      animRects[0]->SetAnimator(animator);

      return true;
    }
  case ObjectGraphic::Slot::LOWER:
    if (animRects[1] == nullptr && animators[1] == nullptr)
    {
      animators[1] = animator;
      animRects[1] = new AnimationRect(object->GetPosition(), object->GetSize());
      animRects[1]->SetAnchorPoint(MID_BOT);
      animRects[1]->SetAnimator(animator);

      return true;
    }
  case ObjectGraphic::Slot::UPPER:
    if (animRects[2] == nullptr && animators[2] == nullptr)
    {
      animators[2] = animator;
      animRects[2] = new AnimationRect(object->GetPosition(), object->GetSize());
      animRects[2]->SetAnchorPoint(MID_BOT);
      animRects[2]->SetAnimator(animator);

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
    break;
  case ObjectGraphic::Slot::LOWER:
    if (animators[1] != nullptr) animators[1]->SetCurrentAnimClip(name);
    break;
  case ObjectGraphic::Slot::UPPER:
    if (animators[2] != nullptr) animators[2]->SetCurrentAnimClip(name);
    break;
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
    break;
  case ObjectGraphic::Slot::LOWER:
    if (animators[1] != nullptr) animators[1]->SetCurrentFrame(index);
    break;
  case ObjectGraphic::Slot::UPPER:
    if (animators[2] != nullptr) animators[2]->SetCurrentFrame(index);
    break;
  default:
    break;
  }
}

void ObjectGraphic::SetAnchorPoint(AnchorPoint anchor, Type type, Slot slot)
{
  switch (type)
  {
  case ObjectGraphic::Type::TEXTURE:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      if (texRects[0] != nullptr) texRects[0]->SetAnchorPoint(anchor);
      break;
    case ObjectGraphic::Slot::LOWER:
      if(texRects[1] != nullptr) texRects[1]->SetAnchorPoint(anchor);
      break;
    case ObjectGraphic::Slot::UPPER:
      if(texRects[2] != nullptr) texRects[2]->SetAnchorPoint(anchor);
      break;
    default:
      break;
    }
    break;
  case ObjectGraphic::Type::ANIMATION:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      if(animRects[0] != nullptr) animRects[0]->SetAnchorPoint(anchor);
      break;
    case ObjectGraphic::Slot::LOWER:
      if(animRects[1] != nullptr) animRects[1]->SetAnchorPoint(anchor);
      break;
    case ObjectGraphic::Slot::UPPER:
      if(animRects[2] != nullptr) animRects[2]->SetAnchorPoint(anchor);
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

void ObjectGraphic::AddRotation(float rotation, Type type, Slot slot)
{
  switch (type)
  {
  case ObjectGraphic::Type::TEXTURE:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      if(texRects[0] != nullptr) texRects[0]->SetRotation(texRects[0]->GetRotation() + rotation);
      break;
    case ObjectGraphic::Slot::LOWER:
      if(texRects[1] != nullptr) texRects[1]->SetRotation(texRects[1]->GetRotation() + rotation);
      break;
    case ObjectGraphic::Slot::UPPER:
      if(texRects[2] != nullptr) texRects[2]->SetRotation(texRects[2]->GetRotation() + rotation);
      break;
    default:
      break;
    }
    break;
  case ObjectGraphic::Type::ANIMATION:
    switch (slot)
    {
    case ObjectGraphic::Slot::NORMAL:
      if (animRects[0] != nullptr) animRects[0]->SetRotation(animRects[0]->GetRotation() + rotation);
      break;
    case ObjectGraphic::Slot::LOWER:
      if (animRects[1] != nullptr) animRects[1]->SetRotation(animRects[1]->GetRotation() + rotation);
      break;
    case ObjectGraphic::Slot::UPPER:
      if (animRects[2] != nullptr) animRects[2]->SetRotation(animRects[2]->GetRotation() + rotation);
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

void ObjectGraphic::FadeOut(float duration, Type type, Slot slot)
{
  assert(duration > 0);

  float opacity = 0.0f;
  int slotNum = -1;

  switch (slot)
  {
  case ObjectGraphic::Slot::NORMAL:
    slotNum = 0;
    break;
  case ObjectGraphic::Slot::LOWER:
    slotNum = 1;
    break;
  case ObjectGraphic::Slot::UPPER:
    slotNum = 2;
    break;
  default:
    break;
  }

  if (slotNum >= 0)
  {

    if (type == ObjectGraphic::Type::TEXTURE)
    {
      if (texRects[slotNum] != nullptr)
      {
        opacity = texRects[slotNum]->TextureRect::GetOpacity();
        if (texFading[slotNum] == false && opacity > 0.0f)
        {
          texFading[slotNum] = true;
          texFadeSpeed[slotNum] = opacity / duration;
        }
      }
    }
    else if (type == ObjectGraphic::Type::ANIMATION)
    {
      if (animRects[slotNum] != nullptr)
      {
        opacity = animRects[slotNum]->TextureRect::GetOpacity();
        if (animFading[slotNum] == false && opacity > 0.0f)
        {
          animFading[slotNum] = true;
          animFadeSpeed[slotNum] = opacity / duration;
        }
      }
    }
  }
}

//Animator* ObjectGraphic::GetAnimator(Slot slot)
//{
//  switch (slot)
//  {
//  case ObjectGraphic::Slot::NORMAL:
//    if (animators[0] != nullptr) return animators[0];
//  case ObjectGraphic::Slot::LOWER:
//    if (animators[1] != nullptr) return animators[1];
//  case ObjectGraphic::Slot::UPPER:
//    if (animators[2] != nullptr) return animators[2];
//  default:
//    return nullptr;
//  }
//}
