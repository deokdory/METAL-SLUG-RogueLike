#include "stdafx.h"
#include "Game.h"

#include "Character/Player.h"
#include "Map/SampleStage/SamplePlate.h"

void Game::Init() {
  player = new Player(Values::CenterOfScreen, Vector3(100, 100, 1));
  plates.push_back(new SamplePlate(Vector3(640, 150, 0), Vector3(1920, 32, 1),
                                   0.0f));
  background = new TextureRect(Values::CenterOfScreen, Vector3(1280, 1500, 1),
                               0.0f, TexturePath + L"exterior-parallaxBG1.png");
}

void Game::Destroy() { SAFE_DELETE(player); }

void Game::Update() {
  background->Update();

  for (auto p : plates) {
    p->Update();
  }

  auto foot = player->GetFootCollision();
  //Collision
  {
    player->SetIsOnGround(false);
    for (auto p : plates) {
      auto plateCollision = p->GetCollision();
      if (BoundingBox::AABB(foot, plateCollision)) {
  
        player->SetIsOnGround();
        auto x = player->GetPosition().x;
        auto y =
            p->GetPosition().y + p->GetSize().y / 2 + player->GetSize().y / 2;
  
        if(player->GetYSpeed() < 0) player->SetPosition(Vector3(x, y, 0.f));
      }
    }
  }

  if (Keyboard::Get()->Down(VK_SPACE)) {
    player->Jump();
  }
  if (Keyboard::Get()->Down('A')) {
    player->Sword();
  }
  if (Keyboard::Get()->Press('S')) {
    player->Guard(true);
  } else {
    player->Guard(false);
  }

  if (Keyboard::Get()->Press(VK_RIGHT) && !Keyboard::Get()->Press(VK_LEFT)) {
    player->MoveRight();
  } else if (Keyboard::Get()->Press(VK_LEFT) &&
             !Keyboard::Get()->Press(VK_RIGHT)) {
    player->MoveLeft();
  } else {
    player->Idle();
  }
  player->Update();
}

void Game::Render() {
  background->Render();
  player->Render(); 
  for (auto p : plates) {
    p->Render();
  }
}

void Game::PostRender() {}

void Game::GUI() {}
