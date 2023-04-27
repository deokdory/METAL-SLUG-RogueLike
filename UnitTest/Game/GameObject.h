#pragma once
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

#include "Component/Graphic/ObjectGraphic.h"
#include "Component/Movement/PlayerMovement.h"

class GameObject {
 public:
  GameObject(Vector3 position, Vector3 size);
  virtual ~GameObject();

  virtual void Update();
  virtual void Render();
  virtual void GUI();

  void Move(Vector3 position);

  Vector3 GetPosition() { return this->position; }
  Vector3 GetSize() { return this->size; }
  float GetRotation() { return this->rotation; }

  class ObjectGraphic* GetGraphic();

  void InitGraphic(Animator* animator, ObjectGraphic::Slot slot);
  void InitGraphic(std::wstring path, ObjectGraphic::Slot slot);
  
  void SetFliped(bool isFliped) { this->isFliped = isFliped; }
  bool GetIsFliped() { return isFliped; }

  class Collision* GetCollision();

 protected:
  class ObjectGraphic* graphic = nullptr;
  class Collision* collision = nullptr;

  Vector3 position;
  Vector3 size;
  float rotation = 0;

  bool isFliped = false;

};