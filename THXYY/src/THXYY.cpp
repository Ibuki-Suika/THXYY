#include "THXYY.h"
#include "Scene\Title\Title.h"
#include "resource.h"
#include <time.h>

THXYY::THXYY()
{
	engine = nullptr;
}

THXYY::~THXYY()
{
	TH_SAFE_RELEASE(engine);
}

bool THXYY::CreateGame(int width, int height, bool fullScreen)
{
	auto exceptionManager = ExceptionManager::GetInstance();

	if (Game::CreateGame(width, height, fullScreen, "THXYY", IDI_THXYY, IDI_SMALL) == false)
	{
		return false;
	}

	engine = STGEngine::Create();
	if (engine == nullptr)
	{
		return false;
	}
	engine->Retain();

	auto stgResources = STGResources::GetInstance();
	if (!stgResources->LoadSounds())
	{
		return false;
	}
	if (!stgResources->LoadTexTures())
	{
		return false;
	}

	auto global = Global::GetInstance();
	if (!global->Load())
	{
		return false;
	}

	Title* title = new Title();
	LoadScene(title);

	return true;
}

void THXYY::OnShutdown()
{
	TH_SAFE_RELEASE(engine);

	delete Global::GetInstance();

	Game::OnShutdown();
}