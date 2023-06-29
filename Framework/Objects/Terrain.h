#pragma once

class Terrain : public GameObject 
{
public:
  enum class Type
  {
    NONE,
    FOOTHOLDER,
    STAIR
  };

   Terrain();
   Terrain(Vector3 position, Type type);

   virtual ~Terrain();

   virtual void Update();
   virtual void Render();

   Type GetTerrainType() { return terrainType; }
   virtual float GetFootholderTop(Vector3 objectPosition) = 0;

   void SetCanDropDown(bool canDropDown) { this->canDropDown = canDropDown; }
   bool GetCanDropDown() { return canDropDown; }

protected:
  Terrain::Type terrainType = Type::NONE;
  bool canDropDown = true; // 밑점프가 가능한 발판인지
};

class Footholder : public Terrain
{
public:
  enum class Type
  {
    NONE,
    EDGE,
    MID,
  };

  Footholder() = default;
  Footholder(Vector3 position, Footholder::Type footholderType, Direction side = Direction::NONE, bool withDeco = false);

  float GetFootholderTop(Vector3 objectPosition);

private:
  bool withDeco = false;
};

class Stair : public Terrain
{
public:
  enum class Type
  {
    NONE,
    NORMAL_UP,
    NORMAL_DOWN,
    LONG_UP,
    LONG_DOWN
  };

  Stair(Vector3 position, Stair::Type stairType);

  float GetFootholderTop(Vector3 objectPosition);
};