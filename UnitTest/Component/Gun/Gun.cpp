#include "stdafx.h"
#include "Gun.h"

#include "Level/Level.h"

Gun::Gun(GameObject* owner, float rpm, float vertRecoil, float horiRecoil, float bulletSpeed, float bulletDamage,
         float magazine, float magazineMax, float ammo, float ammoMax)
  : rpm(rpm), vertRecoil(vertRecoil), horiRecoil(horiRecoil), bulletSpeed(bulletSpeed), 
    magazine(magazine), magazineMax(magazineMax), ammo(ammo), ammoMax(ammoMax)
{
  new Bullet(owner, Bullet::Side::PLAYER, bulletSpeed, )
}

Gun::~Gun()
{
  SAFE_DELETE(bullet);
}

void Gun::Update(Vector3 position, Vector3 axis)
{
  auto currTime = Time::Get()->Running();

  if (isBursting == false)
  {
    if (isTriggered)
    {
      switch (mode)
      {
      case Gun::FireMode::SEMI_AUTO:
      case Gun::FireMode::BURST:
      {

        if (isTriggeredPrev == false)
        {
          if (currTime - lastFire >= rpm)
          {
            Fire(position, axis);
          }
          break;
        }
      }
      case Gun::FireMode::AUTO:
      {
        if (currTime - lastFire >= rpm)
        {
          Fire(position, axis);
        }
        break;
      }
      default:
        break;
      }
      isTriggeredPrev = true;
    }


  }
}

void Gun::Render()
{
}

void Gun::PullTrigger()
{
  isTriggered = true;
}

void Gun::ReleaseTrigger()
{
  isTriggered = false;
}

void Gun::Fire(Vector3 position, Vector3 axis)
{
  auto level = GameManager::Get()->GetCurrentLevel();
  level->PushObject()
}

void Gun::Reload()
{
}

void Gun::SupplyAmmo(UINT ammo)
{
}

void Gun::SwitchMode()
{
  switch (mode)
  {
  case Gun::FireMode::SEMI_AUTO:
    mode = Gun::FireMode::BURST;
    return;
  case Gun::FireMode::BURST:
    mode = Gun::FireMode::AUTO;
    return;
  case Gun::FireMode::AUTO:
    mode = Gun::FireMode::SEMI_AUTO;
    return;
  default:
    return;
  }
}

void Gun::Recoil()
{
}
