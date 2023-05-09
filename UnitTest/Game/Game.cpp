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
    gameWorld->Update();
    frameCount++;
}

void Game::Render() {
    gameWorld->Render();
}

void Game::PostRender() {}

void Game::GUI() {

  gameWorld->GUI();

  ImGui::Begin("Game");
  {
    float runningTime = Time::Get()->Running();

    std::string runningStr = "running " + std::to_string(runningTime);
    ImGui::Text(runningStr.c_str());

    std::string fpsStr = "frameCount " + std::to_string(frameCount);
    ImGui::Text(fpsStr.c_str());

    std::string cameraPosStr = "mouse world position " + std::to_string(Mouse::Get()->GetPosition().x + Camera::Get()->GetPosition().x) + " x " + std::to_string(Mouse::Get()->GetPosition().y + Camera::Get()->GetPosition().y);
    ImGui::Text(cameraPosStr.c_str());

    double globalSpeed = Time::Get()->GetGlobalSpeed();
    std::string globalSpeedStr = "global speed " + std::to_string(globalSpeed);
    ImVec4 color = ImVec4(0.76f, 0.77f, 0.8f, 1.0f);
    if(globalSpeed != 1.0) color = ImVec4(1, 1, 0, 1);
    ImGui::TextColored(color, globalSpeedStr.c_str());
  }
  ImGui::End();
}
