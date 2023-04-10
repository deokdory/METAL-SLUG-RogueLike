#include "stdafx.h"
#include "Game.h"


void Game::Init() { 
  gameWorld = new GameWorld();
  prevTime = Time::Get()->Running();
}

void Game::Destroy() { SAFE_DELETE(gameWorld); }

void Game::Update() {
  double currTime = Time::Get()->Running();
  double elapsedTime = currTime - prevTime;
  elapsedTotal += elapsedTime;
    gameWorld->update();

  if (elapsedTotal > MS_PER_UPDATE) {
    elapsedTotal -= MS_PER_UPDATE;
  }
}

void Game::Render() {
    gameWorld->render();
}

void Game::PostRender() {}

void Game::GUI() {}
