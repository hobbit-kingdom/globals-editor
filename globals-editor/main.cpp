#include "gui.h"
#include<iostream>
#include<fstream>
#include <thread>
#include <string>

#include "TextEditor.h"
#include <filesystem>
using namespace gui;
int main(  //__stdcall wWinMain
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{

	TextEditor editor;
	auto cpos = editor.GetCursorPosition();
	static const char* fileToEdit = "kingjoyer/gui.cpp";

	std::ifstream t(fileToEdit);
	std::cout << t.good();
	std::cout << std::filesystem::absolute(fileToEdit).string() << std::endl;
	std::string a = "";
	if (t.good())
	{
		std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		editor.SetText(str);
		a = str;
		std::cout << str;
		std::cout << "fff";
	}


	setlocale(LC_ALL, "RUSSIAN");

	// create gui
	CreateHWindow("Cheat Menu");
	CreateDevice();
	CreateImGui();

	while (gui::isRunning)
	{
		gui::BeginRender();

		gui::Render(a);
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	// destroy gui
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}
