#pragma once

#include "PauseMenuItem.h"

class YesNoMenu : public Menu
{
private:
	PauseMenuItem* title = nullptr;

public:
	YesNoMenu();
	virtual ~YesNoMenu();

	virtual void OnStart() override;

	virtual bool OnKeyDown(EngineObject* sender, int key) override;

	virtual void OnMenuItemClicked(int index) override;

	void Enter();

	void Confirm();

	void Cancel();

	void Clear();
};