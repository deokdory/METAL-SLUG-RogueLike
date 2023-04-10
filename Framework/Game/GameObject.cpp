#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(Vector3 position, Vector3 size) 
: position(position), size(size) {

  animRect = new AnimationRect(position, size);
  animator = new Animator();

  hitbox = new BoundingBox(position, size, 0.0f, Color(0, 0, 1, 0.3f));

}

GameObject::~GameObject() {
  SAFE_DELETE(hitbox);

  SAFE_DELETE(animator);
  SAFE_DELETE(animRect);
}


void GameObject::update() { 

  animRect->SetPosition(position);
  animRect->SetSize(size);

  animRect->Update();
  hitbox->Update(position, size, 0.0f);
  animator->Update();
}
void GameObject::render() {
  animRect->Render();
  hitbox->Render();
}