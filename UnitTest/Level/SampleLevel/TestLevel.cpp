#include "stdafx.h"
#include "TestLevel.h"

#include "Character/Agent.h"
#include "Character/SoldierSample.h"

#include "Character/Animations.h"
#include "UI/HUD.h"

TestLevel::TestLevel() 
: Level() { init(); }

void TestLevel::init() {

  //auto background = new GameObject(Values::CenterOfScreen + Vector3(0, -100, 0), Vector3(4352, 944, 0));
  //background->SetAnchorPoint(AnchorPoint::CENTER);
  //background->InitGraphic(TexturePath + L"background_sample.png", ObjectGraphic::Slot::NORMAL);
  //
  //objects.push_back(background);

  auto player = new Agent(Values::CenterOfScreen, Vector3(44, 80, 0.f));
  player->InitGraphic(Animations::GetEriLower(), ObjectGraphic::Slot::LOWER);
  player->InitGraphic(Animations::GetEriUpper(), ObjectGraphic::Slot::UPPER);

  objects.push_back(player);

  InitTestEnemies();

  //auto player2 = new Agent(Values::CenterOfScreen, Vector3(44, 80, 0.f));
  //
  //player2->InitGraphic(Animations::GetEriLower(), ObjectGraphic::Slot::LOWER);
  //player2->InitGraphic(Animations::GetEriUpper(), ObjectGraphic::Slot::UPPER);
  //
  //objects.push_back(player2);
  //player2->SetIsWaitingDelete(true);

  Vector3 startPosition = { 640 - TILESIZE * 8, 100, 0 };
  Vector3 currPosition = startPosition;
  terrains.push_back(new Terrain(currPosition, Terrain::Type::FH_EDGE_L));
  for (UINT i = 1; i < 15; i++)
  {
    currPosition.x = startPosition.x + TILESIZE * i;
    terrains.push_back(new Terrain(currPosition, Terrain::Type::FH_MID));
  }
  currPosition.x = startPosition.x + TILESIZE * 15;
  terrains.push_back(new Terrain(currPosition, Terrain::Type::FH_EDGE_R));
  terrains.push_back(new Terrain({ 640, 200, 0 }, Terrain::Type::STAIR_UP));

  //terrains.push_back(new Terrain(Vector3(640, 100, 0), Vector3(1920, 32, 0), TexturePath + L"SamplePlate.png"));
  //terrains.push_back(new Terrain(Vector3(1280, 350, 0), Vector3(32, 300, 0), TexturePath + L"SamplePlate.png"));
  //terrains.push_back(new Terrain(Vector3(640, 420, 0), Vector3(640, 32, 0), TexturePath + L"SamplePlate.png"));

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