#pragma once
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

// 오브젝트의 상태 정의
  enum class ObjState {
  IDLE,
  RUNNING,
  FALLING,
  SLIDING,
  SHOOTING,
  MELEE_ATTACKING,
  THROWING
};

class GameObject {
 public:
  GameObject(Vector3 position, Vector3 size);
  virtual ~GameObject();

  virtual void update();
  virtual void render();

  void move(Vector3 position);

  Vector3 getPosition() { return position; }
  Vector3 getSize() { return size; }
  float getRotation() { return rotation; }

  ObjState& GetState() { return state; }

  void InitGraphic(Animator* animator);
  void InitGraphic(std::wstring path);

  class Collision* GetCollision() {
    return collision;
  }

 protected:
  class IGraphic* graphic = nullptr;
  class Collision* collision = nullptr;

  Vector3 position;
  Vector3 size;
  float rotation = 0;

  ObjState state = ObjState::IDLE;
};