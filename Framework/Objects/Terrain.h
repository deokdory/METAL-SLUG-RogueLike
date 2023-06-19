#pragma once

class Terrain : public GameObject {
 public:
   enum class Type
   {
     NONE,
     FH_EDGE_L, 
     FH_MID, 
     FH_MID_L_WP, // With Pannel (Decoration)
     FH_MID_R_WP, 
     FH_EDGE_R_WP, 
     FH_EDGE_R, 
     STAIR_UP, 
     STAIR_DOWN
   };

   Terrain(Vector3 position, Type type);
   ~Terrain();

   virtual void Update();
   virtual void Render();

   Type GetTerrainType() { return terrainType; }
   float GetFootholderTop(Vector3 position);

private:
  Type terrainType;
};