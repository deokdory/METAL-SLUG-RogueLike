#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain(Vector3 position, Type type, int floor)
  : GameObject(position), terrainType(type), floor(floor)
{
}

Terrain::Terrain()
  : GameObject({ 0, 0, 0 })
{
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

Footholder::Footholder(Vector3 position, int floor, Footholder::Type footholderType, Direction side, bool withDeco)
 : Terrain(position, Terrain::Type::FOOTHOLDER, floor), withDeco(withDeco)
{
  objectType = GameObject::Type::TERRAIN;
  TerrainCollision* trnCollision = nullptr;
  graphic->SetAnchorPoint(AnchorPoint::CENTER);

  graphic->InitTexture(TexturePath + L"MS5_2-2_TRN_FOOTHOLDER.png");
  Vector2 texel = { 1.0f / 384.0f, 1.0f / 64.0f };
  float endY = 63 * texel.y;

  size = { 64, 64, 0 };

  switch (footholderType)
  {
  case Footholder::Type::EDGE:
    switch (side)
    {
    case Direction::LEFT:
      if (withDeco)
      {
        graphic->SetUV({ 384 * texel.x, 0 }, { 447 * texel.x, endY });
        trnCollision = new TerrainCollision(this, TerrainCollision::Type::FH_EDGE_L);
      }
      else
      {
        graphic->SetUV({ 0,0 }, { 63 * texel.x, endY });
        trnCollision = new TerrainCollision(this, TerrainCollision::Type::FH_EDGE_L);
      }
      break;
    case Direction::RIGHT:
    default:
      if (withDeco)
      {
        graphic->SetUV({ 128 * texel.x, 0 }, { 191 * texel.x, endY });
        trnCollision = new TerrainCollision(this, TerrainCollision::Type::FH_EDGE_R);
      }
      else
      {
        graphic->SetUV({ 320 * texel.x, 0 }, { 383 * texel.x, endY });
        trnCollision = new TerrainCollision(this, TerrainCollision::Type::FH_EDGE_R);
      }
      break;
    }
    break;

  case Footholder::Type::MID:
  {
    if (withDeco)
    {
      switch (side)
      {
      case Direction::LEFT:
        graphic->SetUV({ 64 * texel.x, 0 }, { 127 * texel.x, endY });
        trnCollision = new TerrainCollision(this, TerrainCollision::Type::FH_MID);
        break;
      case Direction::RIGHT:
      default:
        graphic->SetUV({ 192 * texel.x, 0 }, { 255 * texel.x, endY });
        trnCollision = new TerrainCollision(this, TerrainCollision::Type::FH_MID);
        break;
      }
    }
    else
    {
      graphic->SetUV({ 256 * texel.x, 0 }, { 319 * texel.x, endY });
      trnCollision = new TerrainCollision(this, TerrainCollision::Type::FH_MID);
    }
  }
  break;
  }

  if (trnCollision == nullptr)
  {
    std::cout << "Terrain::TerrainCollision is null!" << std::endl;
    assert(false);
  }

  trnCollision->InitializeBase();
  collision = trnCollision;

  SetAnchorPoint(AnchorPoint::CENTER);
}


float Footholder::GetFootholderTop(Vector3 objectPosition)
{
  return collision->GetFootholder()->GetRect()->LT.y;
}


Stair::Stair(Vector3 position, int floor, Stair::Type stairType)
  : Terrain(position, Terrain::Type::STAIR, floor)
{
  objectType = GameObject::Type::TERRAIN;
  TerrainCollision* trnCollision = nullptr;
  graphic->SetAnchorPoint(AnchorPoint::CENTER);

  canDropDown = true;

  size = { 384, 256, 0 };

  switch (stairType)
  {
  case Stair::Type::NORMAL_UP:
    graphic->InitTexture(TexturePath + L"MS5_2-2_TRN_STAIR_UP_SHORTROAD.png");
    trnCollision = new TerrainCollision(this, TerrainCollision::Type::STAIR_UP);
    break;
  case Stair::Type::NORMAL_DOWN:
    graphic->InitTexture(TexturePath + L"MS5_2-2_TRN_STAIR_DOWN_SHORTROAD.png");
    trnCollision = new TerrainCollision(this, TerrainCollision::Type::STAIR_DOWN);
    break;
  default:
    break;
  }

  if (trnCollision == nullptr)
  {
    std::cout << "Terrain::TerrainCollision is null!" << std::endl;
    assert(false);
  }

  trnCollision->InitializeBase();
  collision = trnCollision;

  SetAnchorPoint(AnchorPoint::CENTER);
}

float Stair::GetFootholderTop(Vector3 objectPosition)
{
  BoundingBox* footholder = collision->GetFootholder();

  Vector3 footholderPosition = footholder->GetPosition();
  float footholderRotation = footholder->GetRotation();

  float r = 0.0f;
  float stairEdgeX = 0.0f;

  stairEdgeX = footholder->GetSize().x / 2 * std::cos(D3DXToRadian(footholderRotation));

  r = -(footholderPosition.x - objectPosition.x);

  if (r > stairEdgeX) r = stairEdgeX;
  else if (r < -stairEdgeX) r = -stairEdgeX;

  return footholderPosition.y + (r * std::tan(D3DXToRadian(footholderRotation)));
}