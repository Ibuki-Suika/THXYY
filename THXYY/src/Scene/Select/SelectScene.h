#ifndef SELECT_SCENE_H
#define SELECT_SCENE_H

#include <THEngine.h>

using namespace THEngine;

class SelectTitle;
class RankSelectMenu;

class SelectScene : public Scene
{
private:
	Ptr<Texture> texBackground;
	Ptr<Texture> texLoading;

	Ptr<Layer> bgrLayer;
	Ptr<Layer> blackLayer;
	Ptr<RankSelectMenu> rankSelectMenu;

	Ptr<SelectTitle> title;

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