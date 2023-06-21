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

  for (auto room : rooms)
  {
    room->Update();
    room->SetIsActived(false);
  }
  if (playerCurrentRoom)
  {
    playerCurrentRoom->SetIsActived(true);

    auto* temp = playerCurrentRoom->GetLinkedRoom(Direction::LEFT);
    Room* linkedRoom = nullptr;

    if (temp)
    {
      linkedRoom = temp;
      linkedRoom->SetIsActived(true);
      temp = linkedRoom->GetLinkedRoom(Direction::LEFT);
    }

    if (temp)
    {
      linkedRoom = temp;
      linkedRoom->SetIsActived(true);
    }

    temp = playerCurrentRoom->GetLinkedRoom(Direction::RIGHT);
    if (temp)
    {
      linkedRoom = temp;
      linkedRoom->SetIsActived(true);
      temp = linkedRoom->GetLinkedRoom(Direction::RIGHT);
    }

    if (temp)
    {
      linkedRoom = temp;
      linkedRoom->SetIsActived(true);
    }
  }

  objectsUpdate(objects);

  player->Update();
  checkObjectsCurrentRoom(player);

  objectsUpdate(objForeground);

  playerCurrentRoom = player->GetCurrentRoom();


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

  player->Render();

  for (auto obj : objForeground)
  {
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

void Level::objectsUpdate(std::vector<GameObject*>& objects)
{
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
    checkObjectsCurrentRoom(objects[i]);
  }
}

void Level::checkObjectsCurrentRoom(GameObject* object)
{
  Room* objectCurrentRoom = nullptr;

  float nearWithEdge = 6000.0f;
  float nearest = 6000.0f;

  for (auto room : rooms)
  {
    if (BoundingBox::AABB(object->GetCollision()->GetBase(), room->GetArea()))
    {
      float objectPositionX = object->GetPosition().x;
      float roomPositionX = room->GetPosition().x;
      float roomSizeX = room->GetSize().x;

      if (objectCurrentRoom == nullptr)
      {
        objectCurrentRoom = room;
        object->SetCurrentRoom(room);
      }
      else
      {
        if (objectPositionX > roomPositionX && objectPositionX < roomPositionX + roomSizeX / 2)
        {
          objectCurrentRoom = room;
          object->SetCurrentRoom(room);
        }
        else if (objectPositionX < roomPositionX && objectPositionX > roomPositionX - roomSizeX / 2)
        {
          objectCurrentRoom = room;
          object->SetCurrentRoom(room);
        }
      }
    }
  }
}
