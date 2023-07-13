#include "Framework.h"
#include "Room.h"

Room::Room(Type type, Room* prevRoom, Direction direction)
 : type(type)
{
	switch (type)
	{
	case Room::Type::ELEVATE:
		mapDataFilePath = MapDataPath + L"passage_1to1.csv";
		break;

	default:
		break;
	}

	initTerrains(mapDataFilePath, prevRoom, direction);
	
	area = new BoundingBox(position, size, 0.0f, Color(0, 1, 1, 0.25f));

	if (type == Type::ELEVATE)
		decorations.push_back(new TextureRect(position, Vector3(384, 960, 0), 0.0f, TexturePath + L"MS5_3_ELEVATOR_PILLAR.png"));

	prevRoom->SetLinkedRoom(direction, this);
	this->SetLinkedRoom(Values::GetDirectionOtherSide(direction), prevRoom);

	setFloorFromPrevRoom(prevRoom, direction);
}

Room::Room(Type type, std::wstring mapDataFilePath, Room* prevRoom, Direction direction)
	: type(type)
{
	initTerrains(mapDataFilePath, prevRoom, direction);

	area = new BoundingBox(position, size, 0.0f, setAreaColor(type));

	if(type == Type::ELEVATE)
    decorations.push_back(new TextureRect(position, Vector3(384, 960, 0), 0.0f, TexturePath + L"MS5_3_ELEVATOR_PILLAR.png"));

	prevRoom->SetLinkedRoom(direction, this);
	auto otherSide = Values::GetDirectionOtherSide(direction);
	this->SetLinkedRoom(Values::GetDirectionOtherSide(direction), prevRoom);

	setFloorFromPrevRoom(prevRoom, direction);
}


Room::Room(Type type)
	: type(type), position(Vector3(0,0,0))
{
	mapDataFilePath = MapDataPath + L"room_elevate.csv";

	initTerrains(mapDataFilePath);

	if (type == Type::ELEVATE)
		decorations.push_back(new TextureRect(position, Vector3(384, 960, 0), 0.0f, TexturePath + L"MS5_3_ELEVATOR_PILLAR.png"));

	area = new BoundingBox(position, size, 0.0f, setAreaColor(type));
}

Room::~Room()
{
	SAFE_DELETE(area);

	for (auto trn : trnBackground) SAFE_DELETE(trn);
	for (auto trn : trnMiddleground) SAFE_DELETE(trn);
	for (auto trn : trnForeground) SAFE_DELETE(trn);

  trnBackground.clear();
  trnMiddleground.clear();
  trnForeground.clear();
}

void Room::Update()
{
	area->Update(position, size, 0);

	for (auto deco : decorations) deco->Update();
	for (auto trn : trnBackground) trn->Update();
	for (auto trn : trnMiddleground) trn->Update();
	for (auto trn : trnStairs) trn->Update();
	for (auto trn : trnForeground) trn->Update();
}
void Room::Render()
{

	area->Render();
	for (auto deco : decorations) deco->Render();
	for (auto trn : trnBackground) trn->Render();
	for (auto trn : trnStairs) trn->Render();
	for (auto trn : trnMiddleground) trn->Render();
}
void Room::ForegroundRender()
{
	for (auto trn : trnForeground) trn->Render();
}

void Room::SetLinkedRoom(Direction direction, Room* linkedRoom)
{
	switch (direction)
	{
	case Direction::UP:
		linkedRoomUp = linkedRoom;
		break;

	case Direction::DOWN:
		linkedRoomDown = linkedRoom;
		break;

	case Direction::LEFT:
		linkedRoomLeft = linkedRoom;
		break;

	case Direction::RIGHT:
		linkedRoomRight = linkedRoom;
		break;

	default:
		break;
	}
}

Room* Room::GetLinkedRoom(Direction direction)
{
	switch (direction)
	{
	case Direction::NONE:
		break;

	case Direction::UP:
		return linkedRoomUp;
		break;

	case Direction::DOWN:
		return linkedRoomDown;

	case Direction::LEFT:
		return linkedRoomLeft;
		break;

	case Direction::RIGHT:
		return linkedRoomRight;
		break;

	default:
		break;
	}
}

