#include "stdafx.h"
#include "Level.h"

Level::~Level() {
  //for (auto bg : backgrounds) {
  //  SAFE_DELETE(bg);
  //}
  //for (auto deco : decos) {
  //  SAFE_DELETE(deco);
  //}
  for (auto terr : terrains) {
    SAFE_DELETE(terr);
  }
  for (auto obj : objects) {
    SAFE_DELETE(obj);
  }
  //backgrounds.clear();
  //decos.clear();
  terrains.clear();
  objects.clear();
}

void Level::init() {
  for (auto terr : terrains) {
    terr->Update();
  }
}
void Level::Update() {
  //for (auto obj : objects) {
  //  obj->Update();
  //}
  for (size_t i = 0; i < objects.size(); i++)
  {
    if (objects[i]->GetIsWaitingDelete())
    {
      SAFE_DELETE(objects[i]);
      objects.erase(objects.begin() + i);

      i--;
      continue;
    }
    objects[i]->Update();
  }
  for (size_t i = 0; i < terrains.size(); i++) {
    terrains[i]->Update();
  }
}

void Level::Render() {
  for (auto obj : objects) {
    obj->Render();
  }
  for (auto terr : terrains) {
    terr->Render();
  }
}

void Level::GUI()
{
  for (auto obj : objects) {
    obj->GUI();
  }

}
