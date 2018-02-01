#ifndef TITLEMENU_H
#define TITLEMENU_H

#include <THEngine.h>

using namespace THEngine;

class TitleMenu : public Menu
{
protected:
	int itemCount;
	int currentItem;
	Ptr<Texture> texMenuItem;
	Rect spriteRect[10][3];

protected:
	virtual bool OnKeyDown(Ptr<EngineObject> sender, int key) override;

public:
	TitleMenu();
	virtual ~TitleMenu();

	virtual void Update() override;

	virtual void OnDestroy() override;

	virtual void OnMenuItemClicked(int item) override;

	virtual void OnStart() override;

	void GoOut();
};

#endif