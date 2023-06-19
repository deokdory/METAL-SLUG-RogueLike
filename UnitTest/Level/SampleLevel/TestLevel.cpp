#include "stdafx.h"
#include "TestLevel.h"

#include "Character/Agent.h"
#include "Character/SoldierSample.h"

#include "Character/Animations.h"
#include "UI/HUD.h"

TestLevel::TestLevel() 
: Level() { init(); }

void TestLevel::init() {

  auto player = new Agent(Values::CenterOfScreen, Vector3(44, 80, 0.f));
  player->InitGraphic(Animations::GetEriLower(), ObjectGraphic::Slot::LOWER);
  player->InitGraphic(Animations::GetEriUpper(), ObjectGraphic::Slot::UPPER);

  objects.push_back(player);

  TextureRect* background = new TextureRect(Vector3(640, 360, 0), Vector3(2106, 1024, 0), 0, TexturePath + L"MS5_2-2_BACKGROUND_PATTERN.png");
  background->Update();
  backgrounds.push_back(background);

  // InitTestEnemies();

  // 流立 瘤屈 积己 (具啊促)
  {
    //Vector3 startPosition = { 640 - TILESIZE * 8, 100, 0 };
    //Vector3 currPosition = startPosition;
    //terrains.push_back(new Terrain(currPosition, Terrain::Type::FH_EDGE_L));
    //for (UINT i = 1; i < 15; i++)
    //{
    //  currPosition.x = startPosition.x + TILESIZE * i;
    //  terrains.push_back(new Terrain(currPosition, Terrain::Type::FH_MID));
    //}
    //currPosition.x = startPosition.x + TILESIZE * 15;
    //terrains.push_back(new Terrain(currPosition, Terrain::Type::FH_EDGE_R));
    //
    //startPosition = { 640 - TILESIZE * 8, 100 + TILESIZE * 3, 0 };
    //currPosition = startPosition;
    //terrains.push_back(new Terrain(currPosition, Terrain::Type::FH_EDGE_L));
    //for (UINT i = 1; i < 15; i++)
    //{
    //  currPosition.x = startPosition.x + TILESIZE * i;
    //  terrains.push_back(new Terrain(currPosition, Terrain::Type::FH_MID));
    //}
    //currPosition.x = startPosition.x + TILESIZE * 15;
    //terrains.push_back(new Terrain(currPosition, Terrain::Type::FH_EDGE_R));
    //
    //startPosition = { 640 - TILESIZE * 8, 100 + TILESIZE * 6, 0 };
    //currPosition = startPosition;
    //terrains.push_back(new Terrain(currPosition, Terrain::Type::FH_EDGE_L));
    //for (UINT i = 1; i < 15; i++)
    //{
    //  currPosition.x = startPosition.x + TILESIZE * i;
    //  terrains.push_back(new Terrain(currPosition, Terrain::Type::FH_MID));
    //}
    //currPosition.x = startPosition.x + TILESIZE * 15;
    //terrains.push_back(new Terrain(currPosition, Terrain::Type::FH_EDGE_R));
    //
    //terrains.push_back(new Terrain({ 800, 100 + TILESIZE + TILESIZE/2, 0 }, Terrain::Type::STAIR_UP));
    //terrains.push_back(new Terrain({ 480, 100 + TILESIZE * 3 + TILESIZE * 1.5, 0 }, Terrain::Type::STAIR_DOWN));
  }

  // 颇老 阂矾客辑 积己
  {
    rooms.push_back(new Room(Room::Type::START));
  }

  __super::init();

  GameManager::Get()->SetCurrentLevel(this);
}

void TestLevel::Update() 
{ 
  __super::Update(); 
  if (Keyboard::Get()->Down(VK_F9)) InitTestEnemies();
}

void TestLevel::Render() 
{
  __super::Render(); 
}

void TestLevel::InitTestEnemies()
{
  auto enemy1 = new SoldierSample(Values::CenterOfScreen + Vector3(-300, 0, 0), Vector3(44, 80, 0.f));
  auto enemy2 = new SoldierSample(Values::CenterOfScreen + Vector3(-150, 0, 0), Vector3(44, 80, 0.f));
  auto enemy3 = new SoldierSample(Values::CenterOfScreen + Vector3(0, 0, 0), Vector3(44, 80, 0.f));
  auto enemy4 = new SoldierSample(Values::CenterOfScreen + Vector3(150, 0, 0), Vector3(44, 80, 0.f));
  auto enemy5 = new SoldierSample(Values::CenterOfScreen + Vector3(300, 0, 0), Vector3(44, 80, 0.f));

  objects.push_back(enemy1);
  objects.push_back(enemy2);
  objects.push_back(enemy3);
  objects.push_back(enemy4);
  objects.push_back(enemy5);
}