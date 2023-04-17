#pragma once
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

#include "Component/Graphic/IGraphic.h"

class GameObject {
 public:
  GameObject(Vector3 position, Vector3 size);
  virtual ~GameObject();

  virtual void Update();
  virtual void Render();

  void Move(Vector3 position);

  Vector3 GetPosition() { return position; }
  Vector3 GetSize() { return size; }
  float GetRotation() { return rotation; }

  IGraphic* GetGraphic() { return graphic; }

  void InitGraphic(IGraphic::Type type);
  void SetGraphicResource(Animator* animator, IGraphic::Slot slot);
  void SetGraphicResource(std::wstring path);
  
  void SetFliped(bool bFliped) { this->bFliped = bFliped; }
  bool GetFliped() { return bFliped; }

  class Collision* GetCollision() {
    return collision;
  }

 protected:

  class IGraphic* graphic = nullptr;
  class Collision* collision = nullptr;

  Vector3 position;
  Vector3 size;
  float rotation = 0;

  bool bFliped = false;

};