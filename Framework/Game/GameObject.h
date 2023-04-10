#pragma once
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

class GameObject {
 public:
  GameObject(Vector3 position, Vector3 size);
  virtual ~GameObject();

  virtual void update() = 0;
  virtual void render() = 0;

  void move(Vector3 position) {
    position_.x += position.x;
    position_.y += position.y;
    position_.z += position.z;
  };

  Vector3 getPosition() { return position_; }
  Vector3 getSize() { return size_; }

 protected:
  AnimationRect* animRect_ = nullptr;
  Animator* animator_ = nullptr;

  BoundingBox* bottom_ = nullptr;
  BoundingBox* hitbox_ = nullptr;

  Vector3 position_;
  Vector3 size_;
};