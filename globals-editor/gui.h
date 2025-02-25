#pragma once
#include <d3d9.h>
#include "TextEditor.h"
#include <string>

namespace gui
{
	inline std::string fileToEditGlobal = "GLOBALS.TXT";
	inline std::string fileToMergeGlobal = "ACTIONS.TXT";
	inline std::string saveFilePathGlobal = "GLOBALS.TXT";

	// constant window size
	constexpr int WIDTH = 1230;
	constexpr int HEIGHT = 630;

	// when this changes, exit threads
	// and close menu :)
	inline bool isRunning = true;

	// winapi window vars
	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = { };

	// points for window movement
	inline POINTS position = { };

	// direct x state vars
	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };

	// handle window creation & destruction
	void CreateHWindow(const char* windowName) noexcept;
	void DestroyHWindow() noexcept;
	void SetPaths() noexcept;

	// handle device creation & destruction
	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	// handle ImGui creation & destruction
	void CreateImGui() noexcept;
	void DestroyImGui() noexcept;

	void BeginRender() noexcept;
	void EndRender() noexcept;
	void Render() noexcept;
}
