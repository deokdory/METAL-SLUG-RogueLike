#pragma once
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

class Character {
 public:
  Character(Vector3 position, Vector3 size);
  virtual ~Character();

  virtual void Update() = 0;
  virtual void Render() = 0;

  bool IsOnGround() const { return isOnGround; }

  void SetGravity(float gravity) { this->gravity = gravity; }

  void SetIsOnGround(bool isOnGround = true) { this->isOnGround = isOnGround; }
  void SetGlobalSpeed(float globalSpeed) { this->globalSpeed = globalSpeed; }

  Vector3 GetPosition() { return this->animRect->GetPosition(); }
  Vector3 GetSize() { return this->animRect->GetSize(); }

  void SetPosition(Vector3 position) { this->animRect->SetPosition(position); }

 protected:
  AnimationRect* animRect = nullptr;
  Animator* animator = nullptr;

 protected:
  bool isOnGround = true;
  //bool isJumping = false;

  float globalSpeed = 1.0f;
  float gravity = 20.0f;

  float ySpeed = 0.0f;

  float moveSpeed = 300.f;
  float jumpSpeed = 100.0f;
};