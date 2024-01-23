#include "gui.h"


#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"

#include <iostream>

#include <string>
#include <chrono>
#include <fstream>

#include "TextEditor.h"

using namespace std::chrono;
using namespace std;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

long __stdcall WindowProcess(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter))
		return true;

	switch (message)
	{
	case WM_SIZE: {
		if (gui::device && wideParameter != SIZE_MINIMIZED)
		{
			gui::presentParameters.BackBufferWidth = LOWORD(longParameter);
			gui::presentParameters.BackBufferHeight = HIWORD(longParameter);
			gui::ResetDevice();
		}
	}return 0;

	case WM_SYSCOMMAND: {
		if ((wideParameter & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
	}break;

	case WM_DESTROY: {
		PostQuitMessage(0);
	}return 0;

	case WM_LBUTTONDOWN: {
		gui::position = MAKEPOINTS(longParameter); // set click points
	}return 0;

	case WM_MOUSEMOVE: {
		if (wideParameter == MK_LBUTTON)
		{
			const auto points = MAKEPOINTS(longParameter);
			auto rect = ::RECT{ };

			GetWindowRect(gui::window, &rect);

			rect.left += points.x - gui::position.x;
			rect.top += points.y - gui::position.y;

			if (gui::position.x >= 0 &&
				gui::position.x <= gui::WIDTH &&
				gui::position.y >= 0 && gui::position.y <= 19)
				SetWindowPos(
					gui::window,
					HWND_TOPMOST,
					rect.left,
					rect.top,
					0, 0,
					SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
				);
		}

	}return 0;

	}

	return DefWindowProc(window, message, wideParameter, longParameter);
}

void gui::CreateHWindow(const char* windowName) noexcept
{
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_CLASSDC;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA(0);
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = "class001";
	windowClass.hIconSm = 0;

	RegisterClassEx(&windowClass);

	window = CreateWindowEx(
		0,
		"class001",
		windowName,
		WS_POPUP,
		100,
		100,
		WIDTH,
		HEIGHT,
		0,
		0,
		windowClass.hInstance,
		0
	);

	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
}

void gui::DestroyHWindow() noexcept
{
	DestroyWindow(window);
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool gui::CreateDevice() noexcept
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d)
		return false;

	ZeroMemory(&presentParameters, sizeof(presentParameters));

	presentParameters.Windowed = TRUE;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	presentParameters.EnableAutoDepthStencil = TRUE;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentParameters,
		&device) < 0)
		return false;

	return true;
}

void gui::ResetDevice() noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	const auto result = device->Reset(&presentParameters);

	if (result == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}

void gui::DestroyDevice() noexcept
{
	if (device)
	{
		device->Release();
		device = nullptr;
	}

	if (d3d)
	{
		d3d->Release();
		d3d = nullptr;
	}
}

void gui::CreateImGui() noexcept
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 16.5f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	io.IniFilename = NULL;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);
}

void gui::DestroyImGui() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void gui::BeginRender() noexcept
{
	MSG message;
	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

		if (message.message == WM_QUIT)
		{
			isRunning = !isRunning;
			return;
		}
	}

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void gui::EndRender() noexcept
{
	ImGui::EndFrame();

	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	if (device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		device->EndScene();
	}

	const auto result = device->Present(0, 0, 0, 0);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		ResetDevice();
}

bool actions = true;
bool triggers = false;
bool links = false;

int lang = 0; // 0 - RUS , 1 - ENG
std::string a = "Test";

