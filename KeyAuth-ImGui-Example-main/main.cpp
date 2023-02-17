#include <Windows.h>
#include "auth.hpp"
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
IDirect3DTexture9* masterlogo;
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "D3dx9")
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "icons.h"
#include "MMSystem.h"
#include <filesystem>
#include<direct.h>
#include "bytes.h"
#include <sys/stat.h>
#include "ImSpinner.h"
#include "effects.h"
#include "VMProtectSDK.h"
#include "lazy.h"
#include "Imports.hpp"
#include "xorstr.hpp"
#include "safe_ptr.hpp"
const char* AllCheats[] = { "None", "file name" };
#include "skCrypt.h"
#include "protectmain.h"
#pragma warning(disable : 4996)
using namespace std;
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
using namespace KeyAuth;

std::string name = XorStr("Damnnation"); // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = XorStr("1JtUQax1gG"); // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = XorStr("16fb6f35bb6b6a4a519a65f84cae3dee6d6e1b472c8678511941f00c3e2bbb02"); // app secret, the blurred text on licenses tab and other tabs
std::string version = XorStr("1.2"); // leave alone unless you've changed version on website
std::string url = "https://keyauth.win/api/1.1/"; // change if you're self-hosting
std::string sslPin = "ssl pin key (optional)"; // don't change unless you intend to pin public certificate key. you can get here in the "Pin SHA256" field https://www.ssllabs.com/ssltest/analyze.html?d=keyauth.win&latest. If you do this you need to be aware of when SSL key expires so you can update it
api KeyAuthApp(name, ownerid, secret, version, url, sslPin);
bool loader_active = true;
bool animate = false;
bool animate1 = false;
bool cursor = true;

static int width = 613;
static int height = 380;

char PassWord[50] = "";
char Licence[50] = "";
char UserName[50] = "";
char RgPassWord[50] = "";
char RgUserName[50] = "";
IDirect3DTexture9* Mainimg;

HWND main_hwnd = nullptr;

LPDIRECT3DDEVICE9        g_pd3dDevice;
D3DPRESENT_PARAMETERS    g_d3dpp;
LPDIRECT3D9              g_pD3D;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool CreateDeviceD3D(HWND hWnd)
{
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;

	// Create the D3DDevice
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
	//g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
		return false;
	return true;
}

