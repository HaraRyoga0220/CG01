#include<Windows.h>
#include<cstdint>
#include<string>
#include<format>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

//void Log(const std::string& message) {
//	OutputDebugStringA(message.c_str());
//}
std::wstring ConvertString(const std::string& str);

std::string ConvertString(const std::wstring& str);



LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg,
	WPARAM wparam, LPARAM lparam)
{
	switch (msg) {

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	OutputDebugStringA("Hello,DirectX!\n");
	
	WNDCLASS wc{};
	
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = L"CG2WindowClass";
	wc.hInstance = GetModuleHandle(nullptr);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	RegisterClass(&wc);

	

const int32_t kClientWidth = 1200;
const int32_t kClientHeght = 720;


RECT wrc = { 0,0,kClientWidth,kClientHeght };

AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

HWND hwnd = CreateWindow(
		wc.lpszClassName,
		L"CG2",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr
	);
ShowWindow(hwnd, SW_SHOW);


IDXGIFactory7* dxgiFactory = nullptr;

HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));

assert(SUCCEEDED(hr));

IDXGIAdapter4* useAdapter = nullptr;

for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i,
	DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&useAdapter)) !=
	DXGI_ERROR_NOT_FOUND; ++i) {

	DXGI_ADAPTER_DESC3 adapterDesc{};
	hr = useAdapter->GetDesc3(&adapterDesc);
	assert(SUCCEEDED(hr));

	if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
		Log(std::format(L"Use Adapater:{}\n", adapterDesc.Description));
		break;
	}
	useAdapter = nullptr;
}
assert(useAdapter != nullptr);


MSG msg{};
	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

		}
	}
		return 0;
}


