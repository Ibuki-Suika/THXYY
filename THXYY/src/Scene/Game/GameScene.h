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

	Ptr<PauseMenu> pauseMenu;
	Ptr<YesNoMenu> yesNoMenu;

	Ptr<STGLayer> stgLayer;
	Ptr<STGParticleLayer> stgParticleLayer;
	Ptr<Layer> baseLayer;
	Ptr<Layer> blackLayer;
	Ptr<Layer> blackSTGLayer;
	Ptr<Layer> backgroundLayer;

	Ptr<Sprite> blackSTG;
	Ptr<Sprite> difficulty;

	Ptr<Texture> texGameBg;
	Ptr<Texture> texGameBg2;
	Ptr<Texture> texFront;

	Ptr<ScoreNumber> hiScore[10];
	Ptr<ScoreNumber> score[10];

	Ptr<Sprite> lifeSprite[8];
	Ptr<Sprite> bombSprite[8];

	ArrayList<Ptr<PointNumber>> pointSpriteList;
	ArrayList<Ptr<GrazeNumber>> grazeSpriteList;

	Ptr<PowerNumber> powerSprite[6];

private:
	void CreateFront();
	void UpdateScore();
	void UpdateLifeAndBomb();
	void UpdatePower();
	void DrawMaxPoint();
	void DrawGraze();
	void CreateScorePanel();
	void CreatePowerPanel();
	void DrawNewGameItems();
	bool IsNewGame();
	bool IsFirstStage();

public:
	GameScene();
	virtual ~GameScene();

	virtual void Update() override;
	virtual void Draw() override;

	virtual void OnLoad(Ptr<AsyncInfo> info) override;
	virtual void OnStart() override;
	virtual void OnDestroy() override;

	virtual bool OnKeyDown(Ptr<EngineObject> sender, int key) override;

	void ReturnToTitle();
	void Restart();
	void StartStage();
	void STGFadeOut(int time);
	void STGFadeIn(int time);

	inline Ptr<STGLayer> GetSTGLayer() { return stgLayer; }
	inline Ptr<STGParticleLayer> GetSTGParticleLayer() { return stgParticleLayer; }
	inline Ptr<Layer> GetBackgroundLayer() { return backgroundLayer; }
	inline Ptr<PauseMenu> GetPauseMenu() { return pauseMenu; }
	inline Ptr<YesNoMenu> GetYesNoMenu() { return yesNoMenu; }
};

#endif