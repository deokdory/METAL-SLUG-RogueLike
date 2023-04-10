#pragma once
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

class Decoration {
 public:
  Decoration();
  ~Decoration();

  void update();
  void render();

 private:
  AnimationRect* animRect = nullptr;
  Animator* animator = nullptr;
};