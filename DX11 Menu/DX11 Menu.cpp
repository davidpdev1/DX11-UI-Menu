// DX11 Menu.cpp : Définit le point d'entrée de l'application.
//

#include "stdafx.h"
#include "DX11 Menu.h"


struct FColor {
	float r, g, b, a;
	FColor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
	// Return a pointer to this struct
	float *Get() {
		return (float*)this;
	}
};


class Graphics {
public:
	static const int m_screenWidth = 1920;
	static const int m_screenHeight = 1080;
private:
	ID3D11Device *m_pDevice;
	IDXGISwapChain *m_pSwapchain;
	ID3D11RenderTargetView *m_pRenderTargetView;
	ID3D11DeviceContext *m_pDeviceContext;
	ID3D11RenderTargetView *m_pBackBuffer;
	Base m_menuBase;
public:
	void RenderFrame() {
		m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer, FColor(0.0f, 0.2f, 0.4f, 1.0f).Get());
		m_menuBase.Render();
		m_pSwapchain->Present(0, 0);
	}

	bool Initialize(HWND d3d) {

		DXGI_SWAP_CHAIN_DESC desc = { 0 };

		desc.BufferCount = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow = d3d;
		desc.SampleDesc.Count = 4;
		desc.Windowed = true;

		HRESULT res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &desc, &m_pSwapchain, &m_pDevice, NULL, &m_pDeviceContext);
		if (FAILED(res)) {
			MessageBoxA(NULL, "Failed to create device and swapchain", "Error", MB_OK);
			return false;
		}

		ID3D11Texture2D *imgBackBuffer;
		m_pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&imgBackBuffer);

		m_pDevice->CreateRenderTargetView(imgBackBuffer, NULL, &m_pBackBuffer);
		imgBackBuffer->Release();

		m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBuffer, NULL);


		D3D11_VIEWPORT viewport = { 0 };
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = m_screenWidth;
		viewport.Height = m_screenHeight;

		m_pDeviceContext->RSSetViewports(1, &viewport);

		m_menuBase.Initialize(m_pDevice, m_pSwapchain, m_pDeviceContext);
		MenuComponent::SetWindow(d3d);
		return true;
	}

	void Release() {
		m_pSwapchain->Release();
		m_pBackBuffer->Release();
		m_pDevice->Release();
		m_pDeviceContext->Release();
	}


};
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		Input::Get()->ReportKeyDown(1, 1);
		break;
	case WM_RBUTTONDOWN:
		Input::Get()->ReportKeyDown(2, 1);
		break;
	case WM_MBUTTONDOWN:
		Input::Get()->ReportKeyDown(3, 1);
		break;
	case WM_LBUTTONUP:
		Input::Get()->ReportKeyUp(1);
		break;
	case WM_RBUTTONUP:
		Input::Get()->ReportKeyUp(2);
		break;
	case WM_MBUTTONUP:
		Input::Get()->ReportKeyUp(3);
		break;
	case WM_KEYDOWN:
		Input::Get()->ReportKeyDown(static_cast<DWORD>(wParam), *(short*)&lParam);
		break;
	case WM_KEYUP:
		Input::Get()->ReportKeyUp(static_cast<DWORD>(wParam));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	Input::Get()->IsKeyDown('W');
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	HWND hWnd;
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"MainWindow";


	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL,
		L"MainWindow",
		L"Menu Test",
		WS_OVERLAPPEDWINDOW,
		300,
		100,
		Graphics::m_screenWidth,
		Graphics::m_screenHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	MSG msg;

	Graphics g;
	g.Initialize(hWnd);

	while (true) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);


			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		g.RenderFrame();

	}
	return static_cast<int>(msg.wParam);
}


