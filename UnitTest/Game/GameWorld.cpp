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
}

void GameWorld::Render() { level->Render(); }
