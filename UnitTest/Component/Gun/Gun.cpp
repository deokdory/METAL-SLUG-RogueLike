#include "stdafx.h"
#include "Gun.h"

Gun::Gun(float rpm, float vertRecoil, float horiRecoil, float bulletSpeed, float magazineCurrent, float magazineMax, float ammo, float ammoMax)
  : rpm(rpm), vertRecoil(vertRecoil), horiRecoil(horiRecoil), bulletSpeed(bulletSpeed), magazineCurrent(magazineCurrent), magazineMax(magazineMax), ammo(ammo), ammoMax(ammoMax)
{
}

Gun::~Gun()
{
}

void Gun::Fire(Vector3 position, Vector3 axis)
{
}

void Gun::Reload()
{
}

void Gun::SupplyAmmo(UINT ammo)
{
}

void Gun::Recoil()
{
}
