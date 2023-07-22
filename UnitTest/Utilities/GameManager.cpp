#include "stdafx.h"
#include "GameManager.h"

#include "Character/Agent.h"
#include "Objects/Terrain.h"

void GameManager::Update()
{
  playerCurrentRoom = player->GetCurrentRoom();
  lastStandedTerrain = player->GetMovement()->GetLastStanded();

  if (lastStandedTerrain != nullptr)
    lastStandedTerrainFloor = lastStandedTerrain->GetFloor();

  if (Keyboard::Get()->Press(VK_F11)) player->SetPositionForce({ 0, 100, 0 });
}

void GameManager::GUI()
{
  // 현재 방 상태 프린트용
    std::string roomTypeStr = "Current room type : ";
    std::string isActivedStr = "This room is ";
    std::string roomFloorStr = "Current Room's Floor : ";
    std::string terrainFloorStr = "Last Standed Terrain's Floor : ";
    
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
      roomFloorStr += std::to_string(playerCurrentRoom->GetFloor());
    }
    else
    {
      roomTypeStr += "NULL";
    }

    if (lastStandedTerrain != nullptr)
      terrainFloorStr += std::to_string(lastStandedTerrain->GetFloor());
    else
      terrainFloorStr += "NULL";
    
  ImGui::Begin("Room");
  {
    ImGui::Text(roomTypeStr.c_str());
    ImGui::Text(isActivedStr.c_str());
    ImGui::Text(roomFloorStr.c_str());
    ImGui::Text(terrainFloorStr.c_str());
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
