#include "stdafx.h"
#include "Game.h"


void Game::Init() { 
  gameWorld = new GameWorld();
  prevTime = Time::Get()->Running();
  Time::Get()->InitNewTimer("game");
}

void Game::Destroy() { SAFE_DELETE(gameWorld); }

void Game::Update() {
  double currTime = Time::Get()->Running();
  double elapsedTime = currTime - prevTime;
  elapsedTotal += elapsedTime;

  if (elapsedTotal > MS_PER_UPDATE) {
  gameWorld->Update();
    Time::Get()->UpdateTimer("game");
  }
}

void Game::Render() {
  if (elapsedTotal > MS_PER_UPDATE) {
  gameWorld->Render();
    elapsedTotal -= MS_PER_UPDATE;
  }
}

void Game::PostRender() {}

void Game::GUI() {}
