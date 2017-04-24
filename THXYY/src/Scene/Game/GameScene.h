#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <THEngine.h>
#include "ScoreNumber.h"
#include "PowerNumber.h"
#include "PointNumber.h"
#include "GrazeNumber.h"
#include "STGLayer.h"
#include "STGParticleLayer.h"
#include "PauseMenu.h"
#include "YesNoMenu.h"

using namespace THEngine;

class GameScene : public Scene, public IKeyDownListener
{
private:
	const float SCORE_LEFT = 492.0f;
	const float POWER_LEFT = 530.0f;

	PauseMenu* pauseMenu = nullptr;
	YesNoMenu* yesNoMenu = nullptr;

	STGLayer* stgLayer = nullptr;
	STGParticleLayer* stgParticleLayer = nullptr;
	Layer* baseLayer = nullptr;
	Layer* blackLayer = nullptr;
	Layer* blackSTGLayer = nullptr;
	Layer* backgroundLayer = nullptr;

	Sprite* blackSTG = nullptr;

	Texture* texGameBg;
	Texture* texGameBg2;

	ScoreNumber* hiScore[10];
	ScoreNumber* score[10];

	Sprite* lifeSprite[8];
	Sprite* bombSprite[8];

	ArrayList<PointNumber*> pointSpriteList;
	ArrayList<GrazeNumber*> grazeSpriteList;

	PowerNumber* powerSprite[6];

public:
	GameScene();
	virtual ~GameScene();

	virtual void Update() override;
	virtual void Draw() override;

	virtual void OnLoad(AsyncInfo* info) override;
	virtual void OnStart() override;
	virtual void OnDestroy() override;

	virtual bool OnKeyDown(EngineObject* sender, int key) override;

	void UpdateScore();
	void UpdateLifeAndBomb();
	void UpdatePower();
	void DrawMaxPoint();
	void DrawGraze();
	void CreateScorePanel();
	void CreatePowerPanel();

	void ReturnToTitle();
	void STGFadeOut(int time);
	void STGFadeIn(int time);

	inline STGLayer* GetSTGLayer() { return stgLayer; }
	inline STGParticleLayer* GetSTGParticleLayer() { return stgParticleLayer; }
	inline Layer* GetBackgroundLayer() { return backgroundLayer; }
	inline PauseMenu* GetPauseMenu() { return pauseMenu; }
	inline YesNoMenu* GetYesNoMenu() { return yesNoMenu; }
};

#endif