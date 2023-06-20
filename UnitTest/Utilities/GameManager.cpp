#include "stdafx.h"
#include "GameManager.h"

#include "Character/Agent.h"

void GameManager::Update()
{
  playerCurrentRoom = player->GetCurrentRoom();
}

void GameManager::GUI()
{
  std::string roomTypeStr = "Current room type : ";

  if (playerCurrentRoom != nullptr)
  {
    auto roomType = playerCurrentRoom->GetRoomType();
    switch (roomType)
    {
    case Room::Type::EMPTY:
      roomTypeStr += "empty";
      break;
    case Room::Type::UPGRADE:
      roomTypeStr += "upgrade";
      break;
    case Room::Type::BATTLE:
      roomTypeStr += "battle";
      break;
    case Room::Type::ROOT:
      roomTypeStr += "root";
      break;
    case Room::Type::BOSS:
      roomTypeStr += "boss";
      break;
    case Room::Type::ELIMINATE:
      roomTypeStr += "eliminate";
      break;
    case Room::Type::ELEVATE:
      roomTypeStr += "elevate";
      break;
    case Room::Type::PASSAGE:
      roomTypeStr += "passage";
      break;
    default:
      break;
    }
  }
  else roomTypeStr += "NULL";

  ImGui::Begin("GameManager");
  {
    ImGui::Text(roomTypeStr.c_str());
  }
  ImGui::End();
}

void GameManager::SetCurrentLevel(Level* level) { currentLevel = level; }

Level* GameManager::GetCurrentLevel() { return currentLevel; }

Room* GameManager::GetPlayerCurrentRoom() { return playerCurrentRoom; }

float GameManager::GetGlobalGravity() { return globalGravity; }

void GameManager::SetPlayer(class Agent* player) { this->player = player; }

Agent* GameManager::GetPlayer()
{
  return player;
}
