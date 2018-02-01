#include "RankSelectMenu.h"
#include "RankSelectMenuItem.h"
#include "SelectScene.h"
#include <STGEngine.h>
#include <Global.h>

RankSelectMenu::RankSelectMenu()
{
	auto assetManager = AssetManager::GetInstance();
	RankSelectMenuItem::texRank = assetManager->CreateTextureFromFile("res/menu/rank.png");

	this->easy = Ptr<RankSelectMenuItem>::New();
	this->easy->SetType(RankSelectMenuItem::EASY);
	AddMenuItem(this->easy.Get());

	this->normal = Ptr<RankSelectMenuItem>::New();
	this->normal->SetType(RankSelectMenuItem::NORMAL);
	AddMenuItem(this->normal.Get());

	this->hard = Ptr<RankSelectMenuItem>::New();
	this->hard->SetType(RankSelectMenuItem::HARD);
	AddMenuItem(this->hard.Get());

	this->lunatic = Ptr<RankSelectMenuItem>::New();
	this->lunatic->SetType(RankSelectMenuItem::LUNATIC);
	AddMenuItem(this->lunatic.Get());

	auto stgResources = STGResources::GetInstance();

	SetSoundOK(stgResources->soundMenuOK);
	SetSoundSelect(stgResources->soundMenuSelect);
}

RankSelectMenu::~RankSelectMenu()
{
	RankSelectMenuItem::texRank = nullptr;
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
	((SelectScene*)Game::GetInstance()->GetScene().Get())->StartGame();
}

bool RankSelectMenu::OnKeyDown(Ptr<EngineObject> sender, int key)
{
	if (key == 'x' || key == 'X' || key == VK_ESCAPE)
	{
		if (this->easy != nullptr)
		{
			this->easy->Exit();
		}
		if (this->normal != nullptr)
		{
			this->normal->Exit();
		}
		if (this->hard != nullptr)
		{
			this->hard->Exit();
		}
		if (this->lunatic != nullptr)
		{
			this->lunatic->Exit();
		}

		this->easy = nullptr;
		this->normal = nullptr;
		this->hard = nullptr;
		this->lunatic = nullptr;

		EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
		((SelectScene*)Game::GetInstance()->GetScene().Get())->Back();

		return true;
	}
	return Menu::OnKeyDown(sender, key);
}