#pragma once
#include "Enemy.h"

class SoldierSample : public Enemy
{
public:
  SoldierSample(Vector3 position, Vector3 size);
  SoldierSample(Vector3 position, Vector3 size, Room* spawnedRoom);
  virtual ~SoldierSample();

protected:
};