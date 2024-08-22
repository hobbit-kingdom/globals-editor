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

static void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
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

int lang = 1; // 0 - RUS , 1 - ENG
std::string a = "Test";
std::vector<std::string> inputFields;


vector < string > inputTriggerFields = { "0" };
vector < string > inputActionFields = { "0" };

vector<string> TriggersNames = {};
vector<string> ActionsNames = {};


void addInputField() {
	inputFields.push_back("");
}

void removeInputField(int index) {
	inputFields.erase(inputFields.begin() + index);
}

void removeInputFieldVar(int index, vector<string>& arr) {
	arr.erase(arr.begin() + index);
}

void addLinkTriggerField() {
	inputTriggerFields.push_back("0");
}

void addLinkActionField() {
	inputActionFields.push_back("0");
}

bool is_numeric(const std::string& str) {
	for (char c : str) {
		if (!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}

void drawInputFields(string type, string vibor) {
	if (vibor == "Actions")
	{
		for (int i = 0; i < inputFields.size(); i++) {
			char buf[255]{};
			static int bufInt = 0;
			strcpy_s(buf, inputFields[i].c_str());
			ImGui::PushID(i);
			ImGui::Text(ActivityTypeArray[type][i].c_str());

			if (i == 0)
			{
				ImGui::Text(buf);
				inputFields[i] = buf;
			}
			else {
				if (ActivityTypeArray[type][i][ActivityTypeArray[type][i].size()-1] == 'd') {
					if (ImGui::InputText("", buf, sizeof(buf), ImGuiInputTextFlags_CharsDecimal)) {
						inputFields[i] = buf;
					}
				}
					else if (ImGui::InputText("", buf, sizeof(buf))) {
						inputFields[i] = buf;
					}
			}
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
			if (i == 0)
			{
				ImGui::Text(buf);
				inputFields[i] = buf;
			}
			else {
				if (TriggersTypeArray[type][i][TriggersTypeArray[type][i].size() - 1] == 'd') {
					if (ImGui::InputText("", buf, sizeof(buf), ImGuiInputTextFlags_CharsDecimal)) {
						inputFields[i] = buf;
					}
				}
				else if (ImGui::InputText("", buf, sizeof(buf))) {
					inputFields[i] = buf;
				}
			}
			ImGui::PopID();
		}
	}
	else if (vibor == "Links")
	{
		for (int i = 0; i < inputFields.size(); i++) {
			char buf[255]{};

			if (i == 4) {
				for (int j = 0; j < inputTriggerFields.size(); j++) {
					ImGui::PushID(i + j + 255);
					char buf1[255]{};
					strcpy_s(buf1, inputTriggerFields[j].c_str());

					ImGui::Text(LinksTypeArray[type][i].c_str());
					ImGui::SameLine(0, 0);
					ImGui::Text((const char*)to_string(j).c_str());
					ImGui::SameLine(0, 0);
					ImGui::Text(":d");
					if (ImGui::InputText("", buf1, sizeof(buf1), ImGuiInputTextFlags_CharsDecimal)) {
						inputTriggerFields[j] = buf1;
					}

					if (inputTriggerFields[j] != "" && is_numeric(inputTriggerFields[j]) && stoi(inputTriggerFields[j]) < TriggersNames.size() && ImGui::IsItemHovered())
					{
						ImGui::BeginTooltip();
						ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);

						ImGui::TextUnformatted(TriggersNames[stoi(inputTriggerFields[j])].c_str());
						ImGui::PopTextWrapPos();
						ImGui::EndTooltip();
					}
					ImGui::SameLine();
					if (ImGui::Button("-")) {
						removeInputFieldVar(j, inputTriggerFields);
					}

					ImGui::PopID();
				}
			}
			else if (i == 6) {
				for (int j = 0; j < inputActionFields.size(); j++) {
					ImGui::PushID(i + j + 255 + 255);
					char buf1[255]{};
					strcpy_s(buf1, inputActionFields[j].c_str());

					ImGui::Text(LinksTypeArray[type][i].c_str());
					ImGui::SameLine(0, 0);
					ImGui::Text((const char*)to_string(j).c_str());
					ImGui::SameLine(0, 0);
					ImGui::Text(":d");
					if (ImGui::InputText("", buf1, sizeof(buf1), ImGuiInputTextFlags_CharsDecimal)) {
						inputActionFields[j] = buf1;
					}

					if (inputActionFields[j] != "" && is_numeric(inputActionFields[j]) && stoi(inputActionFields[j]) < ActionsNames.size() && ImGui::IsItemHovered())
					{
						ImGui::BeginTooltip();
						ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);

						ImGui::TextUnformatted(ActionsNames[stoi(inputActionFields[j])].c_str());
						ImGui::PopTextWrapPos();
						ImGui::EndTooltip();
					}

					ImGui::SameLine();
					if (ImGui::Button("-")) {
						removeInputFieldVar(j, inputActionFields);
					}
					ImGui::PopID();

				}
			}
			else {
				if (i == 3)
					inputFields[i] = to_string(inputTriggerFields.size());
				else if (i == 5)
					inputFields[i] = to_string(inputActionFields.size());

				strcpy_s(buf, inputFields[i].c_str());
				ImGui::PushID(i);
				ImGui::Text(LinksTypeArray[type][i].c_str());

				if (ImGui::InputText("", buf, sizeof(buf), ImGuiInputTextFlags_CharsDecimal)) {
					inputFields[i] = buf;
				}
				if (i == 3)
				{
					ImGui::SameLine();
					if (ImGui::Button("+")) addLinkTriggerField();
				}
				else if (i == 5)
				{
					ImGui::SameLine();
					if (ImGui::Button("+")) addLinkActionField();
				}
				else if (i == 2)
				{
					ImGui::SameLine(); HelpMarker(lang ?
						"0 - all triggers must be activated\n\n1 - one of the triggers has to be activated"
						:
						(const char*)u8"0 - все триггеры должны сработать\n\n1 - один из триггеров должен сработать"
					);
				}

				ImGui::PopID();
			}
			/*
			ImGui::SameLine();
			if (ImGui::Button("Remove")) {
				removeInputField(i);
				i--;
			}
			*/
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
string fileToEdit = "globals.TXT";
string saveFilePath = "globals.TXT";

map<int, vector<string>> globalsActions;
map<int, int> globalsActionsPositions;

map<int, vector<string>> globalsTriggers;
map<int, int> globalsTriggersPositions;


map<int, vector<string>> globalsLinks;
map<int, int> globalsLinksPositions;

vector<string> LinksNames = {};

static int item_current_idx = 0;
static int item_current_idx_trigger = 0;
static int item_current_idx_link = 0;
static int currentActionTypeIndex = 0;

static const char* actionsTypes[] = { "0", "1", "2", "4", "7", "8", "9", "10", "11",
"12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "25", "28",
"29", "30", "33", "34", "35", "36", "37", "40", "41", "43", "44", "45", "48", "49",
"50", "51", "52" };

static const char* TriggerTypes[] = { "0", "3", "5", "6", "7", "8", "9", "11", "12",
"15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "29", "30",
"31", "32", "34" };

static int TriggerType = 0;
string vibor = " ";

void matchInputFieldsSize(string type, string vibor)
{
	inputFields.clear();
	int inde = 0;

	if (vibor == "Actions")
	{
		for (auto i : ActivityTypeArray[type])
		{
			inputFields.push_back(globalsActions[item_current_idx][inde]);
			inde++;
		}
	}
	else if (vibor == "Triggers")
	{
		for (auto i : TriggersTypeArray[type])
		{
			inputFields.push_back(globalsTriggers[item_current_idx_trigger][inde]);
			inde++;
		}
	}
	else if (vibor == "Links")
	{
		inputTriggerFields.clear();
		inputActionFields.clear();
		for (int i = 0; i < globalsLinks[item_current_idx_link].size(); i++)
		{
			inputFields.push_back(globalsLinks[item_current_idx_link][i]);

			if (i == 3)
			{
				inputFields.push_back("0");
				int actionCountPos = i + 1 + stoi(globalsLinks[item_current_idx_link][i]);
				i++;
				while (i < actionCountPos)
				{
					inputTriggerFields.push_back(globalsLinks[item_current_idx_link][i]);
					i++;
				}
				inputFields.push_back(globalsLinks[item_current_idx_link][i]);
				inputFields.push_back("0");
				i++;
				while (i < globalsLinks[item_current_idx_link].size())
				{
					inputActionFields.push_back(globalsLinks[item_current_idx_link][i]);
					i++;
				}
				break;

			}
		}
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
	{
		for (auto i : TriggersTypeArray[type])
		{
			if (i == "TriggerType0:d")
			{
				inputFields.push_back(TriggerTypes[TriggerType]);
			}
			else inputFields.push_back(DefaultValues[i]);
		}
	}
	else if (vibor == "Links")
	{
		for (auto i : LinksTypeArray[type])
		{
			inputFields.push_back(DefaultValues[i]);
		}
	}
}

void editAction()
{
	string s = to_string(getObjectNumber(globalsActions[item_current_idx][0]));

	for (int i = 0; i < IM_ARRAYSIZE(actionsTypes); i++)
	{
		if (s == actionsTypes[i]) currentActionTypeIndex = i;
	}
}

void editTrigger()
{
	string s = to_string(getObjectNumber(globalsTriggers[item_current_idx_trigger][0]));

	for (int i = 0; i < IM_ARRAYSIZE(TriggerTypes); i++)
	{
		if (s == TriggerTypes[i]) TriggerType = i;
	}
}

static int aiManagerPropRowIndex = 0;

bool loaded = false;
bool errorOpen = false;

void reloadFile(ImGuiTextBuffer& log)
{
	globalsTriggers.clear();
	globalsTriggersPositions.clear();
	TriggersNames.clear();

	globalsActions.clear();
	globalsActionsPositions.clear();
	ActionsNames.clear();

	globalsLinks.clear();
	globalsLinksPositions.clear();
	LinksNames.clear();


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
		errorOpen = true;
		loaded = false;
		log.clear();
	}
	else {
		string line;
		int lineCounter = 1;
		while (std::getline(file, line)) {

			if (!line.find("[ Action") || !line.find("[Action"))
			{
				// Action header
				int actionNumber = getObjectNumber(line);

				if (std::getline(file, line))
				{
					//Action propreties not needed since we can always get Action type from first parameter in parameters
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
			else if (!line.find("[ Trigger") || !line.find("[Trigger"))
			{
				int triggerNumber = getObjectNumber(line);

				if (getline(file, line))
				{
					if (getline(file, line))
					{
						vector<string> parameters = splitBySpaces(line);

						globalsTriggers.emplace(triggerNumber, parameters);
						globalsTriggersPositions.emplace(triggerNumber, lineCounter);

						lineCounter++;
					}
					lineCounter++;
				}
			}
			else if (!line.find("[ Link") || !line.find("[Link"))
			{
				int linkNumber = getObjectNumber(line);

				if (getline(file, line))
				{
					vector<string> parameterObjects = splitBySpaces(line);

					parameterObjects.erase(parameterObjects.begin());
					parameterObjects.erase(parameterObjects.end() - 1);

					if (getline(file, line))
					{
						vector<string> parameters = splitBySpaces(line);

						globalsLinks.emplace(linkNumber, parameters);
						globalsLinksPositions.emplace(linkNumber, lineCounter);
						lineCounter++;
					}
					lineCounter++;
				}
			}
			else if (!line.find("[ AIManager : 1 ]") || !line.find("[AIManager"))
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
		for (const auto& pair : globalsTriggers) TriggersNames.push_back("#" + to_string(pair.first) + " T" + pair.second[0] + " " + pair.second[1]);
		for (const auto& pair : globalsActions) ActionsNames.push_back("#" + to_string(pair.first) + " T" + pair.second[0] + " " + pair.second[1]);
		for (const auto& pair : globalsLinks) LinksNames.push_back("#" + to_string(pair.first));
		loaded = true;
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

	bool open = false, save = false, help = false;
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu(lang ? "Menu" : (const char*)u8"Меню"))
		{
			if (ImGui::MenuItem(lang ? "Open File" : (const char*)u8"Открыть Файл", NULL))
				open = true;
			if (ImGui::MenuItem(lang ? "Save File" : (const char*)u8"Сохранить Файл", NULL))
				save = true;

			ImGui::EndMenu();
		}
		if (ImGui::Button(lang ? "Help" : (const char*)u8"Помощь"))
		{
			help = true;
		}
		ImGui::EndMenuBar();
	}

	if (open)
		ImGui::OpenPopup(lang ? "Open File" : (const char*)u8"Открыть Файл");
	if (help)
		ImGui::OpenPopup("Help");
	if (errorOpen)
		ImGui::OpenPopup("Error");

	if (ImGui::BeginPopupModal("Error"))
	{
		ImGui::Text(lang ? "File path is invalid/file can't be opened" : (const char*)u8"Путь к файлу не верен/нельзя открыть файл");

		if (ImGui::Button("OK"))
		{
			ImGui::CloseCurrentPopup();
			errorOpen = false;
		}
		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Help"))
	{
		ImGui::Text("Actions");

		ImGui::Indent();

		ImGui::Text(lang ? "StringID: if you write text directly in a field\n\nand it will be displayed in the game.\n\nFor example subtitles." : (const char*)u8"StringID: впишите в поле текст\n\nи он будетв игре,\n\nнапример субтитры для катсцен.");

		ImGui::Unindent();

		ImGui::Text("");

		if (ImGui::Button("OK"))
		{
			ImGui::CloseCurrentPopup();
			help = false;
		}
		ImGui::EndPopup();
	}

	if (file_dialog.showFileDialog(lang ? "Open File" : (const char*)u8"Открыть Файл", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".txt"))
	{

		fileToEdit = file_dialog.selected_path;
	}
	if (file_dialog.showFileDialog(lang ? "Save File" : (const char*)u8"Сохранить Файл", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".txt"))
	{
		saveFilePath = file_dialog.selected_path;
		std::ofstream fileStream(saveFilePath);
		if (fileStream.is_open()) {
			fileToEdit = fileToEdit.c_str();
			std::ifstream file(fileToEdit);
			if (!file) {
				std::cerr << "Unable to open file";
			}
			else {
				string line;
				while (std::getline(file, line)) {
					fileStream << line << endl;
				}
			}
			fileStream.close(); // Закрываем файл
		}
	}
	ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("THE GLOBALS EDITOR").x) / 2.f);
	ImGui::Text("THE GLOBALS EDITOR");
	ImGui::Text("");

	ImGui::BeginChild("left2 pane", ImVec2(170, 450), true);
	if (loaded)
	{
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

		if (ImGui::Button(lang ? "Triggers" : (const char*)u8"Триггеры"))
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
				matchInputFieldsSize(to_string(getObjectNumber(globalsActions[item_current_idx][0])), vibor);
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
				changeTypeInputFields(TriggerTypes[TriggerType], vibor);
				actionsEdit = false;
				triggersEdit = false;
				linksEdit = false;

				actionsAdd = false;
				triggersAdd = true;
				linksAdd = false;
			}
			ImGui::Text("");

			ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.24f);
			if (ImGui::Button(lang ? "Edit Trigger" : (const char*)u8"Изменить триггер"))
			{
				editTrigger();
				matchInputFieldsSize(to_string(getObjectNumber(globalsTriggers[item_current_idx_trigger][0])), vibor);

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
			vibor = "Links";
			if (ImGui::Button(lang ? "Add Link" : (const char*)u8"Добавить ссылку"))
			{
				inputTriggerFields.clear();
				inputActionFields.clear();
				changeTypeInputFields("1", vibor);

				actionsEdit = false;
				triggersEdit = false;
				linksEdit = false;

				actionsAdd = false;
				triggersAdd = false;
				linksAdd = true;
			}
			ImGui::Text("");

			if (ImGui::Button(lang ? "Edit Link" : (const char*)u8"Изменить ссылку"))
			{
				inputTriggerFields.clear();
				inputActionFields.clear();
				item_current_idx_link = 0;
				changeTypeInputFields("1", vibor);

				actionsEdit = false;
				triggersEdit = false;
				linksEdit = true;

				actionsAdd = false;
				triggersAdd = false;
				linksAdd = false;
			}
		}
	}
	else {
		ImGui::Text(lang ? "Load globals file at first" : (const char*)u8"Сначало загрузите\n\nфайл глобалс");
	}
	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("left pane", ImVec2(500, 450), true);
	static ImGuiTextBuffer log;
	if (linksEdit)
	{
		ImGui::Text("Link");
		ImGui::SameLine();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.5f);

		const char* combo_preview_value = LinksNames[item_current_idx_link].c_str();
		if (ImGui::BeginCombo(" ", combo_preview_value))
		{
			for (int n = 0; n < LinksNames.size(); n++)
			{
				const bool is_selected = (item_current_idx_link == n);
				if (ImGui::Selectable(LinksNames[n].c_str(), is_selected))
				{
					item_current_idx_link = n;
					matchInputFieldsSize("1", vibor);
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::SameLine(); HelpMarker(lang ?
			"With a link you can like triggers and actions together.\n\n"
			"When a trigger will be triggered, an action will de executed.\n\n"
			"Multiple triggers can be linked to multiple actions, etc." :
			(const char*)u8"Ссылка соединяет триггер с активностью.\n\nКогда сработает триггер, будет запущена активность.\n\nНесколько триггеров может быть соединено с несколькими активностями."
		);

		ImGui::Text("");

		if (ImGui::Button(lang ? "Save link " : (const char*)u8"Сохранить ссылку "))
		{
			replaceText(fileToEdit, globalsLinksPositions[item_current_idx_link], compileLink(inputFields, inputTriggerFields, inputActionFields, item_current_idx_link, item_current_idx_link));
			reloadFile(log);
		}
		ImGui::SameLine();
		if (ImGui::Button(lang ? "Delete Link" : (const char*)u8"Удалить ссылку"))
		{
			inputTriggerFields.clear();
			inputActionFields.clear();
			inputFields[3] = "0";
			inputFields[5] = "0";
			replaceText(fileToEdit, globalsLinksPositions[item_current_idx_link], compileLink(inputFields, inputTriggerFields, inputActionFields, item_current_idx_link, item_current_idx_link));
			reloadFile(log);
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(lang ? "Replaces link with an empty one" : (const char*)u8"Заменяет ссылку на пустую");
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
		ImGui::SameLine();
		if (ImGui::Button(lang ? "Revert" : (const char*)u8"Вернуть исходное"))
		{
			matchInputFieldsSize("1", vibor);
		}

		ImGui::Text("");

		drawInputFields("1", vibor);
	}
	if (linksAdd)
	{
		ImGui::Text("Link ");
		ImGui::SameLine();
		ImGui::Text(to_string(globalsLinks.size()).c_str());

		ImGui::SameLine(); HelpMarker(lang ?
			"With a link you can like triggers and actions together.\n\n"
			"When a trigger will be triggered, an action will de executed.\n\n"
			"Multiple triggers can be linked to multiple actions, etc." :
			(const char*)u8"Ссылка соединяет триггер с активностью.\n\nКогда сработает триггер, будет запущена активность.\n\nНесколько триггеров может быть соединено с несколькими активностями."
		);

		ImGui::Text("");

		if (ImGui::Button(lang ? "Add link " : (const char*)u8"Добавить ссылку "))
		{
			for (const std::string& value : inputFields) {
				std::cout << "Input Value: " << value << std::endl;
			}

			insertText(fileToEdit, globalsLinksPositions[globalsLinksPositions.size() - 1] + 3, compileLink(inputFields, inputTriggerFields, inputActionFields, stoi(inputFields[0]), globalsLinksPositions.size()));
			vector<string> aiManagerProp = { to_string(globalsTriggers.size()) + " " + to_string(globalsActions.size()) + " " + to_string(globalsLinks.size() + 1) };
			replaceText(fileToEdit, aiManagerPropRowIndex, aiManagerProp);
			reloadFile(log);
		}

		ImGui::Text("");

		drawInputFields("1", vibor);
	}
	if (triggersEdit)
	{
		ImGui::Text("Trigger");
		ImGui::SameLine();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.5f);

		const char* combo_preview_value = TriggersNames[item_current_idx_trigger].c_str();
		if (ImGui::BeginCombo("   ", combo_preview_value))
		{
			for (int n = 0; n < TriggersNames.size(); n++)
			{
				const bool is_selected = (item_current_idx_trigger == n);
				if (ImGui::Selectable(TriggersNames[n].c_str(), is_selected))
				{
					item_current_idx_trigger = n;
					editTrigger();
					matchInputFieldsSize(TriggerTypes[TriggerType], vibor);
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::SameLine(); HelpMarker(lang ?
			"A trigger is something that can happen in The Hobbit.\n\n"
			"For example it can be when a stone hits an NPC,\n\n"
			"when Bilbo enters volume, a cutscene finishes, etc." :
			(const char*)u8"Триггер это что-то, что происходит в игре.\n\nНапример Бильбо заходит в волум, катсцена закончилась,\n\nпо НПС попал камень и тд."
		);

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

				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					ImGui::TextUnformatted(lang ? tipsTriggersENG[TriggerTypes[n]].c_str() : tipsTriggersRUS[TriggerTypes[n]].c_str());
					ImGui::PopTextWrapPos();
					ImGui::EndTooltip();
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::SameLine();
		if (ImGui::Button(lang ? "Revert type" : (const char*)u8"Вернуть исходное"))
		{
			editTrigger();
			matchInputFieldsSize(TriggerTypes[TriggerType], vibor);
		}

		ImGui::Text("");

		if (ImGui::Button(lang ? "Save trigger" : (const char*)u8"Сохранить триггер"))
		{
			for (const std::string& value : inputFields) {
				std::cout << "Input Value: " << value << std::endl;
			}

			replaceText(fileToEdit, globalsTriggersPositions[item_current_idx_trigger], compileAction(inputFields, stoi(inputFields[0]), item_current_idx_trigger, vibor));
			reloadFile(log);
		}
		ImGui::SameLine();
		if (ImGui::Button(lang ? "Delete trigger" : (const char*)u8"Удалить триггер"))
		{
			for (int i = 2; i < inputFields.size(); i++)
				inputFields[i] = "";
			inputFields[0] = "0";

			replaceText(fileToEdit, globalsTriggersPositions[item_current_idx_trigger], compileAction(inputFields, 0, item_current_idx_trigger, vibor)); // 0 - empty activity
			triggersEdit = false;
			reloadFile(log);
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(lang ? "Replaces trigger with an empty one" : (const char*)u8"Заменяет триггер на пустой");
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}

		ImGui::Text("");

		drawInputFields(TriggerTypes[TriggerType], vibor);
	}
	if (triggersAdd)
	{
		ImGui::Text("Trigger ");
		ImGui::SameLine();
		ImGui::Text(to_string(globalsTriggers.size()).c_str());
		ImGui::SameLine(); HelpMarker(lang ?
			"A trigger is something that can happen in The Hobbit.\n\n"
			"For example it can be when a stone hits an NPC,\n\n"
			"when Bilbo enters volume, a cutscene finishes, etc." :
			(const char*)u8"Триггер это что-то, что происходит в игре.\n\nНапример Бильбо заходит в волум, катсцена закончилась,\n\nпо НПС попал камень и тд."
		);
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

				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					ImGui::TextUnformatted(lang ? tipsTriggersENG[TriggerTypes[n]].c_str() : tipsTriggersRUS[TriggerTypes[n]].c_str());
					ImGui::PopTextWrapPos();
					ImGui::EndTooltip();
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::Text("");

		if (ImGui::Button(lang ? "Add trigger " : (const char*)u8"Добавить триггер "))
		{
			insertText(fileToEdit, globalsTriggersPositions[globalsTriggersPositions.size() - 1] + 3, compileAction(inputFields, stoi(inputFields[0]), globalsTriggersPositions.size(), vibor));
			vector<string> aiManagerProp = { to_string(globalsTriggers.size() + 1) + " " + to_string(globalsActions.size()) + " " + to_string(globalsLinks.size()) };
			replaceText(fileToEdit, aiManagerPropRowIndex, aiManagerProp);
			reloadFile(log);
		}

		ImGui::Text("");

		drawInputFields(TriggerTypes[TriggerType], vibor);
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
					matchInputFieldsSize(actionsTypes[currentActionTypeIndex], vibor);
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::SameLine(); HelpMarker(lang ?
			"Action is something that will be executed.\n\n"
			"This can be telport Bilbo, start a cutscene, spawn NPC, etc." :
			(const char*)u8"Активность это действие что произойдет в игре.\n\nНапример телепортировать Бильбо, заспавнить НПС, начать катсцену и тд."
		);

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
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					ImGui::TextUnformatted(lang ? tipsActionsENG[actionsTypes[n]].c_str() : tipsActionsRUS[actionsTypes[n]].c_str());
					ImGui::PopTextWrapPos();
					ImGui::EndTooltip();
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
			matchInputFieldsSize(actionsTypes[currentActionTypeIndex], vibor);
		}

		ImGui::Text("");

		if (ImGui::Button(lang ? "Save action" : (const char*)u8"Сохранить активность"))
		{
			for (const std::string& value : inputFields) {
				std::cout << "Input Value: " << value << std::endl;
			}

			replaceText(fileToEdit, globalsActionsPositions[item_current_idx], compileAction(inputFields, stoi(inputFields[0]), item_current_idx, vibor));
			reloadFile(log);
		}
		ImGui::SameLine();
		if (ImGui::Button(lang ? "Delete action" : (const char*)u8"Удалить активность"))
		{
			for (int i = 2; i < inputFields.size(); i++)
				inputFields[i] = "";
			inputFields[0] = "0";

			replaceText(fileToEdit, globalsActionsPositions[item_current_idx], compileAction(inputFields, 0, item_current_idx, vibor)); // 0 - empty activity
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

		ImGui::Text("");

		drawInputFields(actionsTypes[currentActionTypeIndex], vibor);
	}
	if (actionsAdd)
	{
		ImGui::Text("Action ");
		ImGui::SameLine();
		ImGui::Text(to_string(globalsActions.size()).c_str());

		ImGui::SameLine(); HelpMarker(lang ?
			"Action is something that will be executed.\n\n"
			"This can be telport Bilbo, start a cutscene, spawn NPC, etc." :
			(const char*)u8"Активность это действие что произойдет в игре.\n\nНапример телепортировать Бильбо, заспавнить НПС, начать катсцену и тд."
		);

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
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					ImGui::TextUnformatted(lang ? tipsActionsENG[actionsTypes[n]].c_str() : tipsActionsRUS[actionsTypes[n]].c_str());
					ImGui::PopTextWrapPos();
					ImGui::EndTooltip();
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::Text("");

		if (ImGui::Button(lang ? "Add action " : (const char*)u8"Добавить активность "))
		{
			for (const std::string& value : inputFields) {
				std::cout << "Input Value: " << value << std::endl;
			}

			insertText(fileToEdit, globalsActionsPositions[globalsActionsPositions.size() - 1] + 3, compileAction(inputFields, stoi(inputFields[0]), globalsActionsPositions.size(), vibor));
			vector<string> aiManagerProp = { to_string(globalsTriggers.size()) + "  " + to_string(globalsActions.size() + 1) + " " + to_string(globalsLinks.size()) };
			replaceText(fileToEdit, aiManagerPropRowIndex, aiManagerProp);
			reloadFile(log);
		}

		ImGui::Text("");

		drawInputFields(actionsTypes[currentActionTypeIndex], vibor);
	}

	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("text pane", ImVec2(525, 450), true, ImGuiWindowFlags_HorizontalScrollbar);

	ImGui::Text(fileToEdit.c_str());
	if (ImGui::Button(lang ? "Load Globals" : (const char*)u8"Загрузить Глобалс")) reloadFile(log);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(lang ? "Make sure you selected globals file in the Menu" : (const char*)u8"Убедитесь что вы выбрали глобалс файл в меню");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

	ImGui::TextUnformatted(log.begin(), log.end());

	ImGui::EndChild();

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
