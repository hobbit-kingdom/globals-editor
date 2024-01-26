#include "gui.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"

#include <iostream>

#include <string>
#include <chrono>
#include <fstream>
#include <vector>
#include <map>

#include "TextEditor.h"
#include "ActivityTypeArray.h"
#include "imguiFileBrowser.h"
#include "TextFunctions.h"


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
void FileSelectionCallback(const char* result) {
	// Получить выбранный файл
	std::string selectedFile = result;

	// Выполнить необходимые действия с выбранным файлом
	// Например, вывести путь до файла на консоль
	std::cout << "Выбранный файл: " << selectedFile << std::endl;
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

bool actionsEdit = false;
bool triggersEdit = false;
bool linksEdit = false;

bool actionsAdd = false;
bool triggersAdd = false;
bool linksAdd = false;

int lang = 0; // 0 - RUS , 1 - ENG
std::string a = "Test";
std::vector<std::string> inputFields;

void addInputField() {
	inputFields.push_back("");
}

void removeInputField(int index) {
	inputFields.erase(inputFields.begin() + index);
}
void drawInputFields(string type, string vibor) {
	if (vibor == "Actions")
	{
		for (int i = 0; i < inputFields.size(); i++) {
			char buf[255]{};
			strcpy_s(buf, inputFields[i].c_str());
			ImGui::PushID(i);
			ImGui::Text(ActivityTypeArray[type][i].c_str());

			if (ImGui::InputText("", buf, sizeof(buf))) {
				inputFields[i] = buf;
			}
			/*
			ImGui::SameLine();
			if (ImGui::Button("Remove")) {
				removeInputField(i);
				i--;
			}
			*/
			ImGui::PopID();
		}
	}
	else if (vibor == "Triggers")
	{
		for (int i = 0; i < inputFields.size(); i++) {
			char buf[255]{};
			strcpy_s(buf, inputFields[i].c_str());
			ImGui::PushID(i);
			ImGui::Text(TriggersTypeArray[type][i].c_str());

			if (ImGui::InputText("", buf, sizeof(buf))) {
				inputFields[i] = buf;
			}
			/*
			ImGui::SameLine();
			if (ImGui::Button("Remove")) {
				removeInputField(i);
				i--;
			}
			*/
			ImGui::PopID();
		}
	}
}

std::vector<std::string> splitBySpaces(string s)
{
	std::istringstream iss(s);
	std::vector<std::string> words;
	std::string word;

	while (iss >> word) {
		if (!word.empty()) {
			// Check if the word is quoted
			if (word.front() == '"' && word.back() != '"') {
				std::string quotedWord = word;
				while (iss >> word && word.back() != '"') {
					quotedWord += " " + word;
				}
				// Add the complete quoted word (including spaces) to the vector
				quotedWord += " " + word;
				words.push_back(quotedWord);
			}
			else {
				words.push_back(word);
			}
		}
	}

	return words;
}

int getObjectNumber(string s)
{
	std::stringstream ss(s);
	while (!isdigit(ss.peek()) && ss.peek() != EOF) {
		ss.ignore();
	}

	// Extract the number
	int extractedNumber;
	ss >> extractedNumber;

	return extractedNumber;
}

imgui_addons::ImGuiFileBrowser file_dialog;
string fileToEdit = "globals-editor/globals.TXT";

map<int, vector<string>> globalsActions;
map<int, int> globalsActionsPositions;
vector<int> ActionIndexes;

vector<string> ActionsNames = {};

map<int, vector<string>> globalsTriggers;
map<int, int> globalsTriggersPositions;
vector<int> TriggerIndexes;

vector<string> TriggersNames = {};

static int item_current_idx = 0;
static int currentActionTypeIndex = 0;
static const char* actionsTypes[] = { "1", "2", "4", "7" };
static const char* TriggerTypes[] = { "3" };
static int TriggerType = 0;
string vibor = " ";
void matchInputFieldsSize(string type)
{
	inputFields.clear();
	cout << item_current_idx << "\n";
	int inde = 0;
	for (auto i : ActivityTypeArray[type])
	{
		inputFields.push_back(globalsActions[item_current_idx][inde]);
		inde++;
	}
}

void changeTypeInputFields(string type, string vibor)
{

	inputFields.clear();
	if (vibor == "Actions") {
		for (auto i : ActivityTypeArray[type])
		{

			if (i == "ActionType0:d")
			{
				inputFields.push_back(actionsTypes[currentActionTypeIndex]);
			}
			else inputFields.push_back(DefaultValues[i]);
		}
	}
	else if (vibor == "Triggers")
		for (auto i : TriggersTypeArray[type])
		{

			if (i == "TriggerType0:d")
			{
				inputFields.push_back(TriggerTypes[TriggerType]);
			}
			else inputFields.push_back(DefaultValues[i]);
		}
}



void editAction()
{
	string s = to_string(getObjectNumber(ActionsNames[item_current_idx]));

	for (int i = 0; i < IM_ARRAYSIZE(actionsTypes); i++)
	{
		if (s == actionsTypes[i]) currentActionTypeIndex = i;
	}
}

static int aiManagerPropRowIndex = 0;

void reloadFile(ImGuiTextBuffer& log)
{
	globalsActions.clear();
	globalsActionsPositions.clear();
	ActionsNames.clear();

	fileToEdit = fileToEdit.c_str();

	std::ifstream t(fileToEdit);

	if (t.good())
	{
		string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		a = str;
		log.clear();
		log.appendf(a.c_str());
	}

	std::ifstream file(fileToEdit);
	if (!file) {
		std::cerr << "Unable to open file";
	}
	else {
		string line;
		int lineCounter = 1;
		while (std::getline(file, line)) {

			if (!line.find("[ Action"))
			{
				// Action header
				int actionNumber = getObjectNumber(line);

				if (std::getline(file, line))
				{
					//Action propreties not needed since we can always get Action type from first parameter in parameters
					/*
					vector<string> propreties = splitBySpaces(line);

					propreties.erase(propreties.begin());
					propreties.pop_back();
					*/
					if (std::getline(file, line))
					{
						//Action Parameters
						vector<string> parameters = splitBySpaces(line);

						globalsActions.emplace(actionNumber, parameters);
						globalsActionsPositions.emplace(actionNumber, lineCounter);
						lineCounter++;
					}
					lineCounter++;
				}
			}

			if (!line.find("[ AIManager : 1 ]"))
			{
				if (std::getline(file, line))
				{
					lineCounter++;
					if (std::getline(file, line))
					{
						lineCounter++;
						aiManagerPropRowIndex = lineCounter;
					}
				}
			}

			lineCounter++;
		}

		for (const auto& pair : globalsActions) ActionsNames.push_back(pair.second[0] + "|" + pair.second[1]);
	}
}

void gui::Render() noexcept
{
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	ImGui::Begin(
		"The Globals Editor v1.0 by Mr_Kliff and king174rus",
		&isRunning,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_MenuBar
	);

	bool open = false, save = false;
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("Open", NULL))
				open = true;
			if (ImGui::MenuItem("Save", NULL))
				save = true;

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (open)
		ImGui::OpenPopup("Open File");
	if (save)
		ImGui::OpenPopup("Save File");

	if (file_dialog.showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".txt"))
	{
		std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
		std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file

		fileToEdit = file_dialog.selected_path;
	}

	ImGui::ShowDemoWindow();

	ImGui::Text("                                                                            THE GLOBALS EDITOR                  ");
	ImGui::Text("");

	ImGui::BeginChild("left2 pane", ImVec2(200, 0), true);

	if (ImGui::Button(lang ? "Actions" : (const char*)u8"Активности"))
	{
		actions = true;
		triggers = false;
		links = false;

		actionsEdit = false;
		triggersEdit = false;
		linksEdit = false;

		actionsAdd = false;
		triggersAdd = false;
		linksAdd = false;
	}

	if (ImGui::Button(lang ? "Triggers" : (const char*)u8"Тригеры"))
	{
		actions = false;
		triggers = true;
		links = false;

		actionsEdit = false;
		triggersEdit = false;
		linksEdit = false;

		actionsAdd = false;
		triggersAdd = false;
		linksAdd = false;
	}

	if (ImGui::Button(lang ? "Links" : (const char*)u8"Ссылки"))
	{
		actions = false;
		triggers = false;
		links = true;

		actionsEdit = false;
		triggersEdit = false;
		linksEdit = false;

		actionsAdd = false;
		triggersAdd = false;
		linksAdd = false;
	}

	ImGui::Text("");
	ImGui::Text("");
	ImGui::Text("");

	if (actions)
	{
		vibor = "Actions";
		if (ImGui::Button(lang ? "Add Action" : (const char*)u8"Добавить активность"))
		{
			changeTypeInputFields(actionsTypes[currentActionTypeIndex], vibor);
			actionsEdit = false;
			triggersEdit = false;
			linksEdit = false;

			actionsAdd = true;
			triggersAdd = false;
			linksAdd = false;
		}

		ImGui::Text("");

		if (ImGui::Button(lang ? "Edit Action" : (const char*)u8"Изменить активность"))
		{
			editAction();
			matchInputFieldsSize(to_string(getObjectNumber(ActionsNames[item_current_idx])));
			actionsEdit = true;
			triggersEdit = false;
			linksEdit = false;

			actionsAdd = false;
			triggersAdd = false;
			linksAdd = false;
		}
	}

	if (triggers)
	{

		vibor = "Triggers";
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.24f);

		if (ImGui::Button(lang ? "Add Trigger" : (const char*)u8"Добавить триггер"))
		{
			actionsEdit = false;
			triggersEdit = false;
			linksEdit = false;
			actionsAdd = false;
			triggersAdd = true;
			linksAdd = false;

		}
		ImGui::Text("");


		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.24f);
		if (ImGui::Button(lang ? "Edit Trigger" : (const char*)u8"Изменить тригер"))
		{
			actionsEdit = false;
			triggersEdit = true;
			linksEdit = false;
			actionsAdd = false;
			triggersAdd = false;
			linksAdd = false;
		}
	}

	if (links)
	{
		if (ImGui::Button(lang ? "Add Link" : (const char*)u8"Добавить ссылку"))
		{
			actionsEdit = false;
			triggersEdit = false;
			linksEdit = true;
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

	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("left pane", ImVec2(600, 0), true);
	if (linksEdit)
	{

	}
	static ImGuiTextBuffer log;
	if (triggersEdit)
	{
		ImGui::Text("Action");
		ImGui::SameLine();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.5f);

		const char* combo_preview_value = ActionsNames[item_current_idx].c_str();
		if (ImGui::BeginCombo("   ", combo_preview_value))
		{
			for (int n = 0; n < ActionsNames.size(); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(ActionsNames[n].c_str(), is_selected))
				{
					item_current_idx = n;
					editAction();
					matchInputFieldsSize(actionsTypes[currentActionTypeIndex]);
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::Text("");

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.24f);

		const char* combo_preview_value2 = TriggerTypes[TriggerType];
		if (ImGui::BeginCombo(lang ? "Change Trigger Type" : (const char*)u8"Изменить Тип Триггера", combo_preview_value2))
		{
			for (int n = 0; n < IM_ARRAYSIZE(TriggerTypes); n++)
			{
				const bool is_selected = (TriggerType == n);
				if (ImGui::Selectable(TriggerTypes[n], is_selected))
				{
					currentActionTypeIndex = n;
					changeTypeInputFields(TriggerTypes[TriggerType], vibor);
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::SameLine();
		if (ImGui::Button(lang ? "Revert type" : (const char*)u8"Вернуть исходное"))
		{
			editAction();
			matchInputFieldsSize(TriggerTypes[TriggerType]);
		}

		ImGui::Text("");

		drawInputFields(TriggerTypes[TriggerType], vibor);

		if (ImGui::Button(lang ? "Save action" : (const char*)u8"Сохранить активность"))
		{
			for (const std::string& value : inputFields) {
				std::cout << "Input Value: " << value << std::endl;
			}

			replaceText(fileToEdit, globalsActionsPositions[item_current_idx], compileAction(inputFields, stoi(inputFields[0]), item_current_idx));
			reloadFile(log);
		}
		ImGui::SameLine();
		if (ImGui::Button(lang ? "Delete action" : (const char*)u8"Удалить активность"))
		{
			for (int i = 2; i < inputFields.size(); i++)
				inputFields[i] = "";
			inputFields[0] = "0";

			replaceText(fileToEdit, globalsActionsPositions[item_current_idx], compileAction(inputFields, 0, item_current_idx)); // 0 - empty activity
			actionsEdit = false;
			reloadFile(log);
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(lang ? "Replaces activity with an empty one" : (const char*)u8"Заменяет активность на пустую");
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
	if (triggersAdd)
	{
		ImGui::Text("Trigger ");
		ImGui::SameLine();
		ImGui::Text(to_string(globalsActions.size()).c_str());


		ImGui::Text("");

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.24f);

		const char* combo_preview_value2 = TriggerTypes[TriggerType];
		if (ImGui::BeginCombo(lang ? "Change Trigger Type" : (const char*)u8"Изменить Тип Триггера", combo_preview_value2))
		{
			for (int n = 0; n < IM_ARRAYSIZE(TriggerTypes); n++)
			{
				const bool is_selected = (TriggerType == n);
				if (ImGui::Selectable(TriggerTypes[n], is_selected))
				{
					TriggerType = n;
					changeTypeInputFields(TriggerTypes[TriggerType], vibor);
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		drawInputFields(TriggerTypes[TriggerType], vibor);
		if (ImGui::Button(lang ? "Save trigger" : (const char*)u8"Сохранить триггер"))
		{
			insertText(fileToEdit, globalsActionsPositions[globalsActionsPositions.size() - 1] + 3, compileAction(inputFields, stoi(inputFields[0]), globalsActionsPositions.size()));
			vector<string> aiManagerProp = { "153            " + to_string(globalsActions.size() + 1) + "         126         " };
			replaceText(fileToEdit, aiManagerPropRowIndex, aiManagerProp);
			reloadFile(log);
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(lang ? "Replaces activity with an empty one" : (const char*)u8"Заменяет активность на пустую");
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
	}
		if (actionsEdit)
		{
			ImGui::Text("Action");
			ImGui::SameLine();

			ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.5f);

			const char* combo_preview_value = ActionsNames[item_current_idx].c_str();
			if (ImGui::BeginCombo("   ", combo_preview_value))
			{
				for (int n = 0; n < ActionsNames.size(); n++)
				{
					const bool is_selected = (item_current_idx == n);
					if (ImGui::Selectable(ActionsNames[n].c_str(), is_selected))
					{
						item_current_idx = n;
						editAction();
						matchInputFieldsSize(actionsTypes[currentActionTypeIndex]);
					}

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			ImGui::Text("");

			ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.24f);

			const char* combo_preview_value2 = actionsTypes[currentActionTypeIndex];
			if (ImGui::BeginCombo(lang ? "Change Action Type" : (const char*)u8"Изменить Тип Активности", combo_preview_value2))
			{
				for (int n = 0; n < IM_ARRAYSIZE(actionsTypes); n++)
				{
					const bool is_selected = (currentActionTypeIndex == n);
					if (ImGui::Selectable(actionsTypes[n], is_selected))
					{
						currentActionTypeIndex = n;
						changeTypeInputFields(actionsTypes[currentActionTypeIndex], vibor);
					}

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			ImGui::SameLine();
			if (ImGui::Button(lang ? "Revert type" : (const char*)u8"Вернуть исходное"))
			{
				editAction();
				matchInputFieldsSize(actionsTypes[currentActionTypeIndex]);
			}

			ImGui::Text("");

			drawInputFields(actionsTypes[currentActionTypeIndex], vibor);

			if (ImGui::Button(lang ? "Save action" : (const char*)u8"Сохранить активность"))
			{
				for (const std::string& value : inputFields) {
					std::cout << "Input Value: " << value << std::endl;
				}

				replaceText(fileToEdit, globalsActionsPositions[item_current_idx], compileAction(inputFields, stoi(inputFields[0]), item_current_idx));
				reloadFile(log);
			}
			ImGui::SameLine();
			if (ImGui::Button(lang ? "Delete action" : (const char*)u8"Удалить активность"))
			{
				for (int i = 2; i < inputFields.size(); i++)
					inputFields[i] = "";
				inputFields[0] = "0";

				replaceText(fileToEdit, globalsActionsPositions[item_current_idx], compileAction(inputFields, 0, item_current_idx)); // 0 - empty activity
				actionsEdit = false;
				reloadFile(log);
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(lang ? "Replaces activity with an empty one" : (const char*)u8"Заменяет активность на пустую");
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
		}
		if (actionsAdd)
		{
			ImGui::Text("Action ");
			ImGui::SameLine();
			ImGui::Text(to_string(globalsActions.size()).c_str());


			ImGui::Text("");

			ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.24f);

			const char* combo_preview_value2 = actionsTypes[currentActionTypeIndex];
			if (ImGui::BeginCombo(lang ? "Change Action Type" : (const char*)u8"Изменить Тип Активности", combo_preview_value2))
			{
				for (int n = 0; n < IM_ARRAYSIZE(actionsTypes); n++)
				{
					const bool is_selected = (currentActionTypeIndex == n);
					if (ImGui::Selectable(actionsTypes[n], is_selected))
					{
						currentActionTypeIndex = n;
						changeTypeInputFields(actionsTypes[currentActionTypeIndex], vibor);
					}

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			/*
			ImGui::SameLine();
			if (ImGui::Button(lang ? "Revert type" : (const char*)u8"Вернуть исходное"))
			{
				editAction();
				matchInputFieldsSize(actionsTypes[currentActionTypeIndex]);
			}
			*/

			ImGui::Text("");

			drawInputFields(actionsTypes[currentActionTypeIndex], vibor);

			if (ImGui::Button(lang ? "Save action" : (const char*)u8"Сохранить активность"))
			{
				for (const std::string& value : inputFields) {
					std::cout << "Input Value: " << value << std::endl;
				}

				insertText(fileToEdit, globalsActionsPositions[globalsActionsPositions.size() - 1] + 3, compileAction(inputFields, stoi(inputFields[0]), globalsActionsPositions.size()));
				vector<string> aiManagerProp = { "153            " + to_string(globalsActions.size() + 1) + "         126         " };
				replaceText(fileToEdit, aiManagerPropRowIndex, aiManagerProp);
				reloadFile(log);
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(lang ? "Replaces activity with an empty one" : (const char*)u8"Заменяет активность на пустую");
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
		}
	}

		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("text pane", ImVec2(370, 0), true);


		if (ImGui::Button("Show File"))
		{
			reloadFile(log);

		}

		ImGui::TextUnformatted(log.begin(), log.end());
	
		ImGui::EndChild();
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
