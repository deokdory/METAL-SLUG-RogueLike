#pragma once
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

class GameObject {
 public:
  GameObject(Vector3 position, Vector3 size);
  virtual ~GameObject();

  virtual void update();
  virtual void render();

  void move(Vector3 position) {
    position.x += position.x;
    position.y += position.y;
    position.z += position.z;
  };

  Vector3 getPosition() { return position; }
  Vector3 getSize() { return size; }

 protected:
  AnimationRect* animRect = nullptr;
  Animator* animator = nullptr;

  BoundingBox* hitbox = nullptr;

  Vector3 position;
  Vector3 size;
};