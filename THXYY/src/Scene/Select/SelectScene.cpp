#include "SelectScene.h"
#include "SelectTitle.h"
#include "RankSelectMenu.h"
#include "StarParticle.h"
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

	this->texLoading = assetManager->CreateTextureFromFile("res/loading/loading.png");
	StarParticle::tex = this->texLoading;

	SelectTitle::tex = assetManager->CreateTextureFromFile("res/menu/select.png");

	this->bgrLayer = Ptr<Layer>::New();
	AddLayer(this->bgrLayer);

	Ptr<Sprite> background = Ptr<Sprite>::New();
	background->SetTexture(this->texBackground);
	background->SetPosition(Vector3f(320, 240, 100));
	Ptr<TweenSequence> sequence = Ptr<TweenSequence>::New();
	sequence->AddTween(Ptr<Delay>::New(DELAY_TIME).Get());
	sequence->AddTween(Ptr<ColorTo>::New(Vector3f(0.6f, 0.6f, 0.6f), 100, Tweener::SIMPLE).Get());
	sequence->AddTween(Ptr<Delay>::New(DELAY_TIME).Get());
	sequence->AddTween(Ptr<ColorTo>::New(Vector3f(1.0f, 1.0f, 1.0f), 100, Tweener::SIMPLE).Get());
	sequence->SetLooped(true);
	background->AddTween(sequence.Get());
	bgrLayer->AddChild(background.Get());
}

SelectScene::~SelectScene()
{
	SelectTitle::tex = nullptr;
	StarParticle::tex = nullptr;
}

void SelectScene::OnStart()
{
	Scene::OnStart();

	ShowRank();

	for (int i = 0; i < 10; i++)
	{
		Ptr<StarParticle> particle = Ptr<StarParticle>::New();
		this->bgrLayer->AddChild(particle.Get());
	}
}

void SelectScene::Update()
{
	Scene::Update();

	frame++;
	if (frame == 8)
	{
		frame = 0;
		Ptr<StarParticle> particle = Ptr<StarParticle>::New();
		this->bgrLayer->AddChild(particle.Get());
	}

	if (nowLoading)
	{
		frame_nowLoading++;
		if (frame_nowLoading == 4)
		{
			frame_nowLoading = 0;
			Ptr<Particle3D> particle = Ptr<Particle3D>::New();
			particle->SetTexture(this->texLoading);
			particle->SetTexRect(Rect(32, 64, 96, 128));
			particle->SetPosition(Vector3f(Math::Random(416, 640), 128, 50));
			particle->SetSpeed(1.0f + Math::Random(0, 200) / 100.0f);
			particle->SetLife(30);
			particle->SetRotatingAxis(Vector3f(0, 0, 1));
			particle->SetAlpha(0);
			particle->SetRotatingSpeed(Math::Random(100, 800) / 100.0f);

			float scale = Math::Random(50, 100) / 100.0f;
			particle->SetScale(Vector3f(scale, scale, 1));
			float rad = Math::ToRad(Math::Random(0, 90) + 225);
			particle->SetDirection(Vector3f(cos(rad), sin(rad), 0));

			Ptr<TweenSequence> sequence = Ptr<TweenSequence>::New();
			sequence->AddTween(Ptr<FadeTo>::New(0.8f, 10, Tweener::EASE_OUT).Get());
			sequence->AddTween(Ptr<Delay>::New(10).Get());
			sequence->AddTween(Ptr<FadeOut>::New(10, Tweener::EASE_OUT).Get());
			particle->AddTween(sequence.Get());

			this->blackLayer->AddChild(particle.Get());
		}
	}
}

