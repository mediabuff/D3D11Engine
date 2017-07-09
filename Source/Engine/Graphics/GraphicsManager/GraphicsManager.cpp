#include "GraphicsManager.h"

using namespace EngineAPI::Graphics;

//Init static data
GraphicsManager* GraphicsManager::instance = nullptr;

GraphicsManager* GraphicsManager::GetInstance()
{
	if (!instance)
		instance = GE_NEW GraphicsManager();
	return instance;
}

void GraphicsManager::DestroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}