#include "stdafx.h"
#include "GameManager.h"

#include "Character/Agent.h"
#include "Objects/Terrain.h"

void GameManager::Update()
{
  playerCurrentRoom = player->GetCurrentRoom();
  lastStandedTerrain = player->GetMovement()->GetLastStanded();

  if (playerCurrentRoom)
  {
    Vector3 playerCurrentRoomPosition = playerCurrentRoom->GetPosition();
    Vector3 playerPosition = player->GetPosition();

    if (playerPosition.y >= playerCurrentRoomPosition.y + 160.f)
      playerCurrentFloor = 2;
    else if (playerPosition.y >= playerCurrentRoomPosition.y - 32.f)
      playerCurrentFloor = 1;
    else
      playerCurrentFloor = 0;
  }

  if (Keyboard::Get()->Press(VK_F11)) player->SetPositionForce({ 0, 100, 0 });
}

void GameManager::GUI()
{
  // ���� �� ���� ����Ʈ��
    std::string roomTypeStr = "Current room type : ";
    std::string isActivedStr = "This room is ";
    std::string roomFloorStr = "Current Room's Floor : ";
    std::string playerCurrentFloorStr = "Last Standed Terrain's Floor : ";
    
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
      // ���� �� Ȱ��ȭ ����
      if (playerCurrentRoom->GetIsActived()) isActivedStr += "actived";
      else isActivedStr += "not actived";

      // ���� ����
      roomFloorStr += std::to_string(playerCurrentRoom->GetFloor());
    }
    else
    {
      roomTypeStr += "NULL";
    }

    playerCurrentFloorStr += std::to_string(playerCurrentFloor);
    
  ImGui::Begin("Room");
  {
    ImGui::Text(roomTypeStr.c_str());
    ImGui::Text(isActivedStr.c_str());
    ImGui::Text(roomFloorStr.c_str());
    ImGui::Text(playerCurrentFloorStr.c_str());
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
