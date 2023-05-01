#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(GameObject* fired, Side side, float speed, float damage, std::wstring texturePath)
: GameObject(fired->GetPosition(), Vector3(62, 14, 0)), fired(fired), side(side), speed(speed), damage(damage), texturePath(texturePath)
{
  type = Type::BULLET;
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
    if (flyingTime >= 5.0)
      isWaitingDelete = true;

    flyingTime += Time::Get()->WorldDelta();

    Move(axis * speed);

    graphic->Update();
    collision->Update();
  }


}

void Bullet::Render()
{
  graphic->Render();
  collision->Render();
}


void Bullet::hit(GameObject* object)
{
  isHit = true;
}

Bullet* Bullet::NewBullet(Vector3 position, Vector3 axis)
{
  return new Bullet(fired, side, speed, damage, texturePath, position, axis);
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
    collision->InitializeBase();

    //Move(axis * (speed * 4));
  
}
