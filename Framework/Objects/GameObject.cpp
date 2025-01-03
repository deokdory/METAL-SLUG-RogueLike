#include "Framework.h"
#include "GameObject.h"

#include "Game/Level/Room/Room.h"

GameObject::GameObject(Vector3 position, Vector3 size) 
: position(position), size(size), rotation(0) {

  graphic = new ObjectGraphic(this);
  collision = new Collision(this);
  collision->InitializeBase();
}

GameObject::GameObject(Vector3 position) // 지형 용 생성자
  : position(position), rotation(0), isActived(true)
{
  graphic = new ObjectGraphic(this);
  //collision->InitializeBase();
  //collision = new Collision(this);
}

GameObject::~GameObject() {
  SAFE_DELETE(graphic);
  SAFE_DELETE(collision);
}

void GameObject::Update() {

  if (isActived)
  {
    if (graphic != nullptr) graphic->Update();
  }

  collision->Update();

  if (objectType != Type::PLAYER)
  {
    if (currentRoom)
    {
      if (currentRoom->GetIsActived())
      {
        isActived = true;
      }
      else
      {
        isActived = false;
      }
    }
    else isActived = false;
  }
}

void GameObject::Render() {
  if (isActived)
  {
    if (graphic != nullptr) graphic->Render();
    collision->Render();
  }
}

void GameObject::GUI()
{
}

void GameObject::Move(Vector3 position) { this->position += position; }

ObjectGraphic* GameObject::GetGraphic()
{
  return graphic;
}

void GameObject::InitGraphic(Animator* animator, ObjectGraphic::Slot slot)
{
  graphic->InitAnimation(animator, slot);
}

void GameObject::InitGraphic(std::wstring path, ObjectGraphic::Slot slot)
{
  graphic->InitTexture(path, slot);
}

Collision* GameObject::GetCollision()
{
  return collision;
}

void GameObject::SetAnchorPoint(AnchorPoint anchorPoint)
{
  this->anchorPoint = anchorPoint;

  graphic->SetAnchorPoint(anchorPoint);
  collision->SetAnchorPoint(anchorPoint);

}

void GameObject::SetCurrentRoom(Room* currentRoom)
{
  this->currentRoom = currentRoom;
}

Room* GameObject::GetCurrentRoom()
{
  return currentRoom;
}

void GameObject::Interaction(GameObject* object)
{
}