std::vector<Terrain*>& Room::GetTerrains(Layer layer)
{
	switch (layer)
	{
	case Room::Layer::BACKGROUND: return trnBackground;
		break;
	case Room::Layer::MIDDLEGROUND: return trnMiddleground;
		break;
	case Room::Layer::FOREGROUND: return trnForeground;
		break;
	case Room::Layer::STAIRS: return trnStairs;
		break;
	}
}

void Room::SetIsActived(bool isActived)
{
	Color color = Color(1, 0, 0, 0.25f);
	if (isActived == false) color = Color(0, 1, 0, 0.25f);

	this->isActived = isActived;
	this->area->ChangeColor(color);
}

Color Room::setAreaColor(Type type)
{
	Color areaColor = Color(0, 0, 0, 0);

	switch (type)
	{
	case Room::Type::EMPTY:
		break;
	case Room::Type::UPGRADE:
		areaColor = Color(1, 1, 0, 0.1f);
		break;

	case Room::Type::BATTLE:
		areaColor = Color(1, 0.5f, 0, 0.1f);
		break;

	case Room::Type::ROOT:
		areaColor = Color(1, 0.5f, 0.25f, 0.1f);
		break;

	case Room::Type::BOSS:
		areaColor = Color(1, 0, 1, 0.1f);
		break;

	case Room::Type::ELIMINATE:
		areaColor = Color(1, 0, 0, 0.1f);
		break;

	case Room::Type::ELEVATE:
		areaColor = Color(0, 1, 1, 0.1f);
		break;

	case Room::Type::PASSAGE:
		areaColor = Color(0, 0, 1, 0.1f);
		break;

	default:
		break;
	}

	return areaColor;
}