void CleanupDeviceD3D()
{
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

bool LoginCheck = false;

int APIENTRY WindownsMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL,"Loaders", NULL };
	RegisterClassEx(&wc);
	main_hwnd = CreateWindow(wc.lpszClassName, "Loaders", WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL);
	if (!CreateDeviceD3D(main_hwnd)) {
		CleanupDeviceD3D();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}
	ShowWindow(main_hwnd, SW_HIDE);
	UpdateWindow(main_hwnd);

        HWND Stealth;
        AllocConsole();
        Stealth = FindWindowA("ConsoleWindowClass", NULL);
        ShowWindow(Stealth, 0);
	
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
	ImFontConfig icons_config;

	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.OversampleH = 3;
	icons_config.OversampleV = 3;

	ImFont* font1 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 14.0f);
	io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 14.0f, &icons_config, icons_ranges);
	D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, Damnnasionimage, sizeof(Damnnasionimage), 300, 300, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &Mainimg);

	constexpr auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b)
	{
		return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
	};

	auto& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;
	style.Colors[ImGuiCol_WindowBg] = ImColor(13, 13, 13);
	style.Colors[ImGuiCol_ChildBg] = ImColor(15, 15, 15);
	style.Colors[ImGuiCol_Border] = ImColor(0, 0, 0);
	style.Colors[ImGuiCol_TextSelectedBg] = ImColor(255, 255, 255, 50);
	style.Colors[ImGuiCol_FrameBg] = ImColor(34, 34, 34);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(51, 52, 54);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(51, 52, 54);
	style.Colors[ImGuiCol_Button] = ImColor(29, 29, 29, 0);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(30, 30, 30, 150);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(23, 23, 23, 0);
	style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);

	ImGui_ImplWin32_Init(main_hwnd);
	ImGui_ImplDX9_Init(g_pd3dDevice);

	DWORD window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar;
	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);
	auto x = float(screen_rect.right - width) / 2.f;
	auto y = float(screen_rect.bottom - height) / 2.f;
	int old_tab = 0;
	int tab_count = 0, tab = 0;
	const char* items[]{ " Fortnite"," Apex"," Valorant" };
	int selecteditem = 0;
	bool InfWindow = false;
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	mkdir("C:\\Damnnation loader");
	mkdir("C:\\Damnnation loader\\configs");
	ifstream config;
	config.open("C:\\Damnnation loader\\configs\\User.config");
	config >> UserName;
	config.close();
	ifstream config1;
	config1.open("C:\\Damnnation loader\\configs\\Pass.config");
	config1 >> PassWord;
	config1.close();
	ifstream config2;
	config2.open("C:\\Damnnation loader\\configs\\Key.config");
	config2 >> Licence;
	config2.close();
	KeyAuthApp.init();
	mainprotect();
	if (KeyAuthApp.checkblack())
	{
		exit(0);
	}
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		{
			const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
			ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);
			ImGui::SetNextWindowSize(ImVec2(width, height));
			ImGui::SetNextWindowBgAlpha(1.0f);
			ImGui::Begin("Loader", &loader_active, ImGuiWindowFlags_NoDecoration);
			{
				auto draw = ImGui::GetForegroundDrawList();
				ImVec2 pos = ImGui::GetWindowPos();
				ImVec2 size = ImGui::GetWindowSize();
				if (tab == 0)
				{

					animate = true;
					static float progress = 0.0f;
					static float progress_dir = 1.0f;
					if (animate)
					{
						progress += progress_dir * 0.19f * ImGui::GetIO().DeltaTime;
					}
					if (animate)
					{
						ImGui::SetNextItemWidth(150);
						ImGui::SetCursorPos({ 210, 84 });
						ImSpinner::SpinnerPulsar("##spinner", 90, 8, col);
					}
					if (progress >= 1.0f)
					{
						tab = 1;
					}

				}
				if (tab == 1)
				{
					draw->AddRectFilled({ pos.x + 2,pos.y + 3 }, { pos.x + 612, pos.y + 33 }, ImColor(12, 12, 12, 200), 0, 0);
					draw->AddRect({ pos.x + 3,pos.y + 3 }, { pos.x + 612, pos.y + 27 }, ImColor(3, 3, 3, 235), 0, 0, 1.3f);
					draw->AddRect({ pos.x + 2,pos.y + 2 }, { pos.x + 612, pos.y + 28 }, ImColor(20, 20, 20, 255), 0, 0, .8f);
					ImGui::SetCursorPos(ImVec2(220, 10));
					ImGui::Image(Mainimg, (ImVec2(150, 125)));
					ImGui::SetCursorPos(ImVec2(135, 140));
					ImGui::BeginChild("##loginchild1", ImVec2(350, 220), true, ImGuiWindowFlags_NoResize);
					ImGui::SetCursorPos({ 74, 10 });
					ImGui::SetNextItemWidth(160);
					ImGui::InputText("Username##usernamelogin", UserName, IM_ARRAYSIZE(UserName));
					ImGui::SetCursorPos({ 74, 40 });
					ImGui::SetNextItemWidth(160);
					ImGui::InputText("Password##passwordlogin", PassWord, IM_ARRAYSIZE(PassWord));
					ImGui::SetCursorPos({ 74, 70 });
					ImGui::SetNextItemWidth(160);
					ImGui::InputText("Key##Keylogin", Licence, IM_ARRAYSIZE(Licence));
					ImGui::SetCursorPos({ 135, 180 });
					if (ImGui::Button("Login##Log", ImVec2(60, 30)))
					{
						ofstream config;
						ofstream config1;
						ofstream config2;
						config.open("C:\\Damnnation loader\\configs\\User.config");
						config << UserName;
						config.close();

						config1.open("C:\\Damnnation loader\\configs\\Pass.config");
						config1 << PassWord;
						config1.close();

						config2.open("C:\\Damnnation loader\\configs\\Key.config");
						config2 << Licence;
						config2.close();
						KeyAuthApp.regstr(UserName, PassWord, Licence);
						KeyAuthApp.login(UserName, Licence);
						if (!KeyAuthApp.data.success)
						{
							MessageBox(NULL, ("Regster Unsuccessful!"), ("Debugger"), MB_OK);
						}
						else
							tab = 2;

						if (KeyAuthApp.data.success)
						{
							tab = 2;
						}
						else
							MessageBox(NULL, ("Regster Unsuccessful!"), ("Debugger"), MB_OK);
					}
				}
				if (tab == 2)
				{
					draw->AddRectFilled({ pos.x + 2,pos.y + 3 }, { pos.x + 612, pos.y + 33 }, ImColor(12, 12, 12, 200), 0, 0);
					draw->AddRect({ pos.x + 3,pos.y + 3 }, { pos.x + 612, pos.y + 27 }, ImColor(3, 3, 3, 235), 0, 0, 1.3f);
					draw->AddRect({ pos.x + 2,pos.y + 2 }, { pos.x + 612, pos.y + 28 }, ImColor(20, 20, 20, 255), 0, 0, .8f);
					draw->AddText({ pos.x + 9, pos.y + 7 }, ImColor(165, 29, 207), "Damnnation.gay");

					draw->AddRectFilled({ pos.x + 5,pos.y + 30 }, { pos.x + 110, pos.y + 447 }, ImColor(12, 12, 12, 255), 0, 0);
					draw->AddRect({ pos.x + 5,pos.y + 30 }, { pos.x + 110, pos.y + 447 }, ImColor(3, 3, 3, 235), 0, 0, 1.3f);
					draw->AddRect({ pos.x + 4,pos.y + 29 }, { pos.x + 111, pos.y + 448 }, ImColor(20, 20, 20, 255), 0, 0, .8f);
					draw->AddText({ pos.x + 33 ,pos.y + 36 }, ImColor(255, 255, 255), "RustLite");
					draw->AddText({ pos.x + 33 ,pos.y + 70 }, ImColor(255, 255, 255), "RustRage");
					draw->AddText({ pos.x + 33 ,pos.y + 100 }, ImColor(255, 255, 255), "Valorant");
					draw->AddText({ pos.x + 33 ,pos.y + 130 }, ImColor(255, 255, 255), "Spoofer");
				}
			}
			ImGui::End();
		}
		ImGui::EndFrame();

		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		if (g_pd3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			g_pd3dDevice->EndScene();
		}
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
		HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
		if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			ResetDevice();
		}
		if (!loader_active) {
			msg.message = WM_QUIT;
		}
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	CleanupDeviceD3D();
	//	DestroyWindow(main_hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
	//	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;
	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			ResetDevice();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	WindownsMain(0, 0, 0, 0);
}

std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}
