//EngineMain.cpp
//Created 21/07/16
//Created By Daniel Bowler
//
//Entry point for the engine

#pragma once

#include "../Config/EngineConfig.h" //Build settings
#include "EngineStd.h"
#include "../OS/Application/Application.h"
#include "../Debug/Log/DebugLog.h"
#include <iostream>

//
//Libs - D3D11
//
#ifdef ENGINE_CONFIG_GRAPHICS_API_D3D11
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DCompiler.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "legacy_stdio_definitions.lib") //TODO: Remove dependancy on this for dxerr to work!
#pragma comment (lib, "dxgi.lib")

#if defined(DEBUG) | defined(_DEBUG)
#pragma comment (lib, "d3dx11d.lib")
#pragma comment (lib, "Effects11d.lib")
#pragma comment (lib, "dxguid.lib") //Debug names
#else
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "Effects11.lib")
#endif
#endif

#ifdef ENGINE_CONFIG_PLATFORM_WIN32
void ShowConsoleW32()
{
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);

	*stdout = *hf_out;
	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;
}
#endif
  
#ifdef ENGINE_CONFIG_PLATFORM_WIN32
int EngineMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance,
	LPWSTR     lpCmdLine,
	int       nCmdShow, 
	int appVersionMajor, int appVersionMinor, int appVersionPatch,
	EngineAPI::OS::Application* gameAppInstance)
{    
	//Set up checks for memory leaks.  
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//Enables console for debugging purposes
	//ShowConsoleW32();
	//AttachConsole(GetCurrentProcessId());

	//Ensure an app exists.  
	if (gameAppInstance == NULL)
		EngineAPI::Debug::DebugLog::PrintErrorMessage("EngineMain: gameAppInstance == NULL. Make sure to create a project specific Application instance.\n");
	
	//Set app global pointer & init the engine. 
	g_App = (EngineAPI::OS::Application*)gameAppInstance;
	if (!g_App->InitEngine(hInstance, lpCmdLine, NULL, appVersionMajor, appVersionMinor, appVersionPatch, 960, 540)) //Win32
		return -1;

	//Init the game / application
	if (!g_App->InitApplication())
		return -2;

	//Enter loop. Loops until the engine decides it needs to quit (be it an error or 
	//whatever)
	g_App->EnterGameLoop();

	//Once game loop exits, shutdown the game followed by the engine & its subsystems
	if (!g_App->ShutdownApplication())
		return -3;
	if (!g_App->ShutdownEngine())
		return -4;

	//Done. No errors it seems
	return 0;
}
#endif