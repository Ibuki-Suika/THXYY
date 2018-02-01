#include "PauseMenu.h"
#include "../../STGCore/STGCore.h"
#include "../Title/Title.h"

static const int FADE_TIME = 30;

PauseMenu::PauseMenu() : Menu(32, 16, 384, 448)
{
	auto stgResources = STGResources::GetInstance();

	SetSoundOK(stgResources->soundMenuOK);
	SetSoundSelect(stgResources->soundMenuSelect);
}

PauseMenu::~PauseMenu()
{
	PauseMenuItem::texPauseMenu = nullptr;
}

void PauseMenu::OnLoad(Ptr<AsyncInfo> info)
{
	PauseMenuItem::texPauseMenu = AssetManager::GetInstance()->CreateTextureFromFile("res/menu/pause_menu.png");
}

void PauseMenu::OnStart()
{
	Menu::OnStart();

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

void PauseMenu::DoPause()
{
	state = PAUSE;

	auto global = Global::GetInstance();
	black = Ptr<Sprite>::New();
	black->SetTexture(global->texBlack);
	black->SetPosition(Vector3f(192, 224, 10));
	black->SetAlpha(0);
	black->AddTween(Ptr<FadeTo>::New(0.75f, FADE_TIME, Tweener::EASE_OUT).Get());
	AddChild(black.Get());

	title = Ptr<PauseMenuItem>::New(PauseMenuItem::PAUSE);
	title->SetPosition(Vector3f(-140, 440, 5));
	title->SetAlpha(0);
	title->AddTween(Ptr<MoveBy>::New(Vector3f(140, -235, 0), FADE_TIME, Tweener::EASE_OUT).Get());
	title->AddTween(Ptr<FadeTo>::New(1.0f, FADE_TIME, Tweener::EASE_OUT).Get());
	AddChild(title.Get());

	AddMenuItem(Ptr<PauseMenuItem>::New(PauseMenuItem::RESUME).Get());
	AddMenuItem(Ptr<PauseMenuItem>::New(PauseMenuItem::RETURN_TO_TITLE).Get());
	AddMenuItem(Ptr<PauseMenuItem>::New(PauseMenuItem::SAVE_REPLAY).Get());
	AddMenuItem(Ptr<PauseMenuItem>::New(PauseMenuItem::RETRY).Get());

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->SetPosition(Vector3f(-140, 440, 5));
		menuItem->SetAlpha(0);
		menuItem->AddTween(Ptr<MoveBy>::New(Vector3f(150, -285 - 32 * i, 0), FADE_TIME, Tweener::EASE_OUT).Get());
		menuItem->AddTween(Ptr<FadeTo>::New(1.0f, FADE_TIME, Tweener::EASE_OUT).Get());
	}

	EventSystem::GetInstance()->RegisterKeyDownListener(this);
}

void PauseMenu::DoGameOver()
{
	state = GAME_OVER;

	auto global = Global::GetInstance();
	black = Ptr<Sprite>::New();
	black->SetTexture(global->texBlack);
	black->SetPosition(Vector3f(192, 224, 10));
	black->SetAlpha(0);
	black->AddTween(Ptr<FadeTo>::New(0.75f, FADE_TIME, Tweener::EASE_OUT).Get());
	AddChild(black.Get());

	title = Ptr<PauseMenuItem>::New(PauseMenuItem::GAME_OVER);
	title->SetPosition(Vector3f(-140, 440, 5));
	title->SetAlpha(0);
	title->AddTween(Ptr<MoveBy>::New(Vector3f(140, -235, 0), FADE_TIME, Tweener::EASE_OUT).Get());
	title->AddTween(Ptr<FadeTo>::New(1.0f, FADE_TIME, Tweener::EASE_OUT).Get());
	AddChild(title.Get());

	AddMenuItem(Ptr<PauseMenuItem>::New(PauseMenuItem::CONTINUE).Get());
	AddMenuItem(Ptr<PauseMenuItem>::New(PauseMenuItem::RETURN_TO_TITLE).Get());
	AddMenuItem(Ptr<PauseMenuItem>::New(PauseMenuItem::SAVE_REPLAY).Get());
	AddMenuItem(Ptr<PauseMenuItem>::New(PauseMenuItem::RETRY).Get());

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->SetPosition(Vector3f(-140, 440, 5));
		menuItem->SetAlpha(0);
		menuItem->AddTween(Ptr<MoveBy>::New(Vector3f(150, -285 - 32 * i, 0), FADE_TIME, Tweener::EASE_OUT).Get());
		menuItem->AddTween(Ptr<FadeTo>::New(1.0f, FADE_TIME, Tweener::EASE_OUT).Get());
	}

	EventSystem::GetInstance()->RegisterKeyDownListener(this);
}

