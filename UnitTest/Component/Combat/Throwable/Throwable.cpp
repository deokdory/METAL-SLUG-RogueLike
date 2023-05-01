#include "stdafx.h"
#include "Throwable.h"

Throwable::Throwable(GameObject* thrown, Side side, float gravityOffset, float damage, float range, std::wstring texturePath)
  : GameObject(thrown->GetPosition(), Vector3(26, 32, 0)), thrown(thrown), side(side), gravityOffset(gravityOffset), strength(strength), damage(damage), range(range), texturePath(texturePath)
{
}

Throwable::~Throwable()
{
}

void Throwable::Update()
{
  float gravity = GameManager::Get()->GetGlobalGravity();

  if (ySpeed > fallingSpeedMax) ySpeed -= gravity;
  else ySpeed = fallingSpeedMax;

  Move(Vector3(xSpeed, ySpeed, 0));

  graphic->AddRotation(-xSpeed, ObjectGraphic::Type::TEXTURE);

  graphic->Update();
  collision->Update();
}

void Throwable::Render()
{
  graphic->Render();
  collision->Render();
}

void Throwable::hit(GameObject* object)
{
}

Throwable* Throwable::NewThrowable(Vector3 position, Vector3 axis, float strength)
{
  return new Throwable(thrown, side, gravityOffset, strength, damage, range, texturePath, position, axis);
}

Throwable* Throwable::InitGrenade(GameObject* object)
{
  return new Throwable(object, Side::PLAYER, 0, 5, 10, TexturePath + L"grenade.png");
}

Throwable::Throwable(GameObject* thrown, Side side, float gravityOffset, float strength, float damage, float range, std::wstring texturePath, Vector3 position, Vector3 axis)
  : GameObject(position, Vector3(26, 32, 0)), thrown(thrown), side(side), gravityOffset(gravityOffset), strength(strength), damage(damage), range(range), texturePath(texturePath), axis(axis)
{
  Vector3 speed = axis * strength;

  xSpeed = speed.x;
  ySpeed = speed.y;

  graphic->InitTexture(texturePath);

  collision->InitializeTop();
  collision->InitializeBase();
  collision->InitializeBottom();
}