void SelectScene::ShowRank()
{
	this->title = Ptr<SelectTitle>::New();
	this->title->SetType(SelectTitle::RANK_SELECT);
	this->title->SetPosition(Vector3f(480 + OFFSET, 416, 25));
	title->SetAlpha(0.0f);
	this->title->AddTween(Ptr<MoveTo>::New(Vector3f(480, 416, 25), FADE_TIME, Tweener::SIMPLE).Get());
	this->title->AddTween(Ptr<FadeTo>::New(1.0f, FADE_TIME, Tweener::SIMPLE).Get());
	this->bgrLayer->AddChild(this->title.Get());

	this->rankSelectMenu = Ptr<RankSelectMenu>::New();
	AddLayer(this->rankSelectMenu.Get());
}

void SelectScene::Back()
{
	this->title->AddTween(Ptr<MoveTo>::New(Vector3f(480 + OFFSET, 416, 25), FADE_TIME, Tweener::SIMPLE).Get());
	this->title->AddTween(Ptr<FadeOut>::New(FADE_TIME, Tweener::SIMPLE).Get());

	Ptr<FrameTimer> timer = Ptr<FrameTimer>::New();
	timer->SetFrame(FADE_TIME);
	timer->run = []() {
		auto game = Game::GetInstance();
		Ptr<Title> titleScene = Ptr<Title>::New();
		titleScene->SetNeedFadeIn(false);
		game->LoadScene(titleScene.Get());
	};
	GetScheduler()->AddFrameTimer(timer);
}

void SelectScene::StartGame()
{
	this->blackLayer = Ptr<Layer>::New();
	AddLayer(this->blackLayer);

	Audio::GetInstance()->GetCurrentMusic()->FadeOut(2000);

	Ptr<Sprite> black = Ptr<Sprite>::New();
	black->SetPosition(Vector3f(320, 240, 100));
	black->SetTexture(Global::GetInstance()->texBlack);
	black->SetAlpha(0);
	black->AddTween(Ptr<FadeTo>::New(1.0f, GO_TO_NEXT_SCENE_TIME, Tweener::SIMPLE).Get());
	blackLayer->AddChild(black.Get());

	Ptr<Sprite> loading = Ptr<Sprite>::New();
	loading->SetPosition(Vector3f(544, 80, 20));
	loading->SetTexture(this->texLoading);
	loading->SetTexRect(Rect(0, 256, 0, 96));
	loading->SetAlpha(0.0f);
	Ptr<TweenSequence> sequence = Ptr<TweenSequence>::New();
	sequence->AddTween(Ptr<ColorTo>::New(Vector3f(0.5f, 0.5f, 0.5f), 18, Tweener::SIMPLE).Get());
	sequence->AddTween(Ptr<ColorTo>::New(Vector3f(1.0f, 1.0f, 1.0f), 18, Tweener::SIMPLE).Get());
	sequence->SetLooped(true);
	loading->AddTween(sequence.Get());
	loading->AddTween(Ptr<FadeTo>::New(1.0f, 18, Tweener::SIMPLE).Get());
	blackLayer->AddChild(loading.Get());

	this->nowLoading = true;

	Ptr<FrameTimer> timer = Ptr<FrameTimer>::New();
	timer->SetFrame(GO_TO_NEXT_SCENE_TIME);
	timer->run = [this]() {
		auto engine = STGEngine::GetInstance();
		auto global = Global::GetInstance();

		engine->Init();
		engine->SetGameType(STGEngine::NEW_GAME);
		global->stageEnum = Global::STAGE_01;
		global->playerEnum = Global::REIMU;
		Ptr<GameScene> scene = Ptr<GameScene>::New();
		Game::GetInstance()->LoadSceneAsync(scene.Get(), 18, [this]() {
			Ptr<Sprite> black2 = Ptr<Sprite>::New();
			black2->SetPosition(Vector3f(320, 240, 0));
			black2->SetTexture(Global::GetInstance()->texBlack);
			black2->SetAlpha(0);
			black2->AddTween(Ptr<FadeTo>::New(1.0f, 18, Tweener::SIMPLE).Get());
			this->blackLayer->AddChild(black2.Get());
		});
	};
	GetScheduler()->AddFrameTimer(timer);
}