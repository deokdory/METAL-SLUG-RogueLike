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

void GameObject::InitGraphic(Animator* animator) {
  graphic = new AnimatedGraphic(this, animator);
}

void GameObject::InitGraphic(Animator* lowerAnim, Animator* upperAnim) {
  graphic = new AgentGraphic(this, lowerAnim, upperAnim);
}

void GameObject::InitGraphic(std::wstring path) {
  graphic = new TexturedGraphic(this, path);
}
