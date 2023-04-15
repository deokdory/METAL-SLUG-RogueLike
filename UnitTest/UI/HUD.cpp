#include "stdafx.h"
#include "HUD.h"

#include "Game/UI/ProgressBar.h"

HUD::HUD() {
  float width = -WinMaxWidth / 2 + 30;
  float height = WinMaxHeight / 2 - 30;
  HPBar = new ProgressBar({width, height, 0}, {200, 30, 1}, 0.0f, Values::Red,
                          UI::LEFT_TO_RIGHT);
}

HUD::~HUD() { SAFE_DELETE(HPBar); }

void HUD::Update() {
  if (Keyboard::Get()->Down(VK_F3)) percent -= 0.1f;
  HPBar->UpdateProgressBar(percent);

  HPBar->Update();
}

void HUD::Render() { HPBar->Render(); }
