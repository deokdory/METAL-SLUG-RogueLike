#include "Framework.h"
#include "ObjectGraphic.h"

ObjectGraphic::ObjectGraphic(GameObject* object)
  : object(object)
{
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

      if (object->GetRotation() != 0) 
        texRects[i]->SetRotation(object->GetRotation());

      texRects[i]->Update();
    }
  }

  // Animation Basic
  Vector3 objPos = object->GetPosition();
  Vector3 objSize = object->GetSize();

  Vector2 lowerSize, lowerRepos;
  lowerSize = lowerRepos = Values::ZeroVec2;

  Vector3 lowerPos = objPos;
  //lowerPos.y -= objSize.y / 2;

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
    //normalPos.y -= objSize.y / 2;

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
    texVisible[slot] = visible;
    break;
  case ObjectGraphic::Type::ANIMATION:
    animVisible[slot] = visible;
    break;
  default:
    break;
  }
}

bool ObjectGraphic::InitTexture(std::wstring path, Slot slot )
{
  if (texRects[slot] == nullptr)
  {
    texRects[slot] = new TextureRect(object->GetPosition(), object->GetSize(), object->GetRotation(), path);
    texRects[slot]->SetAnchorPoint(anchorPoint);

    return true;
  }
  return false;
}

bool ObjectGraphic::InitAnimation(Animator* animator, Slot slot)
{
  if (animRects[slot] == nullptr && animators[slot] == nullptr)
  {
    animators[slot] = animator;
    animRects[slot] = new AnimationRect(object->GetPosition(), object->GetSize());
    animRects[slot]->SetAnchorPoint(anchorPoint);
    animRects[slot]->SetAnimator(animator);

    return true;
  }
  return false;
}

void ObjectGraphic::DeleteGraphic(Type type, Slot slot)
{
  switch (type)
  {
  case ObjectGraphic::Type::TEXTURE:
    SAFE_DELETE(texRects[slot]);
    break;
  case ObjectGraphic::Type::ANIMATION:
    SAFE_DELETE(animRects[slot]);
    break;
  }
}

void ObjectGraphic::SetCurrentAnimation(std::wstring name, Slot slot)
{
    if (animators[slot] != nullptr) animators[slot]->SetCurrentAnimClip(name);
}

void ObjectGraphic::SetCurrentFrame(UINT index, Slot slot)
{
    if (animators[slot] != nullptr) animators[slot]->SetCurrentFrame(index);
}

bool ObjectGraphic::GetIsAnimationFinish(Slot slot)
{
  return animators[slot] != nullptr ? animators[slot]->GetIsFinish() : false;
}

//void ObjectGraphic::SetAnchorPoint(AnchorPoint anchor, Type type, Slot slot)
//{
//  switch (type)
//  {
//  case ObjectGraphic::Type::TEXTURE:
//    switch (slot)
//    {
//    case ObjectGraphic::Slot::NORMAL:
//      if (texRects[0] != nullptr) texRects[0]->SetAnchorPoint(anchor);
//      break;
//    case ObjectGraphic::Slot::LOWER:
//      if(texRects[1] != nullptr) texRects[1]->SetAnchorPoint(anchor);
//      break;
//    case ObjectGraphic::Slot::UPPER:
//      if(texRects[2] != nullptr) texRects[2]->SetAnchorPoint(anchor);
//      break;
//    default:
//      break;
//    }
//    break;
//  case ObjectGraphic::Type::ANIMATION:
//    switch (slot)
//    {
//    case ObjectGraphic::Slot::NORMAL:
//      if(animRects[0] != nullptr) animRects[0]->SetAnchorPoint(anchor);
//      break;
//    case ObjectGraphic::Slot::LOWER:
//      if(animRects[1] != nullptr) animRects[1]->SetAnchorPoint(anchor);
//      break;
//    case ObjectGraphic::Slot::UPPER:
//      if(animRects[2] != nullptr) animRects[2]->SetAnchorPoint(anchor);
//      break;
//    default:
//      break;
//    }
//    break;
//  default:
//    break;
//  }
//}

void ObjectGraphic::SetUV(Vector2 startUV, Vector2 endUV, Slot slot)
{
  TextureRect* textureRect = nullptr;
  switch (slot)
  {
  case ObjectGraphic::NORMAL:
    textureRect = texRects[0];
    break;
  case ObjectGraphic::LOWER:
    textureRect = texRects[1];
    break;
  case ObjectGraphic::UPPER:
    textureRect = texRects[2];
    break;
  default:
    break;
  }

  if (textureRect == nullptr) return;

  textureRect->SetUV(startUV, endUV);
}

void ObjectGraphic::AddRotation(float rotation, Type type, Slot slot)
{
  switch (type)
  {
  case ObjectGraphic::Type::TEXTURE:
      if (texRects[slot] != nullptr) texRects[slot]->SetRotation(texRects[slot]->GetRotation() + rotation);
      break;
  case ObjectGraphic::Type::ANIMATION:
      if (animRects[slot] != nullptr) animRects[slot]->SetRotation(animRects[slot]->GetRotation() + rotation);
      break;
  default:
    break;
  }
}

void ObjectGraphic::FadeOut(float duration, Type type, Slot slot)
{
  assert(duration >= 0);

  float opacity = 0.0f;

  switch (type)
  {
  case ObjectGraphic::Type::TEXTURE:
    if (texRects[slot] != nullptr)
    {
      opacity = texRects[slot]->TextureRect::GetOpacity();
      if (texFading[slot] == false && opacity > 0.0f)
      {
        texFading[slot] = true;
        texFadeSpeed[slot] = opacity / duration;
      }
    }
    break;
  case ObjectGraphic::Type::ANIMATION:
    if (animRects[slot] != nullptr)
    {
      opacity = animRects[slot]->TextureRect::GetOpacity();
      if (animFading[slot] == false && opacity > 0.0f)
      {
        animFading[slot] = true;
        animFadeSpeed[slot] = opacity / duration;
      }
    }
    break;
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
