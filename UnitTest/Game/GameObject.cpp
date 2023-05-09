#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(Vector3 position, Vector3 size) 
: position(position), size(size), rotation(0) {

  graphic = new ObjectGraphic(this);
  collision = new Collision(this);
}

GameObject::~GameObject() {
  SAFE_DELETE(graphic);
  SAFE_DELETE(collision);
}

void GameObject::Update() {
  if (graphic != nullptr) graphic->Update();
  collision->Update();
}
void GameObject::Render() {
  if (graphic != nullptr) graphic->Render();
  collision->Render();
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
