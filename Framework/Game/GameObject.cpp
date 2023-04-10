#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(Vector3 position, Vector3 size) {
  animRect_ = new AnimationRect(position, size);
  animator_ = new Animator();

  hitbox_ = new BoundingBox();
  bottom_ = new BoundingBox();
}

GameObject::~GameObject() {
  SAFE_DELETE(hitbox_);
  SAFE_DELETE(bottom_);

  SAFE_DELETE(animator_);
  SAFE_DELETE(animRect_);
}
