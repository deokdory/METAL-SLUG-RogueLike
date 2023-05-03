#include "stdafx.h"
#include "HUD.h"

#include "Game/UI/ProgressBar.h"

HUD::HUD() {

  float width = -WinMaxWidth / 2 + 540;
  float height = -WinMaxHeight / 2 + 50;

  HPBar = new ProgressBar({width, height, 0}, {200, 20, 0}, 0.0f, Values::Red,
                          UI::LEFT_TO_RIGHT);
}

HUD::~HUD() { SAFE_DELETE(HPBar); }

void HUD::Update() {

  HPBar->UpdateProgressBar(percent);
  HPBar->Update();
}

void HUD::Render() { HPBar->Render(); }
