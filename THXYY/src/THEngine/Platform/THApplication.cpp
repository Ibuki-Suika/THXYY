#include "THApplication.h"
#include "../UI/THEventSystem.h"

using namespace THEngine;

Application* Application::instance = nullptr;

Application::Application()
{
	ASSERT(instance == nullptr);

	d3d = NULL;
	device = NULL;

	needQuit = false;

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&projection);
	D3DXMatrixIdentity(&view);

	instance = this;
}

Application::~Application()
{
	UnregisterClass(TEXT("THGameEngine"), hInstance);

	TH_SAFE_RELEASE(d3d);
	TH_SAFE_RELEASE(device);
}

Application* Application::GetInstance()
{
	return instance;
}

int Application::Init(int width, int height, bool fullScreen, String title, int bigIcon, int smallIcon)
{
	auto exceptionManager = ExceptionManager::GetInstance();

	int status;

	this->width = width;
	this->height = height;
	this->fullScreen = fullScreen;
	this->title = title;
	this->bigIcon = bigIcon;
	this->smallIcon = smallIcon;

	hInstance = (HINSTANCE)GetModuleHandle(NULL);

	status = RegisterGameClass();
	if (TH_FAILED(status))
	{
		exceptionManager->PushException(new Exception("ע�ᴰ����ʧ�ܡ�"));
		return status;
	}

	status = CreateGameWindow();
	if (TH_FAILED(status))
	{
		exceptionManager->PushException(new Exception("��������ʧ�ܡ�"));
		return status;
	}

	status = InitDeviceContext();
	if (TH_FAILED(status))
	{
		auto exception = exceptionManager->GetException();
		exceptionManager->PushException(new Exception((String)"��ʼ��Direct3Dʧ�ܡ�ԭ���ǣ�\n" + exception->GetInfo()));
		return status;
	}

	return TH_SUCCESS;
}

int Application::RegisterGameClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(bigIcon));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("THGameEngine");
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(smallIcon));

	if (RegisterClassEx(&wcex) == 0)
	{
		return -1;
	}
	return TH_SUCCESS;
}

int Application::CreateGameWindow()
{
	UINT windowStyle = WS_OVERLAPPEDWINDOW;
	windowStyle &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);            //�̶����ڴ�С

	hWnd = CreateWindow(TEXT("THGameEngine"), title.GetBuffer(), windowStyle,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return -1;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//�ƶ���������Ļ���벢���ÿͻ�����С
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	RECT windowRect;
	GetWindowRect(hWnd, &windowRect);

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);

	MoveWindow(hWnd, (screen_width - width) / 2, (screen_height - height) / 2, width + windowRect.right - windowRect.left - clientRect.right - clientRect.left,
		height + windowRect.bottom - windowRect.top - clientRect.bottom - clientRect.top, TRUE);

	return TH_SUCCESS;
}

int Application::InitDeviceContext()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	THLog((String)"��Ϸ��ʼ��" + time.wYear + "��" + time.wMonth + "��" + time.wDay + "��"
		+ time.wHour + ":" + time.wMinute + ":" + time.wSecond + "��");

	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (TH_FAILED(CreateDevice()))
	{
		return -1;
	}

	device->SetRenderState(D3DRS_ZENABLE, true);
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	device->SetRenderState(D3DRS_LIGHTING, false);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_GAUSSIANQUAD);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_GAUSSIANQUAD);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_GAUSSIANQUAD);

	device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	return TH_SUCCESS;
}

int Application::CreateDevice()
{
	HRESULT hr;

	//����֡��
	int refresh;
	if (!fullScreen)
	{
		refresh = 0;
	}
	else
	{
		refresh = 60;
		ShowCursor(FALSE);
	}
	
	D3DDEVTYPE deviceType;
	int vertexProcessingType;

	//��ȡ�豸����
	GetDeviceInfo(&deviceType, &vertexProcessingType);

	//��ȡ���ز�������
	D3DMULTISAMPLE_TYPE multiSampleType;
	DWORD qualityLevel;

	GetMultiSampleType(deviceType, &multiSampleType, &qualityLevel);

	//����豸����
	if (TH_FAILED(CheckDeviceCaps(deviceType)))
	{
		return -1;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = multiSampleType;
	d3dpp.MultiSampleQuality = qualityLevel;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = !fullScreen;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = refresh;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, deviceType,
		hWnd, vertexProcessingType, &d3dpp, &device);

	if (FAILED(hr))
	{
		return -1;
	}

	THLog("Direct3D�ɹ���ʼ����");
	return TH_SUCCESS;
}

void Application::GetDeviceInfo(D3DDEVTYPE* deviceType, int* vertexProcessingType)
{
	HRESULT hr;
	hr = d3d->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_UNKNOWN, D3DFMT_UNKNOWN, !fullScreen);
	if (FAILED(hr))
	{
		*deviceType = D3DDEVTYPE_HAL;
		THLog("ʹ��Ӳ����Ⱦģʽ��HAL����");
	}
	else
	{
		*deviceType = D3DDEVTYPE_REF;
		THLog("ʹ�������Ⱦģʽ��REF����");
	}

	D3DCAPS9 d3dcaps;
	ZeroMemory(&d3dcaps, sizeof(d3dcaps));
	d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, *deviceType, &d3dcaps);

	if (d3dcaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		*vertexProcessingType = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		THLog("ʹ��Ӳ�������㡣");
	}
	else
	{
		*vertexProcessingType = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		THLog("ʹ����������㡣");
	}
}

