#include "Framework.h"
#include "Room.h"

Room::Room(Type type, Room* prevRoom)
 : type(type)
{
	for (auto trn : trnBackground) SAFE_DELETE(trn);
	for (auto trn : trnMiddleground) SAFE_DELETE(trn);
	for (auto trn : trnForeground) SAFE_DELETE(trn);

	trnBackground.clear();
	trnMiddleground.clear();
	trnForeground.clear();
}

Room::Room(Type type, std::wstring mapDataFilePath, Room* prevRoom)
	: type(type)
{

}


Room::Room(Type type)
	: type(type)
{
	switch (type)
	{
	case Room::Type::EMPTY:
		break;
	case Room::Type::START:
	{
		mapDataFilePath = MapDataPath + L"test.csv";
	}
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
		break;
	case Room::Type::PASSAGE:
		break;
	default:
		break;
	}

	if (mapDataFilePath != L"")
	{
		std::string str_buf;
		std::fstream fs;

		fs.open(mapDataFilePath, ios::in);
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
				if (count == 0) totalTileY = std::stoi(tiles[0]);
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
						if(targetLayer != nullptr && trnType != Terrain::Type::NONE)
							targetLayer->push_back(new Terrain(tilePosToVector3(trnType, tilePositionX, tilePositionY), trnType));

						count++;
					}
					tiles.clear();
				}
			}
		}
		fs.close();
	}
}

Room::~Room()
{

}

void Room::Update()
{
	for (auto trn : trnBackground) trn->Update();
	for (auto trn : trnMiddleground) trn->Update();
	for (auto trn : trnForeground) trn->Update();
}
void Room::Render()
{
	for (auto trn : trnBackground) trn->Render();
	for (auto trn : trnMiddleground) trn->Render();
}
void Room::ForegroundRender()
{
	for (auto trn : trnForeground) trn->Render();
}

Vector3 Room::tilePosToVector3(Terrain::Type trnType, UINT tilePositionX, UINT tilePositionY)
{
	Vector3 position;
	if (trnType == Terrain::Type::STAIR_DOWN) 
	{
		position.x = (tilePositionX * TILESIZE) - (TILESIZE * 2);
		position.y = (tilePositionY * TILESIZE) + TILESIZE;
		position.z = 0;
	}
	else if (trnType == Terrain::Type::STAIR_UP) 
	{
		position.x = (tilePositionX * TILESIZE) + (TILESIZE * 3);
		position.y = (tilePositionY * TILESIZE) + (TILESIZE);
		position.z = 0;
	}
	else
	{
		position.x = (tilePositionX * TILESIZE) + (TILESIZE / 2);
		position.y = (tilePositionY * TILESIZE) + (TILESIZE / 2);
		position.z = 0;
	}
	return position;
}