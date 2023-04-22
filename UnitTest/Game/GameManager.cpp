#include "stdafx.h"
#include "GameManager.h"

#include "Level/Level.h"

void GameManager::SetCurrentLevel(Level* level)
{
  currentLevel = level;
}

Level* GameManager::GetCurrentLevel()
{
  return currentLevel;
}

void GameManager::SetGlobalSpeed(float speed)
{
  globalSpeed = speed;
}

float GameManager::GetGlobalSpeed()
{
  return globalSpeed;
}
