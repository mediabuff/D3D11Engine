//D3D11Config.h
//Created 09/07/17
//Created By Daniel Bowler
//
//D3D11 specific config

#pragma once

//Global graphics settings
#include "GraphicsConfig.h"

#include <windows.h>
#include <stdio.h>

//Macro which will select the correct subclass to inherit from for graphics classes
#define RENDERING_PLATFORM_IMPLEMENTATION(TYPE) Platform::##D3D11##TYPE
#define RENDERING_PLATFORM_IMPLEMENTATION_CLASS_NAME(CLASS_NAME) D3D11##CLASS_NAME

//Macro which picks API specific version of the class TYPE
#define RENDERING_PLATFORM_CLASS(TYPE) D3D11##TYPE

//C-String representing the API being used
#define RENDERING_PLATFORM_API_STRING "D3D11"

//
//Helper macros
//
#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
#endif

#else
#ifndef HR
#define HR(x) (x)
#endif
#endif 

#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }
#define SafeDelete(x) { delete x; x = 0; }
