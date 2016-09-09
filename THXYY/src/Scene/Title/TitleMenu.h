#ifndef TITLEMENU_H
#define TITLEMENU_H

#include <THEngine.h>

namespace THEngine
{
	class TitleMenu : public Menu	
	{
	protected:
		int itemCount;
		int currentItem;
		Texture* texMenuItem;
		Rect spriteRect[10][3];

	protected:
		virtual bool OnKeyDown(EngineObject* sender, int key) override;

	public:
		TitleMenu();
		virtual ~TitleMenu();

		virtual void Update() override;

		virtual void OnDestroy() override;

		virtual void OnMenuItemClicked(int item) override;
	};
}

#endif