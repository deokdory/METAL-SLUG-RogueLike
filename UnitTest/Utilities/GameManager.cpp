#include "stdafx.h"
#include "GameManager.h"

#include "Character/Agent.h"

void GameManager::Update()
{
  playerCurrentRoom = player->GetCurrentRoom();

  if (Keyboard::Get()->Press(VK_F11)) player->SetPositionForce({ 0, 100, 0 });
}

void GameManager::GUI()
{
  // 현재 방 상태 프린트용
    std::string roomTypeStr = "Current room type : ";
    std::string isActivedStr = "This room is ";
    std::string floorStr = "Current Floor : ";

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
      // 현재 방 활성화 상태
      if (playerCurrentRoom->GetIsActived()) isActivedStr += "actived";
      else isActivedStr += "not actived";

      // 현재 층수
      floorStr += std::to_string(playerCurrentRoom->GetFloor());
    }
    else
    {
      roomTypeStr += "NULL";
    }
    
  ImGui::Begin("Room");
  {
    ImGui::Text(roomTypeStr.c_str());
    ImGui::Text(isActivedStr.c_str());
    ImGui::Text(floorStr.c_str());
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
