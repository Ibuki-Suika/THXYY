#include "SelectScene.h"
#include "SelectTitle.h"
#include "RankSelectMenu.h"
#include "../Title/Title.h"
#include <Global.h>
#include <STGEngine.h>

static const int FADE_TIME = 24;
static const int OFFSET = 60;
static const int DELAY_TIME = 150;
static const int GO_TO_NEXT_SCENE_TIME = 45;

SelectScene::SelectScene()
{
	auto assetManager = AssetManager::GetInstance();
	this->texBackground = assetManager->CreateTextureFromFile("res/menu/background.jpg");
	this->texBackground->Retain();

	this->texLoading = assetManager->CreateTextureFromFile("res/loading/loading.png");
	this->texLoading->Retain();

	SelectTitle::tex = assetManager->CreateTextureFromFile("res/menu/select.png");
	SelectTitle::tex->Retain();

	this->bgrLayer = new Layer();
	AddLayer(this->bgrLayer);

	Sprite* background = new Sprite();
	background->SetTexture(this->texBackground);
	background->SetPosition(Vector3f(320, 240, 100));
	TweenSequence* sequence = new TweenSequence();
	sequence->AddTween(new Delay(DELAY_TIME));
	sequence->AddTween(new ColorTo(Vector3f(0.6f, 0.6f, 0.6f), 100, Tweener::SIMPLE));
	sequence->AddTween(new Delay(DELAY_TIME));
	sequence->AddTween(new ColorTo(Vector3f(1.0f, 1.0f, 1.0f), 100, Tweener::SIMPLE));
	sequence->SetLooped(true);
	background->AddTween(sequence);
	bgrLayer->AddChild(background);

	ShowRank();
}

SelectScene::~SelectScene()
{
	TH_SAFE_RELEASE(this->texBackground);
	TH_SAFE_RELEASE(this->texLoading);
	TH_SAFE_RELEASE(SelectTitle::tex);
}

void SelectScene::ShowRank()
{
	this->title = new SelectTitle();
	this->title->SetType(SelectTitle::RANK_SELECT);
	this->title->SetPosition(Vector3f(480 + OFFSET, 416, 25));
	title->SetAlpha(0.0f);
	this->title->AddTween(new MoveTo(Vector3f(480, 416, 25), FADE_TIME, Tweener::SIMPLE));
	this->title->AddTween(new FadeTo(1.0f, FADE_TIME, Tweener::SIMPLE));
	this->bgrLayer->AddChild(this->title);

	this->rankSelectMenu = new RankSelectMenu();
	AddLayer(this->rankSelectMenu);
}

void SelectScene::Back()
{
	this->title->AddTween(new MoveTo(Vector3f(480 + OFFSET, 416, 25), FADE_TIME, Tweener::SIMPLE));
	this->title->AddTween(new FadeOut(FADE_TIME, Tweener::SIMPLE));
	
	FrameTimer* timer = new FrameTimer();
	timer->SetFrame(FADE_TIME);
	timer->run = []() {
		auto game = Game::GetInstance();
		game->LoadScene(new Title());
	};
	GetScheduler()->AddTimer(timer);
}

void SelectScene::StartGame()
{
	Layer* blackLayer = new Layer();
	AddLayer(blackLayer);

	Sprite* black = new Sprite();
	black->SetPosition(Vector3f(320, 240, 100));
	black->SetTexture(Global::GetInstance()->texBlack);
	black->SetAlpha(0);
	black->AddTween(new FadeTo(1.0f, GO_TO_NEXT_SCENE_TIME, Tweener::SIMPLE));
	blackLayer->AddChild(black);

	Sprite* loading = new Sprite();
	loading->SetPosition(Vector3f(544, 80, 0));
	loading->SetTexture(this->texLoading);
	loading->SetTexRect(Rect(0, 256, 0, 96));
	loading->SetAlpha(0.0f);
	TweenSequence* sequence = new TweenSequence();
	sequence->AddTween(new ColorTo(Vector3f(0.5f, 0.5f, 0.5f), 18, Tweener::SIMPLE));
	sequence->AddTween(new ColorTo(Vector3f(1.0f, 1.0f, 1.0f), 18, Tweener::SIMPLE));
	sequence->SetLooped(true);
	loading->AddTween(sequence);
	loading->AddTween(new FadeTo(1.0f, 18, Tweener::SIMPLE));
	blackLayer->AddChild(loading);

	/*FrameTimer* timer = new FrameTimer();
	timer->SetFrame(GO_TO_NEXT_SCENE_TIME);
	timer->run = []() {
		auto engine = STGEngine::GetInstance();
		auto global = Global::GetInstance();

		engine->Init();
		global->stageEnum = Global::STAGE_01;
		global->playerEnum = Global::REIMU;
		GameScene* scene = new GameScene();
		Game::GetInstance()->LoadScene(scene);
	};
	GetScheduler()->AddTimer(timer);*/
}