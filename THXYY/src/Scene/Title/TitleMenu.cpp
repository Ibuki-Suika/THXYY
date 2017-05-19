#include "TitleMenu.h"
#include "../Game/GameScene.h"
#include "../Select/SelectScene.h"
#include "../../STGCore/STGCore.h"
#include "TitleMenuItem.h"

using namespace THEngine;

static const int GO_OUT_TIME = 24;
static const int GO_IN_TIME = 50;

TitleMenu::TitleMenu()
{
	TitleMenuItem::texTitleMenu = AssetManager::GetInstance()->CreateTextureFromFile("res/title/main_menu.png");
	TitleMenuItem::texTitleMenu->Retain();
}

TitleMenu::~TitleMenu()
{
}

void TitleMenu::OnStart()
{
	Menu::OnStart();

	AddMenuItem(new TitleMenuItem(TitleMenuItem::GAME_START));
	AddMenuItem(new TitleMenuItem(TitleMenuItem::EXTRA_START));
	AddMenuItem(new TitleMenuItem(TitleMenuItem::PRACTICE_START));
	AddMenuItem(new TitleMenuItem(TitleMenuItem::SPELL_PRACTICE));
	AddMenuItem(new TitleMenuItem(TitleMenuItem::REPLAY));
	AddMenuItem(new TitleMenuItem(TitleMenuItem::PLAYER_DATA));
	AddMenuItem(new TitleMenuItem(TitleMenuItem::MUSIC_ROOM));
	AddMenuItem(new TitleMenuItem(TitleMenuItem::OPTION));
	AddMenuItem(new TitleMenuItem(TitleMenuItem::MANUAL));
	AddMenuItem(new TitleMenuItem(TitleMenuItem::QUIT));

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->SetPosition(Vector3f(604, 340, 0));
		menuItem->SetAlpha(0);
		menuItem->AddTween(new MoveTo(Vector3f(528, 278 - 24 * i, 0), GO_IN_TIME - 27 + 3 * i, Tweener::EASE_OUT));
		menuItem->AddTween(new FadeTo(1.0f, GO_IN_TIME - 27 + 3 * i, Tweener::EASE_OUT));
	}

	auto stgResources = STGResources::GetInstance();

	SetSoundOK(stgResources->soundMenuOK);
	SetSoundSelect(stgResources->soundMenuSelect);

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
	FrameTimer* timer = new FrameTimer();
	timer->SetFrame(GO_IN_TIME);
	timer->run = [this]() {
		EventSystem::GetInstance()->RegisterKeyDownListener(this);
	};
	GetScheduler()->AddFrameTimer(timer);
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

	FrameTimer* timer = new FrameTimer();
	timer->SetFrame(GO_OUT_TIME);

	switch (item)
	{
	case 0:
	{
		timer->run = []() {
			Game::GetInstance()->LoadScene(new SelectScene());
		};
		break;
	}
	case 9:
		timer->run = []() {
			Game::GetInstance()->Quit();
		};
	}
	GetScheduler()->AddFrameTimer(timer);
	GoOut();
}

void TitleMenu::GoOut()
{
	for (auto iter = this->GetMenuItems()->GetIterator(); iter->HasNext();)
	{
		auto item = iter->Next();
		item->AddTween(new MoveBy(Vector3f(40, 0, 0), GO_OUT_TIME, Tweener::SIMPLE));
		item->AddTween(new FadeOut(GO_OUT_TIME, Tweener::SIMPLE));
	}
}