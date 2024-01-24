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

int main(  //__stdcall wWinMain
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{

	//ActivityTypeArray.insert({ "hii", {"ff","dsd"} });

	for (const auto& pair : ActivityTypeArray) {
		std::cout << "Key: " << pair.first << ", Values: ";
		for (const auto& value : pair.second) {
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}

	setlocale(LC_ALL, "RUSSIAN");

	// create gui
	CreateHWindow("Cheat Menu");
	CreateDevice();
	CreateImGui();

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

	return EXIT_SUCCESS;
}
