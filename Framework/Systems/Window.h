#pragma once

struct DXDesc
{
	wstring AppName;
	HINSTANCE instance;
	HWND handle;
	UINT width; //������ â�� ���� ���� ũ��
	UINT height;
};

class Window
{
public:
	Window(DXDesc desc);
	~Window();

	WPARAM Run(IObject* mainObj); //���ӷ��� �Լ�
private:
	//�Լ�ȣ�� �Ծ�
	//stdcall
	//cdecl
	static LRESULT CALLBACK WndProc //�޼��� ó���Լ�
	(
		HWND handle,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);
	void MainRender();

	static DXDesc desc;
	IObject* mainObj = nullptr;

	double elapsedTime = 0;
	static bool isActive;

	const UINT32 UPDATES_PER_SECOND = 60;
	const double MS_PER_UPDATE = 1.0 / UPDATES_PER_SECOND;
};