void gui::Render(string editor) noexcept
{
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	ImGui::Begin(
		"The Globals Editor v1.0 by Mr_Kliff and king174rus",
		&isRunning,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove
	);

	ImGui::ShowDemoWindow();

	ImGui::Text("                                                                            THE GLOBALS EDITOR                  ");
	ImGui::Text("");
	/*
	static const char* fileToEdit = "globals-editor/main.cpp";
	if (ImGui::Button("Show File"))
	{
		std::ifstream t(fileToEdit);
		std::cout << t.good();

		if (t.good())
		{
			std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

			a = str;
			std::cout << str;
			std::cout << "fff";
		}
	}

	const char* editor_ptr = a.c_str();
	ImGui::Text((const char*)editor_ptr);
	*/

	if (ImGui::Button(lang ? "Actions" : (const char*)u8"Активности"))
	{
		actions = true;
		triggers = false;
		links = false;
	}

	ImGui::SameLine();

	if (ImGui::Button(lang ? "Triggers" : (const char*)u8"Тригеры"))
	{
		actions = false;
		triggers = true;
		links = false;
	}

	ImGui::SameLine();

	if (ImGui::Button(lang ? "Links" : (const char*)u8"Ссылки"))
	{
		actions = false;
		triggers = false;
		links = true;
	}

	ImGui::Text("");
	ImGui::Text("");
	ImGui::Text("");

	if (actions)
	{
		const char* ActivityTypes[] = { "test activity" };
		static int ActivityType = 0;
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.24f);
		ImGui::Combo(lang ? "Select Action type" : (const char*)u8"Выбрать вид Активности", &ActivityType, ActivityTypes, IM_ARRAYSIZE(ActivityTypes));

		if (ImGui::Button(lang ? "Add Action" : (const char*)u8"Добавить активность"))
		{

		}
		ImGui::Text("");

		const char* ActionNames[] = { "action name" };
		static int ActivityName = 0;

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.24f);
		ImGui::Combo(lang ? "Select Action" : (const char*)u8"Выбрать Активность", &ActivityName, ActionNames, IM_ARRAYSIZE(ActionNames));
		if (ImGui::Button(lang ? "Edit Action" : (const char*)u8"Изменить активность"))
		{

		}

	}

	if (triggers)
	{
		const char* TriggerTypes[] = { "test Trigger" };
		static int TriggerType = 0;

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.24f);
		ImGui::Combo(lang ? "Select Trigger type" : (const char*)u8"Выбрать вид триггера", &TriggerType, TriggerTypes, IM_ARRAYSIZE(TriggerTypes));

		if (ImGui::Button(lang ? "Add Trigger" : (const char*)u8"Добавить триггер"))
		{

		}
		ImGui::Text("");

		const char* TriggerNames[] = { "Trigger name" };
		static int TriggerName = 0;

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.24f);
		ImGui::Combo(lang ? "Select Trigger" : (const char*)u8"Выбрать Тригер", &TriggerName, TriggerNames, IM_ARRAYSIZE(TriggerNames));
		if (ImGui::Button(lang ? "Edit Trigger" : (const char*)u8"Изменить тригер"))
		{

		}

	}

	if (links)
	{

		if (ImGui::Button(lang ? "Add Link" : (const char*)u8"Добавить ссылку"))
		{

		}
		ImGui::Text("");

		const char* LinkNames[] = { "action name" };
		static int LinkName = 0;

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.24f);
		ImGui::Combo(lang ? "Select Link" : (const char*)u8"Выбрать ссылку", &LinkName, LinkNames, IM_ARRAYSIZE(LinkNames));
		if (ImGui::Button(lang ? "Edit Link" : (const char*)u8"Изменить ссылку"))
		{

		}

	}


	ImGui::Text("");
	ImGui::Text("");
	ImGui::Text("");
	ImGui::Text("");
	ImGui::Text("");
	ImGui::Text("");

	if (ImGui::Button(!lang ? "Change Language" : (const char*)u8"Поменять язык")) lang = !lang;

	ImGui::Text(lang ? "Our links" : (const char*)u8"Наши ссылки");
	ImGui::Separator();

	if (ImGui::Button("king174rus")) {
		ShellExecute(NULL, "open", "https://www.youtube.com/c/@king174rus", 0, 0, SW_SHOWNORMAL);
	}
	ImGui::SameLine(); ImGui::Text(" "); ImGui::SameLine();
	if (ImGui::Button("Mr_Kliff")) {
		ShellExecute(NULL, "open", "https://youtube.com/c/@YKliffa", 0, 0, SW_SHOWNORMAL);
	}
	ImGui::SameLine(); ImGui::Text(" "); ImGui::SameLine();
	if (ImGui::Button(lang ? "Hobbit Technical Discord" : (const char*)u8"Технический канал Хоббита в Дискорде")) {
		ShellExecute(NULL, "open", "https://discord.gg/hvzB3maxQ3", 0, 0, SW_SHOWNORMAL);
	}


	ImGui::End();


}
