#ifndef RANK_SELECT_MENU_H
#define RANK_SELECT_MENU_H

#include <THEngine.h>

using namespace THEngine;

class RankSelectMenuItem;

class RankSelectMenu : public Menu
{
private:
	Ptr<RankSelectMenuItem> easy;
	Ptr<RankSelectMenuItem> normal;
	Ptr<RankSelectMenuItem> hard;
	Ptr<RankSelectMenuItem> lunatic;

public:
	RankSelectMenu();
	virtual ~RankSelectMenu();

	virtual void OnMenuItemClicked(int item) override;

	virtual bool OnKeyDown(Ptr<EngineObject> sender, int key) override;
};

#endif