bool Room::initTerrains(std::wstring mapDataFilePath, Room* prevRoom, Direction direction)
{
	std::string str_buf;
  std::fstream fs;

  fs.open(mapDataFilePath, ios::in);
  if (fs.fail()) return false;

  // 맵 데이터 쉼표로 분리한 내용들
  std::vector<std::string> tiles;
  tiles.clear();

  // 첫 줄 넘기기 및 X사이즈 체크
  {
    getline(fs, str_buf, '\n');

    String::SplitString(&tiles, str_buf, ",");

    totalTileX = std::stoi(tiles.back()) + 1;
    std::cout << "X Size : " << totalTileX << std::endl;
    tiles.clear();
  }

  // 맨 밑 바닥을 체크하기 위한 동적 배열
  Footholder** bottomFootholder = new Footholder*[totalTileX];

  for (int i = 0; i < totalTileX; i++)
    std::cout << i << std::endl;

  // 맵 데이터 불러오기
  {
    UINT count = 0;

    // 지형 생성자용 데이터
    Terrain::Type trnType = Terrain::Type::NONE;
    Footholder::Type fhType;
    Stair::Type stairType;
    Direction fhSide = Direction::NONE;

    Vector3 trnPosition;
    trnPosition.z = 0;

    bool fhWithDeco = false;

    while (!fs.eof())
    {
      UINT tilePositionX = 0;
      UINT tilePositionY = 0;

      getline(fs, str_buf, '\n');

      String::SplitString(&tiles, str_buf, ",");

      if (tiles.empty()) break;

      if (count == 0)
      {
        totalTileY = std::stoi(tiles[0]) + 1;
        std::cout << "Y Size : " << totalTileY << std::endl;

        size.x = (float)totalTileX * TILESIZE;
        size.y = (float)totalTileY * TILESIZE;
        size.z = 0;

				if (type == Type::ELEVATE) size.y = 960.0f;

        setRoomPosition(prevRoom, direction);
      }

      tilePositionY = std::stoi(tiles[0]);

			int tileFloor = -1;
			if (tilePositionY >= 8) tileFloor = 2;
			else if (tilePositionY >= 5) tileFloor = 1;
			else if (tilePositionY >= 2) tileFloor = 0;

      Vector3 trnPosition;
      trnPosition.z = 0;

      for (UINT i = 1; i < tiles.size(); i++)
      {
        // 앞에 Y구분 열이 있으니까
        tilePositionX = i - 1;

        // 지형들 생성용 데이터들 초기화
        trnType = Terrain::Type::NONE;

        fhType = Footholder::Type::NONE;;
        fhWithDeco = false;
        fhSide = Direction::NONE;

        stairType = Stair::Type::NONE;

        trnPosition = Vector3(0, 0, 0);

        std::vector<Terrain*>* targetLayer = nullptr;

        switch (std::stoi(tiles[i]))
        {
        case EMPTY:
          trnType = Terrain::Type::NONE;
          targetLayer = nullptr;
          break;

        case FOOTHOLDER:
          targetLayer = &trnBackground;
          trnType = Terrain::Type::FOOTHOLDER;
          fhWithDeco = false;

					trnPosition.x = ((float)tilePositionX * TILESIZE) + (TILESIZE / 2) - size.x / 2;
					trnPosition.y = ((float)tilePositionY * TILESIZE) + (TILESIZE / 2) - size.y / 2;

          setEnterFloor(tilePositionX, tilePositionY);

          if (tilePositionX == 0)
          {
            if (tiles[i + 1] != "0") fhType = Footholder::Type::MID;
            else
            {
              fhType = Footholder::Type::EDGE;
              fhSide = Direction::RIGHT;
            }
          }
          else if (tilePositionX == totalTileX - 1)
          {
            if (tiles[i - 1] != "0") fhType = Footholder::Type::MID;
            else
            {
              fhType = Footholder::Type::EDGE;
              fhSide = Direction::LEFT;
            }
          }
          else
          {
            if (tiles[i - 1] != "0" && tiles[i + 1] != "0") fhType = Footholder::Type::MID;
            else if (tiles[i - 1] != "0" && tiles[i + 1] == "0")
            {
              fhType = Footholder::Type::EDGE;
              fhSide = Direction::RIGHT;
            }
            else if (tiles[i - 1] == "0" && tiles[i + 1] != "0")
            {
              fhType = Footholder::Type::EDGE;
              fhSide = Direction::LEFT;
            }
          }


          break;

        case FOOTHOLDER_WITH_DECO:
          targetLayer = &trnBackground;
          trnType = Terrain::Type::FOOTHOLDER;
          fhWithDeco = true;

					trnPosition.x = ((float)tilePositionX * TILESIZE) + (TILESIZE / 2) - size.x / 2;
					trnPosition.y = ((float)tilePositionY * TILESIZE) + (TILESIZE / 2) - size.y / 2;

          setEnterFloor(tilePositionX, tilePositionY);

          if (tilePositionX == 0)
          {
            fhType = Footholder::Type::MID;
            fhSide = Direction::LEFT;
          }
          else if (tilePositionX == totalTileX - 1)
          {
            fhType = Footholder::Type::MID;
            fhSide = Direction::RIGHT;
          }
          else
          {
            if (tiles[i - 1] != "2" && tiles[i + 1] != "2")
            {
              fhType = Footholder::Type::MID;
              fhSide = Direction::LEFT;
            }
            else if (tiles[i - 1] != "2" && tiles[i + 1] == "2")
            {
              fhType = Footholder::Type::MID;
              fhSide = Direction::LEFT;
            }
            else if (tiles[i - 1] == "2" && tiles[i + 1] != "2")
            {
              fhType = Footholder::Type::MID;
              fhSide = Direction::RIGHT;
            }
          }
          break;
        case STAIR_NORMAL_UP:
          targetLayer = &trnStairs;

          trnType = Terrain::Type::STAIR;
          stairType = Stair::Type::NORMAL_UP;

          trnPosition.x = ((float)tilePositionX * TILESIZE) + (TILESIZE * 3) - size.x / 2;
          trnPosition.y = ((float)tilePositionY * TILESIZE) + (TILESIZE) - size.y / 2;

          break;
        case STAIR_NORMAL_DOWN:
          targetLayer = &trnStairs;

          trnType = Terrain::Type::STAIR;
          stairType = Stair::Type::NORMAL_DOWN;

          trnPosition.x = ((float)tilePositionX * TILESIZE) - (TILESIZE * 2) - size.x / 2;
          trnPosition.y = ((float)tilePositionY * TILESIZE) + TILESIZE - size.y / 2;

          break;
        default:
          trnType = Terrain::Type::NONE;
          targetLayer = nullptr;
          break;
        }

        if (targetLayer != nullptr)
        {
					switch (trnType)
					{
					case Terrain::Type::NONE:
						break;
					case Terrain::Type::FOOTHOLDER:
					{
						Footholder* footholder = new Footholder(trnPosition + position, tileFloor, fhType, fhSide, fhWithDeco);
						targetLayer->push_back(footholder);

						bottomFootholder[tilePositionX] = footholder;
					}
            break;

          case Terrain::Type::STAIR:
            targetLayer->push_back(new Stair(trnPosition + position, tileFloor, stairType));
            break;
          default:
            break;
          }
        }
        count++;
      }
      tiles.clear();
    }

    std::cout << "Enter floor left : " << enterFloorL << std::endl
      << "Enter floor right : " << enterFloorR << std::endl;

  }
  fs.close();

	for (int i = 0; i < totalTileX; i++)
		bottomFootholder[i]->SetCanDropDown(false);

	delete[] bottomFootholder;
  return true;
}

