#pragma once

class Collision {

 public:
   enum class Slot
   { TOP, BASE, BOTTOM };

  Collision(class GameObject* object);
  virtual ~Collision();

  virtual void Update();
  virtual void Render();

  void InitializeBase();
  void InitializeFootholder();
  //void InitializeBottom();

  void DeleteBase()   { SAFE_DELETE(base) };
  void DeleteFootholder()    { SAFE_DELETE(footholder) };

  BoundingBox* GetBase() { return base; }
  BoundingBox* GetFootholder() { return footholder; }

  void SetAnchorPoint(AnchorPoint anchorPoint) { this->anchorPoint = anchorPoint; }

  const float GetFootholderThickness() { return footholderThickness; }

 protected:
  class GameObject* object = nullptr;

  Vector3 objPos, objSize;
  float objRotation;

  AnchorPoint anchorPoint = AnchorPoint::MID_BOT;

  BoundingBox* base = nullptr;
  BoundingBox* footholder = nullptr;

  const float footholderThickness = 4;
};

class TerrainCollision : public Collision
{
public:
  enum class Type
  {
    FH_MID, // Foot holder
    FH_EDGE_L,
    FH_EDGE_R,
    STAIR_UP,
    STAIR_DOWN
  };

  TerrainCollision(GameObject* object, Type type);

  virtual void Update();

  //float GetFootholderTop(Vector3 position);
  
private:
  TerrainCollision::Type terrainType;

  Vector3 position = Values::ZeroVec3;
  Vector3 size = Values::ZeroVec3;
  float rotation = 0.0f;
};