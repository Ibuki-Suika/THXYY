#include "PauseMenu.h"
#include "../../STGCore/STGCore.h"
#include "../Title/Title.h"

static const int FADE_TIME = 30;

PauseMenu::PauseMenu() : Menu(32, 16, 384, 448)
{
	PauseMenuItem::texPauseMenu = AssetManager::GetInstance()->CreateTextureFromFile("res/menu/pause_menu.png");
	PauseMenuItem::texPauseMenu->Retain();

	auto stgResources = STGResources::GetInstance();

	SetSoundOK(stgResources->soundMenuOK);
	SetSoundSelect(stgResources->soundMenuSelect);
}

PauseMenu::~PauseMenu()
{
	TH_SAFE_RELEASE(PauseMenuItem::texPauseMenu);
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
	black = new Sprite();
	black->SetTexture(global->texBlack);
	black->SetPosition(Vector3f(192, 224, 10));
	black->SetAlpha(0);
	black->AddTween(new FadeTo(0.75f, FADE_TIME, Tweener::EASE_OUT));
	AddChild(black);

	title = new PauseMenuItem(PauseMenuItem::PAUSE);
	title->SetPosition(Vector3f(-140, 440, 5));
	title->SetAlpha(0);
	title->AddTween(new MoveBy(Vector3f(140, -235, 5), FADE_TIME, Tweener::EASE_OUT));
	title->AddTween(new FadeTo(1.0f, FADE_TIME, Tweener::EASE_OUT));
	AddChild(title);

	AddMenuItem(new PauseMenuItem(PauseMenuItem::RESUME));
	AddMenuItem(new PauseMenuItem(PauseMenuItem::RETURN_TO_TITLE));
	AddMenuItem(new PauseMenuItem(PauseMenuItem::SAVE_REPLAY));
	AddMenuItem(new PauseMenuItem(PauseMenuItem::RETRY));

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->SetPosition(Vector3f(-140, 440, 5));
		menuItem->SetAlpha(0);
		menuItem->AddTween(new MoveBy(Vector3f(150, -285 - 32 * i, 0), FADE_TIME, Tweener::EASE_OUT));
		menuItem->AddTween(new FadeTo(1.0f, FADE_TIME, Tweener::EASE_OUT));
	}

	EventSystem::GetInstance()->RegisterKeyDownListener(this);
}

void PauseMenu::DoGameOver()
{
	state = GAME_OVER;

	auto global = Global::GetInstance();
	black = new Sprite();
	black->SetTexture(global->texBlack);
	black->SetPosition(Vector3f(192, 224, 10));
	black->SetAlpha(0);
	black->AddTween(new FadeTo(0.75f, FADE_TIME, Tweener::EASE_OUT));
	AddChild(black);

	title = new PauseMenuItem(PauseMenuItem::GAME_OVER);
	title->SetPosition(Vector3f(-140, 440, 5));
	title->SetAlpha(0);
	title->AddTween(new MoveBy(Vector3f(140, -235, 5), FADE_TIME, Tweener::EASE_OUT));
	title->AddTween(new FadeTo(1.0f, FADE_TIME, Tweener::EASE_OUT));
	AddChild(title);

	AddMenuItem(new PauseMenuItem(PauseMenuItem::CONTINUE));
	AddMenuItem(new PauseMenuItem(PauseMenuItem::RETURN_TO_TITLE));
	AddMenuItem(new PauseMenuItem(PauseMenuItem::SAVE_REPLAY));
	AddMenuItem(new PauseMenuItem(PauseMenuItem::RETRY));

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->SetPosition(Vector3f(-140, 440, 5));
		menuItem->SetAlpha(0);
		menuItem->AddTween(new MoveBy(Vector3f(150, -285 - 32 * i, 0), FADE_TIME, Tweener::EASE_OUT));
		menuItem->AddTween(new FadeTo(1.0f, FADE_TIME, Tweener::EASE_OUT));
	}

	EventSystem::GetInstance()->RegisterKeyDownListener(this);
}

void PauseMenu::DoResume()
{
	black->AddTween(new FadeOut(FADE_TIME, Tweener::EASE_OUT));

	black = nullptr;

	title->AddTween(new MoveTo(Vector3f(-140, 440, 5), FADE_TIME, Tweener::EASE_OUT));
	title->AddTween(new FadeOut(FADE_TIME, Tweener::EASE_OUT));

	title = nullptr;

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);

		menuItem->AddTween(new MoveTo(Vector3f(-140, 440, 5), FADE_TIME, Tweener::EASE_OUT));
		menuItem->AddTween(new FadeOut(FADE_TIME, Tweener::EASE_OUT));
	}

	ClearItems();

	((GameScene*)Game::GetInstance()->GetScene())->GetSTGLayer()->Resume();
	((GameScene*)Game::GetInstance()->GetScene())->GetSTGParticleLayer()->Resume();

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

void PauseMenu::DoRestart()
{
	auto engine = STGEngine::GetInstance();
	auto scene = (GameScene*)Game::GetInstance()->GetScene();
	scene->STGFadeOut(30);

	auto scheduler = scene->GetScheduler();
	FrameTimer* timer = new FrameTimer();
	timer->SetFrame(30);
	timer->run = [this, scene, engine]()
	{
		engine->Restart();
		scene->STGFadeIn(60);
		scene->GetSTGLayer()->Resume();
		scene->GetSTGParticleLayer()->Resume();
		Clear();
		Resume();
		scene->GetYesNoMenu()->Clear();
	};
	scheduler->AddTimer(timer);

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

void PauseMenu::ReturnToTitle()
{
	((GameScene*)Game::GetInstance()->GetScene())->ReturnToTitle();
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
	auto scene = (GameScene*)Game::GetInstance()->GetScene();

	scene->GetYesNoMenu()->Enter();

	Tween* tween = new FadeTo(0.2f, 20, Tweener::EASE_OUT);
	tween->onFinished = [this]() {this->Pause(); };
	title->AddTween(tween);
	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->AddTween(new FadeTo(0.2f, 20, Tweener::EASE_OUT));
	}

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

void PauseMenu::ConfirmCanceled()
{
	title->AddTween(new FadeTo(1.0f, 20, Tweener::EASE_OUT));
	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->AddTween(new FadeTo(1.0f, 20, Tweener::EASE_OUT));
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

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

bool PauseMenu::OnKeyDown(EngineObject* sender, int key)
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