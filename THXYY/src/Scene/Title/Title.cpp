#include "Title.h"
#include "TitleMenu.h"
#include "../../STGCore/STGCore.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::OnLoad(Ptr<AsyncInfo> info)
{
	Scene::OnLoad(info);

	auto assetManager = AssetManager::GetInstance();

	titleTex = assetManager->CreateTextureFromFile("res/title/title.jpg");
	this->texLogo = assetManager->CreateTextureFromFile("res/title/logo.png");
}

void Title::OnStart()
{
	Scene::OnStart();

	bgrLayer = Ptr<Layer>::New();
	bgrLayer->SetOrder(100);

	Ptr<Sprite> background = Ptr<Sprite>::New();
	background->SetTexture(titleTex);
	background->SetPosition(Vector3f(0.0f, 0.0f, 100.0f));
	background->SetPivot(Vector2f(0.0f, 0.0f));
	bgrLayer->AddChild(background.Get());
	this->AddLayer(bgrLayer);

	Ptr<TitleMenu> titleMenu = Ptr<TitleMenu>::New();
	titleMenu->SetOrder(50);
	this->AddLayer(titleMenu.Get());

	particleLayer = Ptr<ParticleLayer>::New();
	particleLayer->SetOrder(20);
	AddLayer(particleLayer.Get());

	blackLayer = Ptr<Layer>::New();
	blackLayer->SetOrder(0);
	AddLayer(blackLayer);

	CreateLogo();

	if (needFadeIn)
	{
		black = Ptr<Sprite>::New();
		black->SetTexture(Global::GetInstance()->texBlack);
		black->SetPosition(Vector3f(0.0f, 0.0f, 1.0f));
		black->SetPivot(Vector2f(0.0f, 0.0f));
		black->AddTween(Ptr<FadeTo>::New(0.0f, 80, Tweener::SIMPLE).Get());
		blackLayer->AddChild(black.Get());

		titleMenu->Pause();
		Ptr<FrameTimer> timer = Ptr<FrameTimer>::New();
		timer->SetFrame(60);
		timer->run = [titleMenu]() {
			titleMenu->Resume();
		};
		GetScheduler()->AddFrameTimer(timer);

		Ptr<Music> bgm = Global::GetInstance()->titleMusic;
		if (bgm)
		{
			bgm->Play();
		}
	}
}

void Title::CreateLogo()
{
	Ptr<Sprite> logo = Ptr<Sprite>::New();
	logo->SetTexture(this->texLogo);
	logo->SetPosition(Vector3f(228, 355, 5));

	if (needFadeIn)
	{
		logo->SetAlpha(0.0f);
		logo->SetScale(1.5f, 1.5f);
		logo->GetScheduler()->AddFrameTimer(20, [logo]() {
			logo->AddTween(Ptr<FadeTo>::New(1.0f, 30, Tweener::SIMPLE).Get());
			logo->AddTween(Ptr<ScaleTo>::New(Vector3f(1.0f, 1.0f, 1.0f), 30, Tweener::SIMPLE).Get());
		});
	}

	this->bgrLayer->AddChild(logo.Get());
}