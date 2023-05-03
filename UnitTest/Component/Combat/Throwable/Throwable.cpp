#include "stdafx.h"
#include "Throwable.h"

#include "Component/Movement/ThrowableMovement.h"

Throwable::Throwable(GameObject* thrown, Side side, float damage, float range, std::wstring texturePath)
  : GameObject(thrown->GetPosition(), Vector3(24, 30, 0)), 
  thrown(thrown), side(side), strength(0), 
  damage(damage), range(range), texturePath(texturePath)
{
  movement = new ThrowableMovement(this, 0, 0);
  type = Type::THROWABLE;
}

Throwable::~Throwable()
{
  SAFE_DELETE(movement);
}

void Throwable::Update()
{
  auto globalSpeed = Time::Get()->GetGlobalSpeed();

  if (sinceThrown > 3.0)
  {
    bomb();
    return;
  }


  //float gravity = GameManager::Get()->GetGlobalGravity();
  //
  //if (ySpeed > fallingSpeedMax) ySpeed -= gravity;
  //else ySpeed = fallingSpeedMax;
  //
  //Move(Vector3(xSpeed, ySpeed, 0));

  if (isFirstHit) graphic->AddRotation(movement->GetXSpeed() * -2, ObjectGraphic::Type::TEXTURE);
  else
  {
    if (movement->GetXSpeedOrigin() > 0) graphic->AddRotation(-strength * globalSpeed , ObjectGraphic::Type::TEXTURE);
    else graphic->AddRotation(strength * globalSpeed, ObjectGraphic::Type::TEXTURE);
  }
  graphic->Update();
  collision->Update();
  movement->Update();

  if (movement->GetIsFalling() == false) isFirstHit = true;

  sinceThrown += Time::Get()->WorldDelta();
}

void Throwable::Render()
{
  movement->Render();
  graphic->Render();
  collision->Render();
}

bool Throwable::hit(GameObject* object)
{
  switch (object->GetObjectType())
  {
  case GameObject::Type::CHARACTER:
  case GameObject::Type::VEHICLE:
  case GameObject::Type::PROP:
  case GameObject::Type::TERRAIN:
    isBombed = true;
    break;
  case GameObject::Type::BULLET:
  case GameObject::Type::THROWABLE:
  case GameObject::Type::NONE:
    break;
  default:
    break;
  }
  return isBombed;
}

Throwable* Throwable::NewThrowable(Vector3 position, Vector3 axis, float strength)
{
  return new Throwable(thrown, side, strength, damage, range, texturePath, position, axis);
}

Throwable* Throwable::InitGrenade(GameObject* object)
{
  return new Throwable(object, Side::PLAYER, 5, 10, TexturePath + L"grenade.png");
}

Throwable::Throwable(GameObject* thrown, Side side, float strength, float damage, float range, std::wstring texturePath, Vector3 position, Vector3 axis)
  : GameObject(position, Vector3(26, 32, 0)), 
  thrown(thrown), side(side), strength(strength), 
  damage(damage), range(range), texturePath(texturePath), axis(axis)
{
  Vector3 speed = axis * strength;

  //rotateSpeed = strength;
  //if (axis.x < 0) rotateSpeed = -strength;

  movement = new ThrowableMovement(this, speed.x, speed.y);
  graphic->InitTexture(texturePath);

  collision->InitializeTop();
  collision->InitializeBase();
  collision->InitializeBottom();

  sinceThrown = 0.0;
}

void Throwable::bomb()
{
  isWaitingDelete = true;
}
