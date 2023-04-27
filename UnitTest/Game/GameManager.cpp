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

float GameManager::GetGlobalGravity()
{
  return globalGravity;
}
