#pragma once
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

class Decoration {
 public:
  Decoration(Vector3 position, Vector3 size);
  ~Decoration();

  void update();
  void render();

 private:
  AnimationRect* animRect;
  Animator* animator;
};