void PauseMenu::DoResume()
{
	if (black)
		black->AddTween(Ptr<FadeOut>::New(FADE_TIME, Tweener::EASE_OUT).Get());

	black = nullptr;

	title->AddTween(Ptr<MoveTo>::New(Vector3f(-140, 440, 5), FADE_TIME, Tweener::EASE_OUT).Get());
	title->AddTween(Ptr<FadeOut>::New(FADE_TIME, Tweener::EASE_OUT).Get());

	title = nullptr;

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);

		menuItem->AddTween(Ptr<MoveTo>::New(Vector3f(-140, 440, 5), FADE_TIME, Tweener::EASE_OUT).Get());
		menuItem->AddTween(Ptr<FadeOut>::New(FADE_TIME, Tweener::EASE_OUT).Get());
	}

	ClearItems();

	((GameScene*)Game::GetInstance()->GetScene().Get())->GetSTGLayer()->Resume();
	((GameScene*)Game::GetInstance()->GetScene().Get())->GetSTGParticleLayer()->Resume();

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

void PauseMenu::DoRestart()
{
	auto engine = STGEngine::GetInstance();
	auto scene = (GameScene*)Game::GetInstance()->GetScene().Get();
	scene->STGFadeOut(30);

	auto scheduler = scene->GetScheduler();
	Ptr<FrameTimer> timer = Ptr<FrameTimer>::New();
	timer->SetFrame(30);
	timer->run = [this, scene, engine]()
	{
		scene->Restart();
		Clear();
		Resume();
	};
	scheduler->AddFrameTimer(timer);

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

void PauseMenu::ReturnToTitle()
{
	((GameScene*)Game::GetInstance()->GetScene().Get())->ReturnToTitle();
}

void PauseMenu::OnMenuItemClicked(int index)
{
	Menu::OnMenuItemClicked(index);

	switch (state)
	{
	case PAUSE:
		switch (index)
		{
		case 0:    //返回游戏
			DoResume();
			break;
		case 1:   //返回标题菜单
		case 2:   //保存录像
		case 3:   //重新开始
			AskForConfirm();
			break;
		}
		break;
	case GAME_OVER:
		switch (index)
		{
		case 0:    //继续游戏
			break;
		case 1:   //返回标题菜单
		case 2:   //保存录像
		case 3:   //重新开始
			AskForConfirm();
			break;
		}
	}
}

void PauseMenu::AskForConfirm()
{
	auto scene = (GameScene*)Game::GetInstance()->GetScene().Get();

	scene->GetYesNoMenu()->Enter();

	Ptr<Tween> tween = Ptr<FadeTo>::New(0.2f, 20, Tweener::EASE_OUT).Get();
	tween->onFinished = [this]() {this->Pause(); };
	title->AddTween(tween);
	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->AddTween(Ptr<FadeTo>::New(0.2f, 20, Tweener::EASE_OUT).Get());
	}

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

void PauseMenu::ConfirmCanceled()
{
	title->AddTween(Ptr<FadeTo>::New(1.0f, 20, Tweener::EASE_OUT).Get());
	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->AddTween(Ptr<FadeTo>::New(1.0f, 20, Tweener::EASE_OUT).Get());
	}

	Resume();

	EventSystem::GetInstance()->RegisterKeyDownListener(this);
}

void PauseMenu::Confirmed()
{
	switch (state)
	{
	case PAUSE:
	case GAME_OVER:
		switch (currentSelection)
		{
		case 1:      //返回标题菜单
			ReturnToTitle();
			break;
		case 2:      //保存录像
			break;
		case 3:      //重新开始
			DoRestart();
			break;
		}
	}
}

void PauseMenu::Clear()
{
	title->MarkDestroy();
	black->MarkDestroy();
	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->MarkDestroy();
	}
	ClearItems();
	title = nullptr;
	black = nullptr;
	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

bool PauseMenu::OnKeyDown(Ptr<EngineObject> sender, int key)
{
	bool ret = Menu::OnKeyDown(sender, key);

	switch (key)
	{
	case VK_ESCAPE:
		if (state != GAME_OVER)
		{
			DoResume();
			return true;
		}
		break;
	case 'R':
		if (state != REPLAY_OVER)
		{
			DoRestart();
			return true;
		}
		break;
	}

	return ret;
}