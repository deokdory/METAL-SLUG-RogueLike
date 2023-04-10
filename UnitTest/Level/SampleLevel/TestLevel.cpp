#include "stdafx.h"
#include "TestLevel.h"
#include "Character/PlaybleCharacter.h"

TestLevel::TestLevel() {
  objects.push_back(new PlaybleCharacter(Values::CenterOfScreen, Vector3(300, 300, 0.f)));
}

void TestLevel::init() {}

void TestLevel::update() {}

void TestLevel::render() {}
