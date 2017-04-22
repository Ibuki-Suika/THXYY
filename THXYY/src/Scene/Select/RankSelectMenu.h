#ifndef RANK_SELECT_MENU_H
#define RANK_SELECT_MENU_H

#include <THEngine.h>

using namespace THEngine;

class RankSelectMenuItem;

class RankSelectMenu : public Menu
{
private:
	RankSelectMenuItem* easy = nullptr;
	RankSelectMenuItem* normal = nullptr;
	RankSelectMenuItem* hard = nullptr;
	RankSelectMenuItem* lunatic = nullptr;

public:
	RankSelectMenu();
	virtual ~RankSelectMenu();

	virtual void OnMenuItemClicked(int item) override;

	virtual bool OnKeyDown(EngineObject* sender, int key) override;
};

#endif