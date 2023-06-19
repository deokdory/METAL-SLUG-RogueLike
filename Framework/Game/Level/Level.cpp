#include "Framework.h"
#include "Level.h"

Level::Level()
{
  
}

Level::~Level() {
 
  for (auto room : rooms) SAFE_DELETE(room);
  for (auto terr : terrains) SAFE_DELETE(terr);
  for (auto obj : objects) SAFE_DELETE(obj);

  rooms.clear();
  terrains.clear();
  objects.clear();
}

void Level::init() {
  for (auto terr : terrains) {
    terr->Update();
  }
}
void Level::Update() {

  for (auto room : rooms) room->Update();

  //for (size_t i = 0; i < terrains.size(); i++) {
  //  terrains[i]->Update();
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

}

void Level::Render() {

  for (auto bg : backgrounds)
  {
    bg->Render();
  }

  //for (auto terr : terrains) {
  //  terr->Render();
  //}

  for (auto room : rooms) {
    room->Render();
  }

  for (auto obj : objects) {
    obj->Render();
  }

  for (auto room : rooms) {
    room->ForegroundRender();
  }
}

void Level::GUI()
{
  for (auto obj : objects) {
    obj->GUI();
  }
}
