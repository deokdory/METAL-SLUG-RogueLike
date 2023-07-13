#include "stdafx.h"
#include "SoldierSample.h"

#include "Character/Animations.h"

SoldierSample::SoldierSample(Vector3 position, Vector3 size)
  : Enemy(position, size)
{
  graphic->InitAnimation(Animations::GetSoldierKnife());
}

SoldierSample::SoldierSample(Vector3 position, Vector3 size, Room* spawnedRoom)
  : Enemy(position, size, spawnedRoom)
{
  graphic->InitAnimation(Animations::GetSoldierKnife());
}

SoldierSample::~SoldierSample()
{
}
