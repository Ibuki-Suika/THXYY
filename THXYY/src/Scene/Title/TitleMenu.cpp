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
}

TitleMenu::~TitleMenu()
{
}

void TitleMenu::OnStart()
{
	Menu::OnStart();

	AddMenuItem(Ptr<TitleMenuItem>::New(TitleMenuItem::GAME_START).Get());
	AddMenuItem(Ptr<TitleMenuItem>::New(TitleMenuItem::EXTRA_START).Get());
	AddMenuItem(Ptr<TitleMenuItem>::New(TitleMenuItem::PRACTICE_START).Get());
	AddMenuItem(Ptr<TitleMenuItem>::New(TitleMenuItem::SPELL_PRACTICE).Get());
	AddMenuItem(Ptr<TitleMenuItem>::New(TitleMenuItem::REPLAY).Get());
	AddMenuItem(Ptr<TitleMenuItem>::New(TitleMenuItem::PLAYER_DATA).Get());
	AddMenuItem(Ptr<TitleMenuItem>::New(TitleMenuItem::MUSIC_ROOM).Get());
	AddMenuItem(Ptr<TitleMenuItem>::New(TitleMenuItem::OPTION).Get());
	AddMenuItem(Ptr<TitleMenuItem>::New(TitleMenuItem::MANUAL).Get());
	AddMenuItem(Ptr<TitleMenuItem>::New(TitleMenuItem::QUIT).Get());

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->SetPosition(Vector3f(604, 340, 0));
		menuItem->SetAlpha(0);
		menuItem->AddTween(Ptr<MoveTo>::New(Vector3f(528, 278 - 24 * i, 0), GO_IN_TIME - 27 + 3 * i, Tweener::EASE_OUT).Get());
		menuItem->AddTween(Ptr<FadeTo>::New(1.0f, GO_IN_TIME - 27 + 3 * i, Tweener::EASE_OUT).Get());
	}

	auto stgResources = STGResources::GetInstance();

	SetSoundOK(stgResources->soundMenuOK);
	SetSoundSelect(stgResources->soundMenuSelect);

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
	Ptr<FrameTimer> timer = Ptr<FrameTimer>::New();
	timer->SetFrame(GO_IN_TIME);
	timer->run = [this]() {
		EventSystem::GetInstance()->RegisterKeyDownListener(this);
	};
	GetScheduler()->AddFrameTimer(timer);
}

bool TitleMenu::OnKeyDown(Ptr<EngineObject> sender, int key)
{
	return Menu::OnKeyDown(sender, key);
}

void TitleMenu::OnDestroy()
{
	Menu::OnDestroy();

	TitleMenuItem::texTitleMenu = nullptr;
}

void TitleMenu::Update()
{
	Layer::Update();
}

void TitleMenu::OnMenuItemClicked(int item)
{
	Menu::OnMenuItemClicked(item);

	Ptr<FrameTimer> timer = Ptr<FrameTimer>::New();
	timer->SetFrame(GO_OUT_TIME);

	switch (item)
	{
	case 0:
	{
		timer->run = []() {
			Game::GetInstance()->LoadScene(Ptr<SelectScene>::New().Get());
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
		item->AddTween(Ptr<MoveBy>::New(Vector3f(40, 0, 0), GO_OUT_TIME, Tweener::SIMPLE).Get());
		item->AddTween(Ptr<FadeOut>::New(GO_OUT_TIME, Tweener::SIMPLE).Get());
	}
}