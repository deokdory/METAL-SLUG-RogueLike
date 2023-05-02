#include "stdafx.h"
#include "Gun.h"

#include <Windows.h>
//#include "Level/Level.h"

Gun::Gun(GameObject* owner, float rpm, float vertRecoil, float horiRecoil, float bulletSpeed, float bulletDamage,
         UINT magazine, UINT magazineMax, UINT ammo, UINT ammoMax)
  : rpm(rpm), vertRecoil(vertRecoil), horiRecoil(horiRecoil), bulletSpeed(bulletSpeed), magazine(magazine), magazineMax(magazineMax), ammo(ammo), ammoMax(ammoMax)
{
  bullets.clear();
  bullets.assign(30, nullptr);
  //bullet = new Bullet(owner, Bullet::Side::PLAYER, bulletSpeed, bulletDamage, TexturePath + L"bullet_hmg.png");
}

Gun::~Gun()
{
  SAFE_DELETE(bullet);
}

void Gun::Update(Vector3 position, Vector3 axis)
{
  

  double currTime = Time::Get()->Running();
  float originAngle = D3DXVec3Dot(&Values::UpVec, &axis);
  float rotateChecker = D3DXVec3Dot(&Values::RightVec, &axis);

  bool isLeft = false;
  if (rotateChecker < 0) isLeft = true;
  //std::cout << "isLeft? " << isLeft << std::endl;

  originAngle = std::acos(originAngle);
  originAngle = D3DXToDegree(originAngle);
  //std::cout << originAngle << std::endl;
  
  float resultAngle = originAngle;
  if (isLeft) resultAngle = 360 - resultAngle;

  resultAngle -= spray / 2;
  resultAngle += ((double)rand() / RAND_MAX) * spray;

  if (resultAngle > 360) resultAngle -= 360;

  resultAngle = D3DXToRadian(resultAngle);
  //std::cout << resultAngle << std::endl;

  axis = {std::sin(resultAngle), std::cos(resultAngle), 0 };
  //std::cout << axis.x << ", " << axis.y << std::endl;

  if (isReloading)
    if (reloadProgress < reloadSpeed)
    {
      //std::cout << Time::Get()->WorldDelta() << std::endl;
      reloadProgress += (Time::Get()->WorldDelta());
    }
    else 
    {
      Reload(); 
    }

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
          if (rpmProgress >= rpm)
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
          if (rpmProgress>= rpm)
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
        if (rpmProgress >= rpm)
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
    if (rpmProgress >= rpm)
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
  if (rpmProgress < rpm) rpmProgress += Time::Get()->WorldDelta();

  isTriggeredPrev = isTriggered;
}

void Gun::Render()
{
}

void Gun::GUI()
{
  ImGui::Begin("Combat");
  {
    std::string magazineStr = "Magazine : " + std::to_string(magazine) + " / " + std::to_string(magazineMax);
    std::string modeStr = "Mode : ";
    std::string reloadStr = "Reload : " + std::to_string(1.0f - reloadProgress);


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

    ImVec4 color = ImVec4(0.76f, 0.77f, 0.8f, 1.0f);
    if (magazine == 0) color = ImVec4(1, 0, 0, 1);

    ImGui::TextColored(color, magazineStr.c_str());
    ImGui::Text(modeStr.c_str());

    if (isReloading) color = ImVec4(1, 1, 0, 1);
    else color = ImVec4(0.76f, 0.77f, 0.8f, 1.0f);
    ImGui::TextColored(color, reloadStr.c_str());

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
  level->PushObject(bullet->NewBullet(position + (axis * 90), axis));

  rpmProgress = 0.0;
}

void Gun::ReloadBegin()
{
  isTriggered = false;
  isReloading = true;
}

void Gun::Reload()
{
  isReloading = false;
  reloadProgress = 0.0f;
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
  auto gun = new Gun(owner, 1.f / 12.f, 2, 1, 16, 5, 30, 30, 180, 180);

  auto bullet = new Bullet(owner, Bullet::Side::PLAYER, 16, 5, TexturePath + L"bullet_hmg.png");
  gun->SetBullet(bullet);

  return gun;
}

void Gun::Recoil()
{
  
}
