#ifndef SELECT_SCENE_H
#define SELECT_SCENE_H

#include <THEngine.h>

using namespace THEngine;

class SelectTitle;
class RankSelectMenu;

class SelectScene : public Scene
{
private:
	Texture* texBackground = nullptr;
	Texture* texLoading = nullptr;

	Layer* bgrLayer = nullptr;
	RankSelectMenu* rankSelectMenu = nullptr;

	SelectTitle* title = nullptr;

public:
	SelectScene();
	virtual ~SelectScene();

	void ShowRank();
	void Back();
	void StartGame();
};

#endif