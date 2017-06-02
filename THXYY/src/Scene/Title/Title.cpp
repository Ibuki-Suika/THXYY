#include "Title.h"
#include "TitleMenu.h"
#include "../../STGCore/STGCore.h"

Title::Title()
{
}

Title::~Title()
{
	TH_SAFE_RELEASE(titleTex);
	TH_SAFE_RELEASE(texLogo);
}

void Title::OnLoad(AsyncInfo* info)
{
	Scene::OnLoad(info);

	auto assetManager = AssetManager::GetInstance();

	titleTex = assetManager->CreateTextureFromFile("res/title/title.jpg");
	titleTex->Retain();

	this->texLogo = assetManager->CreateTextureFromFile("res/title/logo.png");
	this->texLogo->Retain();
}

void Title::OnStart()
{
	Scene::OnStart();

	bgrLayer = new Layer();
	bgrLayer->SetOrder(100);

	Sprite* background = new Sprite();
	background->SetTexture(titleTex);
	background->SetPosition(Vector3f(0.0f, 0.0f, 100.0f));
	background->SetPivot(Vector2f(0.0f, 0.0f));
	bgrLayer->AddChild(background);
	this->AddLayer(bgrLayer);

	TitleMenu* titleMenu = new TitleMenu();
	titleMenu->SetOrder(50);
	this->AddLayer(titleMenu);

	particleLayer = new ParticleLayer();
	particleLayer->SetOrder(20);
	AddLayer(particleLayer);

	blackLayer = new Layer();
	blackLayer->SetOrder(0);
	AddLayer(blackLayer);

	CreateLogo();

	if (needFadeIn)
	{
		black = new Sprite();
		black->SetTexture(Global::GetInstance()->texBlack);
		black->SetPosition(Vector3f(0.0f, 0.0f, 1.0f));
		black->SetPivot(Vector2f(0.0f, 0.0f));
		black->AddTween(new FadeTo(0.0f, 80, Tweener::SIMPLE));
		blackLayer->AddChild(black);

		titleMenu->Pause();
		FrameTimer* timer = new FrameTimer();
		timer->SetFrame(60);
		timer->run = [titleMenu]() {
			titleMenu->Resume();
		};
		GetScheduler()->AddFrameTimer(timer);

		Music* bgm = Global::GetInstance()->titleMusic;
		if (bgm)
		{
			bgm->Play();
		}
	}
}

void Title::CreateLogo()
{
	Sprite* logo = new Sprite();
	logo->SetTexture(this->texLogo);
	logo->SetPosition(Vector3f(228, 355, 5));

	if (needFadeIn)
	{
		logo->SetAlpha(0.0f);
		logo->SetScale(1.5f, 1.5f);
		logo->GetScheduler()->AddFrameTimer(20, [logo]() {
			logo->AddTween(new FadeTo(1.0f, 30, Tweener::SIMPLE));
			logo->AddTween(new ScaleTo(Vector3f(1.0f, 1.0f, 1.0f), 30, Tweener::SIMPLE));
		});
	}

	this->bgrLayer->AddChild(logo);
}