#pragma once

class Collision {
 public:
  Collision(class GameObject* object);
  ~Collision();

  virtual void Update();
  virtual void Render();

  void InitializeBase();
  void InitializeTop();
  void InitializeBottom();

  BoundingBox* GetBase() { return base; }
  BoundingBox* GetBottom() { return bottom; }
  BoundingBox* GetTop() { return top; }

 protected:
  class GameObject* object = nullptr;

  Vector3 objPos, objSize;
  float objRotation;

  BoundingBox* base = nullptr;
  BoundingBox* bottom = nullptr;
  BoundingBox* top = nullptr;

  const float collisionThickness = 4;
};