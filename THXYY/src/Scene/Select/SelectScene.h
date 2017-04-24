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
	Layer* blackLayer = nullptr;
	RankSelectMenu* rankSelectMenu = nullptr;

	SelectTitle* title = nullptr;

	int frame = 0;
	int frame_nowLoading = 0;
	bool nowLoading = false;

public:
	SelectScene();
	virtual ~SelectScene();

	virtual void Update() override;
	virtual void OnStart() override;

	void ShowRank();
	void Back();
	void StartGame();
};

#endif