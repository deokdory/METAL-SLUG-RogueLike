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
  lag += elapsedTime;

  // 입력 처리 ( 스트림 )

  while (lag >= MS_PER_UPDATE) {
    prevTime = currTime;
    gameWorld->update();
    lag -= MS_PER_UPDATE;
  }
}

void Game::Render() { gameWorld->render(lag / MS_PER_UPDATE); }

void Game::PostRender() {}

void Game::GUI() {}
