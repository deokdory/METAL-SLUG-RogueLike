#include "stdafx.h"
#include "GameWorld.h"

GameWorld::GameWorld() { level = new TestLevel(); }

GameWorld::~GameWorld() { SAFE_DELETE(level); }

void GameWorld::update() { level->update(); }

void GameWorld::render(double interpolation) { level->render(); }
