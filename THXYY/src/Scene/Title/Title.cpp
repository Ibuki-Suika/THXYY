#include "Title.h"
#include "TitleMenu.h"
#include "../../STGCore/STGCore.h"

Title::Title()
{
	titleTex = AssetManager::GetInstance()->CreateTextureFromFile("res/title/title.jpg");
	titleTex->Retain();
}

Title::~Title()
{
	TH_SAFE_RELEASE(titleTex);
}

void Title::OnStart()
{
	Scene::OnStart();

	bgrLayer = new Layer();
	bgrLayer->SetOrder(100);

	Sprite* background = new Sprite();
	background->SetTexture(titleTex);
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
		timer->SetFrame(30);
		timer->run = [titleMenu]() {
			titleMenu->Resume();
		};
		GetScheduler()->AddTimer(timer);
	}
}