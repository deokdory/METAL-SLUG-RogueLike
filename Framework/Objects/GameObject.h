#pragma once

class GameObject {
 public:
  enum class Type { NONE, CHARACTER, PLAYER, VEHICLE, PROP, TERRAIN, BULLET, THROWABLE };

  GameObject(Vector3 position, Vector3 size);
  GameObject(Vector3 position);

  virtual ~GameObject();

  virtual void Update();
  virtual void Render();
  virtual void GUI();

  void Move(Vector3 position);
  void ForceSetPosition(Vector3 position) { this->position = position; }

  Vector3 GetPosition() { return this->position; }
  Vector3 GetSize() { return this->size; }
  float GetRotation() { return this->rotation; }

  class ObjectGraphic* GetGraphic();

  void InitGraphic(Animator* animator, ObjectGraphic::Slot slot);
  void InitGraphic(std::wstring path, ObjectGraphic::Slot slot);

  void SetFliped(bool isFliped) { this->isFliped = isFliped; }
  bool GetIsFliped() { return isFliped; }

  class Collision* GetCollision();

  bool GetIsWaitingDelete() { return isWaitingDelete; }
  void SetIsWaitingDelete(bool isWaitingDelete) { this->isWaitingDelete = isWaitingDelete; }

  GameObject::Type GetObjectType() { return objectType; }

  AnchorPoint GetAnchorPoint() { return anchorPoint; }
  void SetAnchorPoint(AnchorPoint anchorPoint);

protected:
  Type objectType = Type::NONE;

  class ObjectGraphic* graphic = nullptr;
  class Collision* collision = nullptr;

  AnchorPoint anchorPoint = AnchorPoint::MID_BOT;

  Vector3 position = Values::ZeroVec3;
  Vector3 size = Values::ZeroVec3;
  float rotation = 0;

  bool isFliped = false;

  bool isWaitingDelete = false;
};