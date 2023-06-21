#include "stdafx.h"
#include "TestLevel.h"

#include "Character/Agent.h"
#include "Character/SoldierSample.h"

#include "Character/Animations.h"
#include "UI/HUD.h"

#include "GameObjects/Elevator.h"

TestLevel::TestLevel() 
: Level() { init(); }

void TestLevel::init() {

  auto player = new Agent(Vector3(0, 100, 0), Vector3(44, 80, 0.f));
  player->InitGraphic(Animations::GetEriLower(), ObjectGraphic::Slot::LOWER);
  player->InitGraphic(Animations::GetEriUpper(), ObjectGraphic::Slot::UPPER);

  this->player = player;
  GameManager::Get()->SetPlayer(player);

  TextureRect* background = new TextureRect(Vector3(640, 360, 0), Vector3(2106, 1024, 0), 0, TexturePath + L"MS5_2-2_BACKGROUND_PATTERN.png");

  background->Update();
  backgrounds.push_back(background);

  // InitTestEnemies();

  // 颇老 阂矾客辑 积己
  {
    rooms.push_back(new Room(Room::Type::ELEVATE));
    rooms.push_back(new Room(Room::Type::PASSAGE, MapDataPath + L"passage_1to1.csv", rooms[0], Direction::RIGHT));
    rooms.push_back(new Room(Room::Type::BATTLE, MapDataPath + L"room_1.csv", rooms[1], Direction::RIGHT));
    rooms.push_back(new Room(Room::Type::PASSAGE, MapDataPath + L"passage_0to1.csv", rooms[0], Direction::LEFT));
    rooms.push_back(new Room(Room::Type::ELIMINATE, MapDataPath + L"room_2.csv", rooms.back(), Direction::LEFT));

    objForeground.push_back(new Elevator(Vector3(0, -64, 0)));
  }

  __super::init();

  GameManager::Get()->SetCurrentLevel(this);
  GameManager::Get()->Update();
}

void TestLevel::Update() 
{ 
  __super::Update(); 
  if (Keyboard::Get()->Down(VK_F9)) InitTestEnemies(player->GetPosition() + Vector3(0, 100, 0));
}

void TestLevel::Render() 
{
  __super::Render(); 
}

void TestLevel::InitTestEnemies(Vector3 position)
{
  auto enemy1 = new SoldierSample(position + Vector3(-300, 0, 0), Vector3(44, 80, 0.f));
  auto enemy2 = new SoldierSample(position + Vector3(-150, 0, 0), Vector3(44, 80, 0.f));
  auto enemy3 = new SoldierSample(position + Vector3(0, 0, 0), Vector3(44, 80, 0.f));
  auto enemy4 = new SoldierSample(position + Vector3(150, 0, 0), Vector3(44, 80, 0.f));
  auto enemy5 = new SoldierSample(position + Vector3(300, 0, 0), Vector3(44, 80, 0.f));

  objects.push_back(enemy1);
  objects.push_back(enemy2);
  objects.push_back(enemy3);
  objects.push_back(enemy4);
  objects.push_back(enemy5);
}