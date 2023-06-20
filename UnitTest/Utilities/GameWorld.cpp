#include "stdafx.h"
#include "GameWorld.h"

GameWorld::GameWorld() {
  level = new TestLevel();
}

GameWorld::~GameWorld() {
  SAFE_DELETE(level);
}

void GameWorld::Update() {
  Camera::Get()->Update();
  level->Update();
  GameManager::Get()->Update();
}

void GameWorld::Render() { level->Render(); }

void GameWorld::GUI()
{
  level->GUI();
  GameManager::Get()->GUI();
}
