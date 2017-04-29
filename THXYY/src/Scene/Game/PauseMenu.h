#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "PauseMenuItem.h"

class PauseMenu : public Menu
{
private:
	Sprite* black = nullptr;
	PauseMenuItem* title = nullptr;

	enum State
	{
		PAUSE,
		GAME_OVER,
		REPLAY_OVER
	};

	State state = PAUSE;

public:
	PauseMenu();
	virtual ~PauseMenu();

	virtual bool OnKeyDown(EngineObject* sender, int key) override;
	virtual void OnLoad(AsyncInfo* info) override;
	virtual void OnStart() override;
	virtual void OnMenuItemClicked(int index) override;

	void DoPause();
	void DoResume();
	void DoGameOver();
	void DoRestart();

	void ReturnToTitle();

	void AskForConfirm();
	void ConfirmCanceled();
	void Confirmed();

	void Clear();
};

#endif