void Room::setRoomPosition(Room* prevRoom, Direction direction)
{
	Vector3 prevRoomPosition = Values::ZeroVec3;
	Vector3 prevRoomSize = Values::ZeroVec3;

	// 이전 방에 붙이는 중이라면 포지션을 그에 따라 수정
	if (prevRoom != nullptr && direction != Direction::NONE)
	{
		prevRoomPosition = prevRoom->GetPosition();
		prevRoomSize = prevRoom->GetSize();

		switch (direction)
		{
		case Direction::UP:
			position.x = prevRoomPosition.x;
			position.y = prevRoomPosition.y + prevRoomSize.y / 2 + size.y / 2;
			position.z = 0;
			break;

		case Direction::DOWN:
			position.x = prevRoomPosition.x;
			position.y = prevRoomPosition.y - prevRoomSize.y / 2 - size.y / 2;
			position.z = 0;
			break;

		case Direction::LEFT:
			position.x = prevRoomPosition.x - prevRoomSize.x / 2 - size.x / 2;
			position.y = prevRoomPosition.y;
			position.z = 0;
			break;

		case Direction::RIGHT:
			position.x = prevRoomPosition.x + prevRoomSize.x / 2 + size.x / 2;
			position.y = prevRoomPosition.y;
			position.z = 0;
			break;

		default:
			break;
		}
	}
}

void Room::setFloorFromPrevRoom(Room* prevRoom, Direction direction)
{
	switch (direction)
	{
	case Direction::NONE:
		break;
	case Direction::UP:
		floor = prevRoom->GetFloor() + 1;
		break;
	case Direction::DOWN:
		floor = prevRoom->GetFloor() - 1;
		break;
	case Direction::LEFT:
	case Direction::RIGHT:
		floor = prevRoom->GetFloor();
		break;
	default:
		break;
	}
}

void Room::setEnterFloor(UINT tilePositionX, UINT tilePositionY)
{
	// 좌측 입구 체크
	if (tilePositionX == 0
		&& (tilePositionY == 2 || tilePositionY == 5 || tilePositionY == 8))
	{
		// 입구 중복일 시 에러
		if (enterFloorL != -1)
		{
			std::cout << "Room::Enter is doubled" << std::endl;
			assert(false);
		}

		switch (tilePositionY)
		{
		case 2:
			enterFloorL = 0;
			break;

		case 5:
			enterFloorL = 1;
			break;

		case 8:
			enterFloorL = 2;
			break;

		default:
			break;
		}
	}
	// 우측 입구 체크
	else if (tilePositionX == totalTileX - 1
		&& (tilePositionY == 2 || tilePositionY == 5 || tilePositionY == 8))
	{
		// 입구 중복일 시 에러
		if (enterFloorR != -1)
		{
			std::cout << "Room::Enter is doubled" << std::endl;
			assert(false);
		}
		switch (tilePositionY)
		{
		case 2:
			enterFloorR = 0;
			break;

		case 5:
			enterFloorR = 1;
			break;

		case 8:
			enterFloorR = 2;
			break;

		default:
			break;
		}
	}
}