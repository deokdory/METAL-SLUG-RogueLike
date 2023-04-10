#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(Vector3 position, Vector3 size) {
  animRect = new AnimationRect(position, size);
  animator = new Animator();

  hitbox = new BoundingBox();
}

GameObject::~GameObject() {
  SAFE_DELETE(hitbox);

  SAFE_DELETE(animator);
  SAFE_DELETE(animRect);
}


void GameObject::update() { 
  animRect->Update();
  hitbox->Update(size);
  animator->Update();
}
void GameObject::render() {
  animRect->Render();
  hitbox->Render();
}