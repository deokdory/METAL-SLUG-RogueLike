#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"

#include "Game/Game.h"

void Program::Init()
{
  States::Create();
	// Create Buffer
  {
    // view, projection 버퍼 선언
    vpb = new VPBuffer;

    // view 행렬 ( LH -> Left Handed )
    D3DXMatrixLookAtLH(&view, &Vector3(0, 0, 0),  // 카메라 위치
                       &Vector3(0, 0, 100),  // 카메라가 바라보는 방향
                       &Vector3(0, 1, 0)   // 카메라 위쪽 방향
    );

		// projection 행렬

    D3DXMatrixOrthoOffCenterLH(&proj,
                               0.0f,                 // 왼쪽 면의 위치
                               (float)WinMaxWidth,   // 오른쪽 면의 위치
                               0.0f,                 // 아래쪽 면의 위치
                               (float)WinMaxHeight,  // 위쪽 면의 위치
                               0.f,                  
                               1.f                   
    );

		vpb->SetView(view);
    vpb->SetProj(proj);
  }
  Push(new Game);
}

void Program::Destroy()
{
  SAFE_DELETE(vpb);

	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
}

void Program::Update()
{
	for (IObject* obj : objs)
		obj->Update();
}

void Program::Render()
{
  vpb->SetVSBuffer(1);

	for (IObject* obj : objs)
		obj->Render();
}

void Program::PostRender()
{
	for (IObject* obj : objs)
		obj->PostRender();
}

void Program::GUI()
{
	for (IObject* obj : objs)
	{
		obj->GUI();
	}
}

void Program::Push(IObject* obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(program);

	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;

}
