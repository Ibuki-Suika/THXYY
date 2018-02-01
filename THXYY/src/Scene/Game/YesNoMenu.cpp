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

bool YesNoMenu::OnKeyDown(Ptr<EngineObject> sender, int key)
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
	title = Ptr<PauseMenuItem>::New(PauseMenuItem::REALLY);
	title->SetPosition(Vector3f(250, 180, 5));
	title->SetAlpha(0.0f);
	title->AddTween(Ptr<MoveBy>::New(Vector3f(-48.0f, 0.0f, 0.0f), 20, Tweener::EASE_OUT).Get());
	title->AddTween(Ptr<FadeTo>::New(1.0f, 20, Tweener::EASE_OUT).Get());
	AddChild(title.Get());

	AddMenuItem(Ptr<PauseMenuItem>::New(PauseMenuItem::YES).Get());
	AddMenuItem(Ptr<PauseMenuItem>::New(PauseMenuItem::NO).Get());

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->SetPosition(Vector3f(250, 130 - 32 * i, 5));
		menuItem->AddTween(Ptr<MoveBy>::New(Vector3f(-45.0f, 0.0f, 0.0f), 20, Tweener::EASE_OUT).Get());
		menuItem->AddTween(Ptr<FadeTo>::New(1.0f, 20, Tweener::EASE_OUT).Get());
	}

	EventSystem::GetInstance()->RegisterKeyDownListener(this);
}

void YesNoMenu::Confirm()
{
	((GameScene*)Game::GetInstance()->GetScene().Get())->GetPauseMenu()->Confirmed();

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

void YesNoMenu::Clear()
{
	if (title != nullptr)
	{
		title->MarkDestroy();
	}
	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->MarkDestroy();
	}
	ClearItems();
	title = nullptr;
	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

void YesNoMenu::Cancel()
{
	title->AddTween(Ptr<MoveBy>::New(Vector3f(48.0f, 0.0f, 0.0f), 20, Tweener::EASE_OUT).Get());
	title->AddTween(Ptr<FadeOut>::New(20, Tweener::EASE_OUT).Get());

	title = nullptr;

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->AddTween(Ptr<MoveBy>::New(Vector3f(45.0f, 0.0f, 0.0f), 20, Tweener::EASE_OUT).Get());
		menuItem->AddTween(Ptr<FadeOut>::New(20, Tweener::EASE_OUT).Get());
	}

	ClearItems();

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);

	((GameScene*)Game::GetInstance()->GetScene().Get())->GetPauseMenu()->ConfirmCanceled();
}