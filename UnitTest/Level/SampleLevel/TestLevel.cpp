#include "stdafx.h"
#include "TestLevel.h"
#include "Character/PlaybleCharacter.h"

TestLevel::TestLevel() { init(); }

void TestLevel::init() {
  objects.push_back(
      new PlaybleCharacter(Values::CenterOfScreen, Vector3(300, 300, 0.f)));

}

void TestLevel::update() { __super::update(); }

void TestLevel::render() { __super::render(); }
