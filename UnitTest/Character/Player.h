#pragma once

#include "Game/Character.h"
//#include "Geometries/TextureRectTest.h"

#define MAX_FALLING_SPEED 200.f

struct Equip {
  void Render() {
    rect->Render();
    collision->Render();
  }

  TextureRect* rect = nullptr;
  BoundingBox* collision = nullptr;
};

class Player : public Character {
 public:
  Player(Vector3 position, Vector3 size);
  ~Player();

  virtual void Update() override;
  virtual void Render() override;

  void Idle();
  void MoveLeft();
  void MoveRight();
  void Jump();
  void Sword();
  void Guard(bool bGuarding);

  void Falling();

  float GetYSpeed() const { return ySpeed; }

  BoundingBox* GetFootCollision() { return foot; }
  BoundingBox* GetHeadCollision() { return head; }

  private:
  struct Equip sword, shield;

  BoundingBox* foot = nullptr;
  BoundingBox* head = nullptr;

  bool bAttacking = false;
  bool bGuarding = false;
  float timer = 0.0f;

  float collisionHeight = 0.0f;
};