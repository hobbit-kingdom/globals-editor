#include "gui.h"
#include<iostream>
#include<fstream>
#include <thread>
#include <string>
#include <vector>
#include <map>

#include "TextEditor.h"
#include <filesystem>

#include "ActivityTypeArray.h"
using namespace gui;

std::string wstring_to_string(const std::wstring& wstr) {
	return std::string(wstr.begin(), wstr.end());
}

int __stdcall wWinMain(  //__stdcall wWinMain 
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	std::vector<std::wstring> args;
	for (int i = 0; i < argc; i++) {
		args.push_back(argv[i]);
	}

	LocalFree(argv);

	if (args.size() == 2) gui::fileToEditGlobal = wstring_to_string(args[1]);
	else if (args.size() == 3) {
		gui::fileToEditGlobal = wstring_to_string(args[1]);
		gui::fileToMergeGlobal = wstring_to_string(args[2]);
	}

	if (AttachConsole(ATTACH_PARENT_PROCESS)) {
		// Redirect stdout to the console
		FILE* stdoutFile;
		if (freopen_s(&stdoutFile, "CONOUT$", "w", stdout) != 0) {
			MessageBox(NULL, "Failed to redirect stdout!", "Error", MB_ICONERROR);
			return 1;
		}

		// Redirect stderr to the console
		FILE* stderrFile;
		if (freopen_s(&stderrFile, "CONOUT$", "w", stderr) != 0) {
			MessageBox(NULL, "Failed to redirect stderr!", "Error", MB_ICONERROR);
			return 1;
		}

		// Now you can use printf, wprintf, std::cout, etc.
		printf("Optional: first arg is path to globals file, second - path to merge file. Has to be a full path to a file.");

	}

	//for (int i = 1; i < args.size(); i++) {
	//	std::string message = "Argument " + std::to_string(i) + ": " + wstring_to_string(args[i]);
	//	MessageBox(NULL, message.c_str(), "Argument", MB_OK);
	//}

	// create gui
	CreateHWindow("The Globals Editor");
	CreateDevice();
	CreateImGui();
	SetPaths();

	while (gui::isRunning)
	{
		gui::BeginRender();

		gui::Render();
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	// destroy gui
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	// Free the console if we allocated one (optional)
	if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
		FreeConsole();
	}

	return EXIT_SUCCESS;
}
