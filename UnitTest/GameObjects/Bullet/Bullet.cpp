#include "stdafx.h"
#include "Bullet.h"

#include "Character/Character.h"

Bullet::Bullet(GameObject* fired, Side side, float speed, float damage, std::wstring texturePath)
: GameObject(fired->GetPosition(), Vector3(62, 14, 0)), fired(fired), side(side), speed(speed), damage(damage), texturePath(texturePath)
{
  objectType = Type::BULLET;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
  if (isHit)
  {
    graphic->SetVisible(false, ObjectGraphic::Type::TEXTURE);
    isWaitingDelete = true;
  }
  else
  {
    if (flyingTime >= 0.5)
      isWaitingDelete = true;

    flyingTime += Time::Get()->WorldDelta();

    Move(axis * (speed * Time::Get()->GetGlobalSpeed()));

    graphic->Update();
    collision->Update();

    terrainCollisionCheck();
  }
}

void Bullet::Render()
{
  if (isHit) return;
  
  graphic->Render();
  collision->Render();
  
}


void Bullet::hit(GameObject* object)
{
  auto objectType = object->GetObjectType();
  switch (objectType)
  {
  case GameObject::Type::VEHICLE:
  case GameObject::Type::PROP:
  case GameObject::Type::TERRAIN:
    isHit = true; // 탈것, 사물, 지형에 부딪히면 기능을 상실함(사라짐)
    return;
  }

  if (objectType == GameObject::Type::CHARACTER) // 캐릭터와 부딪혔다면 (적군 포함)
  {
    if (object->GetIsActived())
    {
      Character* character = dynamic_cast<Character*>(object); // 게임오브젝트 클래스 포인터를 다운캐스팅
      if (character->GetIsDead() == false)
      {
        character->Damaged(damage); // 캐릭터에게 대미지를 입히고
        isHit = true; // 기능을 상실함
      }
    }
  }
}

Bullet* Bullet::NewBullet(Vector3 position, Vector3 axis)
{
  return new Bullet(fired, side, speed, damage, texturePath, position, axis);
}

bool Bullet::terrainCollisionCheck()
{
  auto level = GameManager::Get()->GetCurrentLevel();

  auto& objects = level->GetObjects();
  auto& terrains = level->GetTerrains();

  BoundingBox* objectBase = nullptr;
  BoundingBox* bulletBox = collision->GetBase();

  for (GameObject* obj : objects)
  {
    if (obj == fired || obj == this) continue;

    objectBase = obj->GetCollision()->GetBase();

    if (BoundingBox::OBB(bulletBox, objectBase))
    {
      hit(obj);
    }
  }

  BoundingBox* terrainBase = nullptr;
  for (Terrain* terr : terrains)
  {
    terrainBase = terr->GetCollision()->GetBase();
    if (BoundingBox::OBB(bulletBox, terrainBase))
    {
      isHit = true;
    }
  }
  return isHit;
}

Bullet::Bullet(GameObject* fired, Side side, float speed, float damage, std::wstring texturePath, Vector3 position, Vector3 axis)
  : GameObject(position, Vector3(62, 14, 0)), fired(fired), side(side), speed(speed), damage(damage), axis(axis), texturePath(texturePath)
{
  
    auto rotateChecker = D3DXVec3Dot(&axis, &Values::UpVec);
    auto bulletRotate = D3DXVec3Dot(&axis, &Values::RightVec);

    bool isOver180 = true;
    if (rotateChecker < 0) isOver180 = false;

    bulletRotate = std::acos(bulletRotate);
    bulletRotate = D3DXToDegree(bulletRotate);

    if (isOver180 == false) bulletRotate = 360.f - bulletRotate;

    this->rotation = bulletRotate;
    //std::cout << rotation << std::endl;

    graphic->InitTexture(texturePath);
    //collision->InitializeBase();

    //Move(axis * (speed * 4));
  
}
