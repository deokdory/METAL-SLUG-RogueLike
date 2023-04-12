#include "stdafx.h"
#include "TestLevel.h"
#include "Character/PlaybleCharacter.h"

TestLevel::TestLevel() { init(); }

void TestLevel::init() {
  auto player =
      new PlaybleCharacter(Values::CenterOfScreen, Vector3(100, 100, 0.f));
  player->GetMovement()->SetLevel(this);

  objects.push_back(player);

  terrains.push_back(new Terrain(Vector3(640, 100, 0), Vector3(640, 64, 0),
                                 TexturePath + L"SamplePlate.png"));
  terrains.push_back(new Terrain(Vector3(900, 150, 0), Vector3(100, 100, 0),
                                 TexturePath + L"SamplePlate.png"));
  terrains.push_back(new Terrain(Vector3(300, 400, 0), Vector3(100, 100, 0),
                                 TexturePath + L"SamplePlate.png"));

}

void TestLevel::update() { __super::update(); }

void TestLevel::render() { __super::render(); }
