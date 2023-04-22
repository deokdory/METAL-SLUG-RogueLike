#include "stdafx.h"
#include "Bullet.h"

#include "Component/Graphic/TexturedGraphic.h"
#include "Component/Collision/Collision.h"

Bullet::Bullet(GameObject* fired, Side side, float speed, float damage)
  :
{
  auto rotateChecker = D3DXVec3Dot(&axis, &Values::UpVec);
  auto bulletRotate = D3DXVec3Dot(&axis, &Values::RightVec);

  bool isOver180 = true;
  if (rotateChecker < 0) isOver180 = false;

  bulletRotate = std::acos(bulletRotate);
  bulletRotate = D3DXToDegree(bulletRotate);

  if (isOver180 == false) bulletRotate = 360.f - bulletRotate;
  
  this->rotation = bulletRotate;
  std::cout << rotation << std::endl;

  graphic = new TexturedGraphic(this);
  graphic->SetResource(TexturePath + L"bulletBasic.png");
  collision->InitializeBase();

  Move(axis * (speed * 4));
}
Bullet::Bullet(Vector3 position, Vector3 axis)
  : GameObject(fired->GetPosition(), Vector3(60, 6, 0)),
  fired(fired), side(side), axis(axis), speed(speed), damage(damage)
{
  auto rotateChecker = D3DXVec3Dot(&axis, &Values::UpVec);
  auto bulletRotate = D3DXVec3Dot(&axis, &Values::RightVec);

  bool isOver180 = true;
  if (rotateChecker < 0) isOver180 = false;

  bulletRotate = std::acos(bulletRotate);
  bulletRotate = D3DXToDegree(bulletRotate);

  if (isOver180 == false) bulletRotate = 360.f - bulletRotate;

  this->rotation = bulletRotate;
  std::cout << rotation << std::endl;

  graphic = new TexturedGraphic(this);
  graphic->SetResource(TexturePath + L"bulletBasic.png");
  collision->InitializeBase();

  Move(axis * (speed * 4));
}
Bullet::Bullet(GameObject* fired, Side side, float speed, float damage, std::wstring texturePath)
: GameObject(fired->GetPosition(),
fired(fired), side(side), axis(axis), speed(speed), damage(damage)
{
  Texture2D* srcTex = new Texture2D(texturePath);

}
Bullet::~Bullet()
{
}

void Bullet::Update()
{
  Move(axis * speed);

  graphic->Update();
  collision->Update();
}

void Bullet::Render()
{
  graphic->Render();
  collision->Render();
}


void Bullet::hit(GameObject* object)
{
  bHit = true;
}

Bullet* Bullet::NewBullet(Vector3 position, Vector3 axis)
{
  return new Bullet(position, axis);
}
