#include "stdafx.h"
#include "TestLevel.h"
#include "Character/PlaybleCharacter.h"

#include "Character/Animations.h"
#include "UI/HUD.h"

TestLevel::TestLevel() { init(); }

void TestLevel::init() {
  auto player =
      new Agent(Values::CenterOfScreen, Vector3(100, 100, 0.f));

  player->InitGraphic(AGENT_GRAPHIC);
  player->setGraphicResource(Animations::getEriLowerTest(), LOWER);
  player->setGraphicResource(Animations::getEriUpperTest(), UPPER);

  player->GetMovement()->SetLevel(this);

  objects.push_back(player);

  terrains.push_back(new Terrain(Vector3(640, 100, 0), Vector3(640, 64, 0),
                                 TexturePath + L"SamplePlate.png"));
  terrains.push_back(new Terrain(Vector3(900, 150, 0), Vector3(100, 100, 0),
                                 TexturePath + L"SamplePlate.png"));
  terrains.push_back(new Terrain(Vector3(300, 400, 0), Vector3(100, 100, 0),
                                 TexturePath + L"SamplePlate.png"));

  playerHud = new HUD();
  __super::init();
}

void TestLevel::update() { 
  playerHud->Update();
  __super::update(); }

void TestLevel::render() {
  playerHud->Render();
  __super::render(); }
