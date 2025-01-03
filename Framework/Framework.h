#pragma once

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

//�̸� �����ϵ� ���.
//pch pre compiled header

#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <unordered_map>
#include <map>
#include <array>
#include <assert.h>
#include <fstream>

using namespace std;

//DirectX
#include <DirectXTex/DirectXTex.h>
#pragma comment(lib, "DirectXTex/DirectXTex.lib")

#include <d3dcompiler.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")

//////////////////////////////////////////
//ImGui

#include "ImGui/imgui.h"
#include "ImGui/imgui_stdlib.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#pragma comment(lib, "ImGui/ImGui.lib")

//////////////////////////////////////////
// NFD

#include "NFD/include/nfd.h"
#pragma comment(lib, "NFD/nfd_d.lib")

//////////////////////////////////////////

enum class AnchorPoint
{
	LEFT_TOP, MID_TOP, RIGHT_TOP,
	LEFT_MID, CENTER, RIGHT_MID,
	LEFT_BOT, MID_BOT, RIGHT_BOT
};

enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };

#include "Interfaces/IObject.h"

#include "Utilities/SingletonBase.h"

#include "Systems/Graphics.h"
#include "Systems/Keyboard.h"
#include "Systems/Mouse.h"
#include "Systems/Time.h"

#include "Utilities/Gui.h"

typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR2 Vector2;
typedef D3DXMATRIX  Matrix;
typedef D3DXCOLOR   Color;
typedef UINT		uint;

#undef random
#define random() (rand() / (double)RAND_MAX + 1)

#define DEVICE Graphics::Get()->GetDevice()
#define DC     Graphics::Get()->GetDC()

#define CHECK(p) assert(SUCCEEDED(p))
#define ZERO_MEMORY(p) ZeroMemory(&p, sizeof(p))

#define SAFE_DELETE(p)		 { if(p) { delete(p);	   (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[](p);	   (p) = nullptr; } }
#define SAFE_RELEASE(p)		 { if(p) { (p)->Release(); (p) = nullptr; } }

#include "Renders/Resources/VertexTypes.h"
#include "Renders/Resources/ShaderBuffer.h"
#include "Renders/Resources/GlobalBuffer.h"
#include "Renders/Resources/Texture2D.h"

#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/IndexBuffer.h"
#include "Renders/IA/InputLayout.h"
#include "Renders/States.h"

#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"

#include "Utilities/DirectHelper.h"
#include "Utilities/BoundingBox.h"
#include "Utilities/String.h"
#include "Utilities/Path.h"

#include "Utilities/Collision/Collision.h"
#include "Utilities/ObjectGraphic/ObjectGraphic.h"
#include "Objects/GameObject.h"
#include "Game/Level/Level.h"

#include "Systems/Camera.h"

#define WinMaxWidth 1280
#define WinMaxHeight 720

#define TILESIZE 64

// position = (mousePos / TILESIZE) * TILESIZE + TILESIZE / 2;

const wstring ShaderPath = L"../_Shaders/";
const wstring TexturePath = L"../_Resources/_Textures/";
const wstring TilePath = L"../_Resources/_TileData/";
const wstring MapDataPath = L"../_Resources/_MapData/";

extern HWND handle;
