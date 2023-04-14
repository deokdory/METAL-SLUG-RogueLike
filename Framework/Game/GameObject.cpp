#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(Vector3 position, Vector3 size) 
: position(position), size(size), rotation(0) {
  collision = new Collision(this);
}

GameObject::~GameObject() {
  SAFE_DELETE(graphic);
  SAFE_DELETE(collision);
}

void GameObject::update() {
  if (graphic != nullptr) graphic->update();
  collision->update();
}
void GameObject::render() {
  if (graphic != nullptr) graphic->render();
  collision->render();
}

void GameObject::move(Vector3 position) { this->position += position; }

void GameObject::InitGraphic(UINT type) {
  switch (type) {
    case TEXTURE_GRAPHIC: {
      graphic = new TexturedGraphic(this);
      return;
    }
    case ANIMATION_GRAPHIC: {
      graphic = new AnimatedGraphic(this);
      return;
    }
    case AGENT_GRAPHIC: {
      graphic = new AgentGraphic(this);
      return;
    }
    default:
      return;
  }
}

void GameObject::setGraphicResource(Animator* animator, UINT slot) {
  graphic->setResource(animator, slot);
}
void GameObject::setGraphicResource(std::wstring path) {
  graphic->setResource(path);
}
