#include "Framework.h"
#include "Room.h"

Room::Room(Type type, Room* prevRoom, Direction direction)
 : type(type)
{
	switch (type)
	{
	case Room::Type::EMPTY:
		break;
	case Room::Type::UPGRADE:
		break;
	case Room::Type::BATTLE:
		break;
	case Room::Type::ROOT:
		break;
	case Room::Type::BOSS:
		break;
	case Room::Type::ELIMINATE:
		break;
	case Room::Type::ELEVATE:
		mapDataFilePath = MapDataPath + L"passage_1to1.csv";
		break;
	case Room::Type::PASSAGE:
		break;
	default:
		break;
	}
	initTerrains(mapDataFilePath, prevRoom, direction);

	area = new BoundingBox(position, size, 0.0f, Color(0, 1, 1, 0.25f));
	area->Update(position, size, 0.0f);

	prevRoom->SetLinkedRoom(direction, this);
	if (direction == Direction::RIGHT)	this->SetLinkedRoom(Direction::LEFT, prevRoom);
	else if (direction == Direction::LEFT) this->SetLinkedRoom(Direction::RIGHT, prevRoom);
}

Room::Room(Type type, std::wstring mapDataFilePath, Room* prevRoom, Direction direction)
	: type(type)
{

	initTerrains(mapDataFilePath, prevRoom, direction);
	//moveTerrainsToRoomPosition(prevRoom, direction);

	area = new BoundingBox(position, size, 0.0f, getAreaColor(type));
	area->Update(position, size, 0.0f);

	prevRoom->SetLinkedRoom(direction, this);
	if (direction == Direction::RIGHT)	this->SetLinkedRoom(Direction::LEFT, prevRoom);
	else if (direction == Direction::LEFT) this->SetLinkedRoom(Direction::RIGHT, prevRoom);
}


Room::Room(Type type)
	: type(type), position(Vector3(0,0,0))
{
	mapDataFilePath = MapDataPath + L"passage_1to1.csv";

	initTerrains(mapDataFilePath);

	area = new BoundingBox(position, size, 0.0f, getAreaColor(type));
	area->Update(position, size, 0.0f);
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
	for (auto trn : trnBackground) trn->Update();
	for (auto trn : trnMiddleground) trn->Update();
	for (auto trn : trnForeground) trn->Update();
}
void Room::Render()
{
	area->Render();
	for (auto trn : trnBackground) trn->Render();
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
	}
}

