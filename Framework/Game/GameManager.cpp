#include "Framework.h"
#include "GameManager.h"

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
