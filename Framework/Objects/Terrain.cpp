#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain(Vector3 position, Type type)
  : GameObject(position), terrainType(type)
{

  objectType = GameObject::Type::TERRAIN;

  TerrainCollision* trnCollision = nullptr;
  graphic->SetAnchorPoint(AnchorPoint::CENTER);

  if (type == Terrain::Type::STAIR_UP || type == Terrain::Type::STAIR_DOWN)
  {
    size = { 640, 257, 0 };
    switch (type)
    {
    case Terrain::Type::STAIR_UP:
      graphic->InitTexture(TexturePath + L"MS5_2-2_TRN_STAIR_UP.png");
      trnCollision = new TerrainCollision(this, TerrainCollision::Type::STAIR_UP);
      break;
    case Terrain::Type::STAIR_DOWN:
      graphic->InitTexture(TexturePath + L"MS5_2-2_TRN_STAIR_DOWN.png");
      trnCollision = new TerrainCollision(this, TerrainCollision::Type::STAIR_DOWN);
      break;
    default:
      break;
    }
  }
  else
  {
    graphic->InitTexture(TexturePath + L"MS5_2-2_TRN_FOOTHOLDER.png");
    Vector2 texel = { 1.0f / 384.0f, 1.0f / 64.0f };
    float endY = 63 * texel.y;
    switch (type)
    {
    case Terrain::Type::FH_EDGE_L:
      graphic->SetUV({ 0,0 }, { 63 * texel.x, endY});
      trnCollision = new TerrainCollision(this, TerrainCollision::Type::FH_EDGE_L);
      break;
    case Terrain::Type::FH_MID:
      graphic->SetUV({ 256 * texel.x, 0 }, { 319 * texel.x, endY });
      trnCollision = new TerrainCollision(this, TerrainCollision::Type::FH_MID);
      break;
    case Terrain::Type::FH_MID_L_WP:
      graphic->SetUV({ 64 * texel.x, 0 }, { 127 * texel.x, endY });
      trnCollision = new TerrainCollision(this, TerrainCollision::Type::FH_MID);
      break;
    case Terrain::Type::FH_MID_R_WP:
      graphic->SetUV({ 192 * texel.x, 0 }, { 255 * texel.x, endY });
      trnCollision = new TerrainCollision(this, TerrainCollision::Type::FH_MID);
      break;
    case Terrain::Type::FH_EDGE_R_WP:
      graphic->SetUV({ 128 * texel.x, 0 }, { 191 * texel.x, endY });
      trnCollision = new TerrainCollision(this, TerrainCollision::Type::FH_EDGE_R);
      break;
    case Terrain::Type::FH_EDGE_R:
      graphic->SetUV({ 320 * texel.x, 0 }, { 383 * texel.x, endY });
      trnCollision = new TerrainCollision(this, TerrainCollision::Type::FH_EDGE_R);
      break;
    default:
      break;
    }
    size = { 64, 64, 0 };
  }

  if (trnCollision == nullptr)
  {
    std::cout << "Terrain::TerrainCollision is null!" << std::endl;
    assert(false);
  }

  collision = trnCollision;
}

Terrain::~Terrain() {
  SAFE_DELETE(collision);
}

void Terrain::Update() { 
  graphic->Update();
  collision->Update();
}

void Terrain::Render() { 
  graphic->Render();
  collision->Render();
}