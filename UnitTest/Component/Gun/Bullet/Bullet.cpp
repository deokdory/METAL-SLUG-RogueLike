#include "stdafx.h"
#include "Bullet.h"

#include "Component/Graphic/TexturedGraphic.h"
#include "Component/Collision/Collision.h"

Bullet::Bullet(GameObject* fired, Side side, Vector3 axis, float speed, float damage)
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