int Application::CheckDeviceCaps(D3DDEVTYPE deviceType)
{
	auto exceptionManager = ExceptionManager::GetInstance();

	D3DCAPS9 d3dcaps;
	ZeroMemory(&d3dcaps, sizeof(d3dcaps));
	d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &d3dcaps);

	//���shader�汾
	int mainVSVersion = (d3dcaps.VertexShaderVersion & 0x0000ff00) >> 8;
	int subVSVersion = d3dcaps.VertexShaderVersion & 0x000000ff;
	int mainPSVersion = (d3dcaps.PixelShaderVersion & 0x0000ff00) >> 8;
	int subPSVersion = d3dcaps.PixelShaderVersion & 0x000000ff;

	if (mainVSVersion < 2)
	{
		exceptionManager->PushException(new Exception((String)"��ǰ�Կ�֧�ֵĶ�����ɫ���汾���͡�\n"
			"��ǰ֧�ְ汾��" + mainVSVersion + "." + subVSVersion
			+ "   �����Ҫ�汾��2.0"));
		return -1;
	}

	if (mainPSVersion < 2)
	{
		exceptionManager->PushException(new Exception((String)"��ǰ�Կ�֧�ֵ�������ɫ���汾���͡�\n"
			"��ǰ֧�ְ汾��" + mainPSVersion + "." + subPSVersion
			+ "   �����Ҫ�汾��2.0"));
		return -1;
	}

	THLog("**********************�豸��Ϣ**********************");
	THLog((String)"������ɫ���汾��" + mainVSVersion + "." + subVSVersion);
	THLog((String)"������ɫ���汾��" + mainPSVersion + "." + subPSVersion);
	THLog("****************************************************");

	return TH_SUCCESS;
}

void Application::GetMultiSampleType(D3DDEVTYPE deviceType, 
	D3DMULTISAMPLE_TYPE* multiSampleType,
	DWORD* qualityLevel)
{
	HRESULT hr;

	const D3DMULTISAMPLE_TYPE multiSampleTypes[] = {
		D3DMULTISAMPLE_NONMASKABLE,
		D3DMULTISAMPLE_NONE,
		D3DMULTISAMPLE_2_SAMPLES,
		D3DMULTISAMPLE_3_SAMPLES,
		D3DMULTISAMPLE_4_SAMPLES,
		D3DMULTISAMPLE_5_SAMPLES,
		D3DMULTISAMPLE_6_SAMPLES,
		D3DMULTISAMPLE_7_SAMPLES,
		D3DMULTISAMPLE_8_SAMPLES,
		D3DMULTISAMPLE_9_SAMPLES,
		D3DMULTISAMPLE_10_SAMPLES,
		D3DMULTISAMPLE_11_SAMPLES,
		D3DMULTISAMPLE_12_SAMPLES,
		D3DMULTISAMPLE_13_SAMPLES,
		D3DMULTISAMPLE_14_SAMPLES,
		D3DMULTISAMPLE_15_SAMPLES,
		D3DMULTISAMPLE_16_SAMPLES
	};

	*multiSampleType = D3DMULTISAMPLE_4_SAMPLES;
	DWORD qualityLevels;

	for (int i = *multiSampleType; i > 0; i--)
	{
		hr = d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, deviceType, D3DFMT_A8R8G8B8,
			!fullScreen, multiSampleTypes[i], &qualityLevels);
		if (!FAILED(hr))
		{
			*multiSampleType = multiSampleTypes[i];
			*multiSampleType = D3DMULTISAMPLE_NONE;
			if (*multiSampleType == D3DMULTISAMPLE_NONE)
			{
				*qualityLevel = 0;
				THLog("��ʹ�ö��ز�����");
			}
			else
			{
				if (qualityLevels == NULL)
				{
					*qualityLevel = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
				}
				else
				{
					*qualityLevel = qualityLevels - 1;
				}
				THLog((String)"ʹ�ö��ز�����������Ϊ" + *multiSampleType + "�������ȼ�" + *qualityLevel + "��");
			}
			return;
		}

	}
}

void Application::DealWithMessage()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			needQuit = true;
			returnCode = (int)msg.wParam;
		}
	}
}

void Application::SetOrtho(float left, float bottom, float width, float height, float znear, float zfar)
{
	D3DXMATRIX projection;
	D3DXMatrixOrthoOffCenterLH(&projection, left, left + width, bottom, bottom + height, znear, zfar);
	SetProjectionTransform(&projection);
}

void Application::SetViewport(int left, int top, int width, int height)
{
	D3DVIEWPORT9 viewport;
	viewport.X = left;
	viewport.Y = top;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinZ = 0;
	viewport.MaxZ = 1;

	device->SetViewport(&viewport);
}

void Application::OnKeyDown(int key)
{
	if (key == VK_HOME)
	{
		PrintScreen();
	}
	EventSystem::GetInstance()->OnKeyDown(key);
}

void Application::PrintScreen()
{
	IDirect3DSurface9 *surface;
	device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surface);
	
	String dir = "snapshot";
	String path;

	WIN32_FIND_DATAW wfd;
	HANDLE handle = FindFirstFile(dir.GetBuffer(), &wfd);
	if (handle == INVALID_HANDLE_VALUE || ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0))
	{
		//snapshotĿ¼������,����֮
		CreateDirectory(dir.GetBuffer(), NULL);
	}
	int i = 1;
	while (true)
	{
		path = dir + "\\" + i + ".jpg";
		handle = FindFirstFile(path.GetBuffer(), &wfd);
		if (handle == INVALID_HANDLE_VALUE )
		{
			break;
		}
		i++;
	}

	D3DXSaveSurfaceToFile(path.GetBuffer(), D3DXIFF_JPG, surface, NULL, NULL);
	surface->Release();
}

LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		Application::GetInstance()->OnKeyDown(wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}