#include "stdafx.h"
#include "Game.h"


void Game::Init() { 
  GameManager::Create();
  gameWorld = new GameWorld();
  prevTime = Time::Get()->Running();
  Time::Get()->InitNewTimer("game");
}

void Game::Destroy() {
  SAFE_DELETE(gameWorld);
  GameManager::Delete();
}

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
  prevTime = Time::Get()->Running();
}

void Game::PostRender() {}

void Game::GUI() {
  gameWorld->GUI();

  ImGui::Begin("Game");
  {
    auto fps = "fps " + std::to_string(Time::Get()->FPS());
    auto running = "running " + std::to_string(Time::Get()->Running());

    ImGui::Text(fps.c_str());
    ImGui::Text(running.c_str());
  }
  ImGui::End();
}
