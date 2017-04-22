#include "RankSelectMenu.h"
#include "RankSelectMenuItem.h"
#include "SelectScene.h"
#include <STGEngine.h>
#include <Global.h>

RankSelectMenu::RankSelectMenu()
{
	auto assetManager = AssetManager::GetInstance();
	RankSelectMenuItem::texRank = assetManager->CreateTextureFromFile("res/menu/rank.png");
	RankSelectMenuItem::texRank->Retain();

	this->easy = new RankSelectMenuItem();
	this->easy->SetType(RankSelectMenuItem::EASY);
	AddMenuItem(this->easy);

	this->normal = new RankSelectMenuItem();
	this->normal->SetType(RankSelectMenuItem::NORMAL);
	AddMenuItem(this->normal);

	this->hard = new RankSelectMenuItem();
	this->hard->SetType(RankSelectMenuItem::HARD);
	AddMenuItem(this->hard);

	this->lunatic = new RankSelectMenuItem();
	this->lunatic->SetType(RankSelectMenuItem::LUNATIC);
	AddMenuItem(this->lunatic);
}

RankSelectMenu::~RankSelectMenu()
{
	TH_SAFE_RELEASE(RankSelectMenuItem::texRank);
}

void RankSelectMenu::OnMenuItemClicked(int item)
{
	Menu::OnMenuItemClicked(item);

	auto engine = STGEngine::GetInstance();
	auto global = Global::GetInstance();
		
	switch (item)
	{
	case 0:
		engine->SetDifficulty(STGEngine::EASY);
		break;
	case 1:
		engine->SetDifficulty(STGEngine::NORMAL);
		break;
	case 2:
		engine->SetDifficulty(STGEngine::HARD);
		break;
	case 3:
		engine->SetDifficulty(STGEngine::LUNATIC);
		break;
	}

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
	((SelectScene*)Game::GetInstance()->GetScene())->StartGame();
}

bool RankSelectMenu::OnKeyDown(EngineObject* sender, int key)
{
	if (key == 'x' || key == 'X' || key == VK_ESCAPE)
	{
		if (this->easy)
		{
			this->easy->Exit();
		}
		if (this->normal)
		{
			this->normal->Exit();
		}
		if (this->hard)
		{
			this->hard->Exit();
		}
		if (this->lunatic)
		{
			this->lunatic->Exit();
		}	

		this->easy = nullptr;
		this->normal = nullptr;
		this->hard = nullptr;
		this->lunatic = nullptr;

		EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
		((SelectScene*)Game::GetInstance()->GetScene())->Back();

		return true;
	}
	return Menu::OnKeyDown(sender, key);
}