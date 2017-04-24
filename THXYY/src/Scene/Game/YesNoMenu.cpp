#include "YesNoMenu.h"
#include "GameScene.h"
#include "../../STGCore/STGResources.h"

YesNoMenu::YesNoMenu() : Menu(32, 16, 384, 448)
{
	auto stgResources = STGResources::GetInstance();

	SetSoundOK(stgResources->soundMenuOK);
	SetSoundSelect(stgResources->soundMenuSelect);
}

YesNoMenu::~YesNoMenu()
{
}

void YesNoMenu::OnStart()
{
	Menu::OnStart();

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

bool YesNoMenu::OnKeyDown(EngineObject* sender, int key)
{
	bool ret = Menu::OnKeyDown(sender, key);

	switch (key)
	{
	case VK_ESCAPE:
		Cancel();
		return true;
	}

	return ret;
}

void YesNoMenu::OnMenuItemClicked(int index)
{
	switch (index)
	{
	case 0:     //确认
		Confirm();
		break;
	case 1:     //取消
		Cancel();
		break;
	}
}

void YesNoMenu::Enter()
{
	title = new PauseMenuItem(PauseMenuItem::REALLY);
	title->SetPosition(Vector3f(250, 180, 5));
	title->SetAlpha(0.0f);
	title->AddTween(new MoveBy(Vector3f(-48.0f, 0.0f, 0.0f), 20, Tweener::EASE_OUT));
	title->AddTween(new FadeTo(1.0f, 20, Tweener::EASE_OUT));
	AddChild(title);

	AddMenuItem(new PauseMenuItem(PauseMenuItem::YES));
	AddMenuItem(new PauseMenuItem(PauseMenuItem::NO));

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->SetPosition(Vector3f(250, 130 - 32 * i, 5));
		menuItem->AddTween(new MoveBy(Vector3f(-45.0f, 0.0f, 0.0f), 20, Tweener::EASE_OUT));
		menuItem->AddTween(new FadeTo(1.0f, 20, Tweener::EASE_OUT));
	}

	EventSystem::GetInstance()->RegisterKeyDownListener(this);
}

void YesNoMenu::Confirm()
{
	((GameScene*)Game::GetInstance()->GetScene())->GetPauseMenu()->Confirmed();

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

void YesNoMenu::Clear()
{
	if (title)
	{
		title->MarkDestroy();
	}
	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->MarkDestroy();
	}
	ClearItems();

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

void YesNoMenu::Cancel()
{
	title->AddTween(new MoveBy(Vector3f(48.0f, 0.0f, 0.0f), 20, Tweener::EASE_OUT));
	title->AddTween(new FadeOut(20, Tweener::EASE_OUT));

	title = nullptr;

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->AddTween(new MoveBy(Vector3f(45.0f, 0.0f, 0.0f), 20, Tweener::EASE_OUT));
		menuItem->AddTween(new FadeOut(20, Tweener::EASE_OUT));
	}

	ClearItems();

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);

	((GameScene*)Game::GetInstance()->GetScene())->GetPauseMenu()->ConfirmCanceled();
}