Color Room::getAreaColor(Type type)
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

	{
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

		// 맵 데이터 불러오기
		{
			UINT count = 0;

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

					Vector3 prevRoomPosition = Values::ZeroVec3;
					Vector3 prevRoomSize = Values::ZeroVec3;

					// 이전 방에 붙이는 중이라면 포지션을 그에 따라 수정
					if (prevRoom != nullptr && direction != Direction::NONE)
					{
						prevRoomPosition = prevRoom->GetPosition();
						prevRoomSize = prevRoom->GetSize();

						switch (direction)
						{
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

				tilePositionY = std::stoi(tiles[0]);

				for (UINT i = 1; i < tiles.size(); i++)
				{
					// 앞에 Y구분 열이 있으니까
					tilePositionX = i - 1;

					Terrain::Type trnType;
					std::vector<Terrain*>* targetLayer = nullptr;

					switch (std::stoi(tiles[i]))
					{
					case 0:
						trnType = Terrain::Type::NONE;
						targetLayer = nullptr;
						break;

					case 1:
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

						if (tilePositionX == 0)
						{
							if (tiles[i + 1] != "0") trnType = Terrain::Type::FH_MID;
							else trnType = Terrain::Type::FH_EDGE_R;
						}
						else if (tilePositionX == totalTileX - 1)
						{
							if (tiles[i - 1] != "0") trnType = Terrain::Type::FH_MID;
							else trnType = Terrain::Type::FH_EDGE_L;
						}
						else
						{
							if (tiles[i - 1] != "0" && tiles[i + 1] != "0") trnType = Terrain::Type::FH_MID;
							else if (tiles[i - 1] != "0" && tiles[i + 1] == "0") trnType = Terrain::Type::FH_EDGE_R;
							else if (tiles[i - 1] == "0" && tiles[i + 1] != "0") trnType = Terrain::Type::FH_EDGE_L;
						}

						targetLayer = &trnBackground;
						break;

					case 2:
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
						if (tilePositionX == 0) trnType = Terrain::Type::FH_MID_L_WP;
						else if (tilePositionX == totalTileX - 1) trnType = Terrain::Type::FH_MID_R_WP;
						else
						{
							if (tiles[i - 1] != "2" && tiles[i + 1] != "2") trnType = Terrain::Type::FH_MID_L_WP;
							else if (tiles[i - 1] != "2" && tiles[i + 1] == "2") trnType = Terrain::Type::FH_MID_L_WP;
							else if (tiles[i - 1] == "2" && tiles[i + 1] != "2") trnType = Terrain::Type::FH_MID_R_WP;
						}
						targetLayer = &trnBackground;
						break;
					case 3:
						trnType = Terrain::Type::STAIR_UP;
						targetLayer = &trnMiddleground;
						break;
					case 4:
						trnType = Terrain::Type::STAIR_DOWN;
						targetLayer = &trnMiddleground;
						break;
					default:
						trnType = Terrain::Type::NONE;
						targetLayer = nullptr;
						break;
					}

					if (targetLayer != nullptr && trnType != Terrain::Type::NONE)
						targetLayer->push_back(new Terrain(tilePosToVector3(trnType, tilePositionX, tilePositionY) + position, trnType));

					count++;
				}
				tiles.clear();
			}

				std::cout << "Enter floor left : " << enterFloorL << std::endl
					<< "Enter floor right : " << enterFloorR << std::endl;

		}
	}
	fs.close();
	return true;
}

void Room::moveTerrainsToRoomPosition(Room* prevRoom, Direction direction)
{
	Vector3 prevRoomPosition = prevRoom->GetPosition();
	Vector3 prevRoomSize = prevRoom->GetSize();

	switch (direction)
	{
	case Direction::UP:
		break;

	case Direction::DOWN:
		break;

	case Direction::LEFT:
	  position.x = prevRoomPosition.x - prevRoomSize.x / 2 - size.x / 2;
		position.y = 0;
		position.z = 0;
		break;

	case Direction::RIGHT:
		position.x = prevRoomPosition.x + prevRoomSize.x / 2 + size.x / 2;
		position.y = 0;
		position.z = 0;
		break;

	default:
		break;
	}
	for (auto trn : trnBackground) trn->Move(position);
	for (auto trn : trnMiddleground) trn->Move(position);
	for (auto trn : trnForeground) trn->Move(position);
}

Vector3 Room::tilePosToVector3(Terrain::Type trnType, UINT tilePositionX, UINT tilePositionY)
{
	Vector3 returnPosition;
	if (trnType == Terrain::Type::STAIR_DOWN) 
	{
		returnPosition.x = ((float)tilePositionX * TILESIZE) - (TILESIZE * 2);
		returnPosition.y = ((float)tilePositionY * TILESIZE) + TILESIZE;
	}

	else if (trnType == Terrain::Type::STAIR_UP) 
	{
		returnPosition.x = ((float)tilePositionX * TILESIZE) + (TILESIZE * 3);
		returnPosition.y = ((float)tilePositionY * TILESIZE) + (TILESIZE);
	}

	else
	{
		returnPosition.x = ((float)tilePositionX * TILESIZE) + (TILESIZE / 2);
		returnPosition.y = ((float)tilePositionY * TILESIZE) + (TILESIZE / 2);
	}

	returnPosition.x -= size.x / 2;
	returnPosition.y -= size.y / 2;
	returnPosition.z = 0;

	return returnPosition;
}