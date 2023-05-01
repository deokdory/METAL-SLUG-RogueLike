#include "stdafx.h"
#include "SoldierSample.h"

#include "Character/Animations.h"

SoldierSample::SoldierSample(Vector3 position, Vector3 size)
  : Enemy(position, size)
{
  graphic->InitAnimation(Animations::GetSoldierSample());
}

SoldierSample::~SoldierSample()
{
}
