#include "THXYY.h"
#include "GameConfig.h"
#include <STGCore.h>
#include "..\Scene\Title\Title.h"
#include "..\resource.h"
#include <time.h>

THXYY::THXYY()
{
	engine = nullptr;
}

THXYY::~THXYY()
{
	TH_SAFE_RELEASE(engine);
}

bool THXYY::CreateGame(const GameConfig& config)
{
	auto exceptionManager = ExceptionManager::GetInstance();

	Config conf;
	config.GetConfig(&conf);
	if (Game::CreateGame(conf, IDI_THXYY, IDI_SMALL) == false)
	{
		return false;
	}

	if (config.useVSync == false)
	{
		switch (config.drawInterval)
		{
		case GameConfig::DrawInterval::ONE:
			break;
		case GameConfig::DrawInterval::HALF:
			SetSpeed(2.0f);
			break;
		case GameConfig::DrawInterval::ONE_THIRD:
			SetSpeed(3.0f);
			break;
		default:
			throw std::logic_error("not implemented");
		}
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