#include "stdafx.h"
#include "Gun.h"

#include <Windows.h>
#include "Level/Level.h"

Gun::Gun(GameObject* owner, float rpm, float vertRecoil, float horiRecoil, float bulletSpeed, float bulletDamage,
         UINT magazine, UINT magazineMax, UINT ammo, UINT ammoMax)
  : rpm(rpm), vertRecoil(vertRecoil), horiRecoil(horiRecoil), bulletSpeed(bulletSpeed), magazine(magazine), magazineMax(magazineMax), ammo(ammo), ammoMax(ammoMax)
{
  new Bullet(owner, Bullet::Side::PLAYER, bulletSpeed, bulletDamage, TexturePath + L"basicBullet.png");
}

Gun::~Gun()
{
  SAFE_DELETE(bullet);
}

void Gun::Update(Vector3 position, Vector3 axis)
{
  auto currTime = Time::Get()->Running();

  if (burstCount == 0)
  {
    if (isTriggered)
    {
      switch (mode)
      {
      case Gun::FireMode::SEMI_AUTO:
      {
        if (isTriggeredPrev == false)
        {
          if (currTime - lastFire >= rpm)
          {
            if(magazineIsEmpty() == false)
              Fire(position, axis);
          }
        }
        break;
      }
      case Gun::FireMode::BURST:
      {
        if (isTriggeredPrev == false)
        {
          if (currTime - lastFire >= rpm)
          {
            if (magazineIsEmpty() == false)
              Fire(position, axis);
              burstCount = 2;
          }
        }
          break;
      }
      case Gun::FireMode::AUTO:
      {
        if (currTime - lastFire >= rpm)
        {
          if (magazineIsEmpty() == false)
            Fire(position, axis);
        }
        break;
      }
      default:
        break;
      }
    }
  }
  else
  {
    if (currTime - lastFire >= rpm)
    {
      if (magazineIsEmpty() == false)
      {
        Fire(position, axis);
        burstCount--;
      }
      else
      {
        burstCount = 0;
      }
    }
  }
    isTriggeredPrev = isTriggered;
}

void Gun::Render()
{
}

void Gun::GUI()
{
  ImGui::Begin("gun");
  {
    std::string magazineStr = std::to_string(magazine) + " / " + std::to_string(magazineMax);
    std::string modeStr = "Mode : ";

    switch (mode)
    {
    case Gun::FireMode::SEMI_AUTO:
      modeStr += "SemiAuto";
      break;
    case Gun::FireMode::BURST:
      modeStr += "Burst";
      break;
    case Gun::FireMode::AUTO:
      modeStr += "Auto";
      break;
    default:
      break;
    }

    ImGui::Text(magazineStr.c_str());
    ImGui::Text(modeStr.c_str());
    ImGui::SliderFloat("rpm", &rpm, 1.f / 1.f, 1.f / 32.f);
  }
  ImGui::End();
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
  magazine--;
  auto level = GameManager::Get()->GetCurrentLevel();
  level->PushObject(bullet->NewBullet(position, axis));

  lastFire = Time::Get()->Running();

}

void Gun::Reload()
{
  
  magazine = magazineMax;
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

Gun* Gun::InitHMG(GameObject* owner)
{
  auto gun = new Gun(owner, 1.f / 8.f, 2, 1, 16, 5, 30, 30, 180, 180);
  auto bullet = new Bullet(owner, Bullet::Side::PLAYER, 16, 5, TexturePath + L"bulletBasic.png");
  gun->SetBullet(bullet);

  return gun;
}

void Gun::Recoil()
{
  
}
