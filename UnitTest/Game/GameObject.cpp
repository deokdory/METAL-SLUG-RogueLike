#include "stdafx.h"
#include "GameObject.h"

#include "Component/Graphic/IGraphic.h"

#include "Component/Graphic/TexturedGraphic.h"
#include "Component/Graphic/AnimatedGraphic.h"
#include "Component/Graphic/AgentGraphic.h"

#include "Component/Collision/Collision.h"

GameObject::GameObject(Vector3 position, Vector3 size) 
: position(position), size(size), rotation(0) {
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

void GameObject::InitGraphic(IGraphic::Type type) {

  switch (type) {
  case IGraphic::Type::TEXTURE_GRAPHIC: {
      graphic = new TexturedGraphic(this);
      return;
    }
    case IGraphic::Type::ANIMATION_GRAPHIC: {
      graphic = new AnimatedGraphic(this);
      return;
    }
    case IGraphic::Type::AGENT_GRAPHIC: {
      graphic = new AgentGraphic(this);
      return;
    }
    default:
      return;
  }
}

void GameObject::SetGraphicResource(Animator* animator, IGraphic::Slot slot) {
  graphic->SetResource(animator, slot);
}

void GameObject::SetGraphicResource(std::wstring path) {
  graphic->SetResource(path);
}