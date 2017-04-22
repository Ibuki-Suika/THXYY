#include "TitleMenu.h"
#include "../Game/GameScene.h"
#include "../Select/SelectScene.h"
#include "../../STGCore/STGCore.h"
#include "TitleMenuItem.h"

using namespace THEngine;

TitleMenu::TitleMenu() : Menu(464, 216, 128, 248)
{
	currentItem = 0;
	itemCount = 10;

	TitleMenuItem::texTitleMenu = AssetManager::GetInstance()->CreateTextureFromFile("res/title/main_menu.png");
	TitleMenuItem::texTitleMenu->Retain();

	TitleMenuItem* menuItem = new TitleMenuItem(TitleMenuItem::GAME_START);
	menuItem->SetPosition(Vector3f(64, 232, 0));
	AddMenuItem(menuItem);

	menuItem = new TitleMenuItem(TitleMenuItem::EXTRA_START);
	menuItem->SetPosition(Vector3f(64, 208, 0));
	AddMenuItem(menuItem);

	menuItem = new TitleMenuItem(TitleMenuItem::PRACTICE_START);
	menuItem->SetPosition(Vector3f(64, 184, 0));
	AddMenuItem(menuItem);

	menuItem = new TitleMenuItem(TitleMenuItem::SPELL_PRACTICE);
	menuItem->SetPosition(Vector3f(64, 160, 0));
	AddMenuItem(menuItem);

	menuItem = new TitleMenuItem(TitleMenuItem::REPLAY);
	menuItem->SetPosition(Vector3f(64, 136, 0));
	AddMenuItem(menuItem);

	menuItem = new TitleMenuItem(TitleMenuItem::PLAYER_DATA);
	menuItem->SetPosition(Vector3f(64, 112, 0));
	AddMenuItem(menuItem);

	menuItem = new TitleMenuItem(TitleMenuItem::MUSIC_ROOM);
	menuItem->SetPosition(Vector3f(64, 88, 0));
	AddMenuItem(menuItem);

	menuItem = new TitleMenuItem(TitleMenuItem::OPTION);
	menuItem->SetPosition(Vector3f(64, 64, 0));
	AddMenuItem(menuItem);

	menuItem = new TitleMenuItem(TitleMenuItem::MANUAL);
	menuItem->SetPosition(Vector3f(64, 40, 0));
	AddMenuItem(menuItem);

	menuItem = new TitleMenuItem(TitleMenuItem::QUIT);
	menuItem->SetPosition(Vector3f(64, 16, 0));
	AddMenuItem(menuItem);

	auto stgResources = STGResources::GetInstance();

	SetSoundOK(stgResources->soundMenuOK);
	SetSoundSelect(stgResources->soundMenuSelect);
}

TitleMenu::~TitleMenu()
{
	
}

bool TitleMenu::OnKeyDown(EngineObject* sender, int key)
{
	return Menu::OnKeyDown(sender, key);
}

void TitleMenu::OnDestroy()
{
	Menu::OnDestroy();

	TH_SAFE_RELEASE(TitleMenuItem::texTitleMenu);
}

void TitleMenu::Update()
{
	Layer::Update();
}

void TitleMenu::OnMenuItemClicked(int item)
{
	Menu::OnMenuItemClicked(item);

	switch (item)
	{
	case 0:
	{
		/*auto engine = STGEngine::GetInstance();

		engine->Init();

		auto global = Global::GetInstance();
		global->stageEnum = Global::STAGE_01;
		global->playerEnum = Global::REIMU;

		GameScene* scene = new GameScene();
		Game::GetInstance()->LoadScene(scene);*/

		Game::GetInstance()->LoadScene(new SelectScene());

		break;
	}
	case 9:
		Game::GetInstance()->Quit();
	}
}