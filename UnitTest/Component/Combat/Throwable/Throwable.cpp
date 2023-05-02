#include "stdafx.h"
#include "Throwable.h"

Throwable::Throwable(GameObject* thrown, Side side, float gravityOffset, float damage, float range, std::wstring texturePath)
  : GameObject(thrown->GetPosition(), Vector3(26, 32, 0)), thrown(thrown), side(side), gravityOffset(gravityOffset), strength(0), damage(damage), range(range), texturePath(texturePath)
{
  type = Type::THROWABLE;
}

Throwable::~Throwable()
{
}

void Throwable::Update()
{
  if (collisionCheck() == true || sinceThrown > 3.0)
  {
    bomb();
    return;
  }

  float gravity = GameManager::Get()->GetGlobalGravity();

  if (ySpeed > fallingSpeedMax) ySpeed -= gravity;
  else ySpeed = fallingSpeedMax;

  Move(Vector3(xSpeed, ySpeed, 0));

  graphic->AddRotation(xSpeed, ObjectGraphic::Type::TEXTURE);

  graphic->Update();
  collision->Update();

  sinceThrown += Time::Get()->WorldDelta();
}

void Throwable::Render()
{
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

  sinceThrown = 0.0;
}

bool Throwable::collisionCheck()
{
  auto level = GameManager::Get()->GetCurrentLevel();
  auto& terrains = level->GetTerrains();
  auto& objects = level->GetObjects();

  BoundingBox* throwableBox = collision->GetBase();
  BoundingBox* objectBox = nullptr;

  for (GameObject* obj : objects)
  {
    if (obj == this || obj == thrown) continue;

    objectBox = obj->GetCollision()->GetBase();
    if (BoundingBox::AABB(throwableBox, objectBox))
    {
      if(hit(obj)) return true;
    }
  }

  BoundingBox *terrainTop, *terrainBase, *terrainBottom;
  terrainTop = terrainBase = terrainBottom = nullptr;

  for (Terrain* terr : terrains)
  {
    terrainTop = terr->GetCollision()->GetTop();
    terrainBase = terr->GetCollision()->GetBase();
    terrainBottom = terr->GetCollision()->GetBottom();

    if (BoundingBox::AABB(throwableBox, terrainTop))
    {
      if (ySpeed < 0) ySpeed *= -0.5f;

      xSpeed * 0.5f;
    }

    if (BoundingBox::AABB(throwableBox, terrainBase))
    {
      xSpeed *= -1.f;
    }

    if (BoundingBox::AABB(throwableBox, terrainBottom))
    {
      ySpeed = 0;
    }
  }
}

void Throwable::bomb()
{
  isWaitingDelete = true;
}
