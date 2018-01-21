#include "GameScene.h"
#include "ItemLine.h"
#include "../Title/Title.h"
#include "../../STGCore/STGCore.h"

using namespace THEngine;

GameScene::GameScene()
{
	auto engine = STGEngine::GetInstance();
	engine->SetGameScene(this);

	baseLayer = Ptr<Layer>::New();
	baseLayer->SetOrder(100);
	AddLayer(baseLayer);

	stgLayer = Ptr<STGLayer>::New();
	stgLayer->SetOrder(10);
	AddLayer(stgLayer.Get());

	stgParticleLayer = Ptr<STGParticleLayer>::New();
	stgParticleLayer->SetOrder(15);
	AddLayer(stgParticleLayer.Get());

	blackLayer = Ptr<Layer>::New();
	blackLayer->SetOrder(0);
	AddLayer(blackLayer);

	blackSTGLayer = Ptr<Layer>::New(32, 16, 384, 448);
	blackLayer->SetOrder(1);
	AddLayer(blackSTGLayer);

	backgroundLayer = Ptr<Layer>::New(32, 16, 384, 448);
	backgroundLayer->SetOrder(50);
	AddLayer(backgroundLayer);

	pauseMenu = Ptr<PauseMenu>::New();
	pauseMenu->SetOrder(5);
	AddLayer(pauseMenu.Get());

	yesNoMenu = Ptr<YesNoMenu>::New();
	yesNoMenu->SetOrder(4);
	AddLayer(yesNoMenu.Get());
}

GameScene::~GameScene()
{
}

void GameScene::Update()
{
	Scene::Update();

	UpdateScore();
	UpdateLifeAndBomb();
	UpdatePower();
}

void GameScene::Draw()
{
	Scene::Draw();
	Device::GetInstance()->SetOrtho(0, 0, Game::GetInstance()->GetWidth(), Game::GetInstance()->GetHeight(), 0, 100);
	Device::GetInstance()->SetViewport(0, 0, Game::GetInstance()->GetWidth(), Game::GetInstance()->GetHeight());
	DrawMaxPoint();
	DrawGraze();
}

void GameScene::CreateFront()
{
	auto engine = STGEngine::GetInstance();

	Ptr<Sprite> background = Ptr<Sprite>::New();
	background->SetTexture(texGameBg);
	background->SetPivot(Vector2f(0.0f, 0.0f));
	background->SetPosition(Vector3f(0.0f, 0.0f, 100.0f));
	baseLayer->AddChild(background.Get());

	//�����Ѷ���
	this->difficulty = Ptr<Sprite>::New();
	this->difficulty->SetTexture(texGameBg2);
	this->difficulty->SetPosition(Vector3f(528.0f, 448.0f, 1.0f));
	switch (engine->GetDifficulty())
	{
	case STGEngine::EASY:
		this->difficulty->SetTexRect(Rect(0.0f, 96.0f, 0.0f, 32.0f));
		break;
	case STGEngine::NORMAL:
		this->difficulty->SetTexRect(Rect(0.0f, 96.0f, 32.0f, 64.0f));
		break;
	case STGEngine::HARD:
		this->difficulty->SetTexRect(Rect(0.0f, 96.0f, 64.0f, 96.0f));
		break;
	case STGEngine::LUNATIC:
		this->difficulty->SetTexRect(Rect(0.0f, 96.0f, 96.0f, 128.0f));
		break;
	case STGEngine::EXTRA:
		this->difficulty->SetTexRect(Rect(0.0f, 96.0f, 128.0f, 160.0f));
		break;
	default:
		break;
	}
	baseLayer->AddChild(this->difficulty.Get());
	if (IsNewGame())
	{
		this->difficulty->SetAlpha(0);
		Ptr<TweenSequence> sequence = Ptr<TweenSequence>::New();
		sequence->AddTween(Ptr<Delay>::New(120).Get());
		sequence->AddTween(Ptr<FadeTo>::New(1.0f, 30, Tweener::SIMPLE).Get());
		this->difficulty->AddTween(sequence.Get());
	}

	//����������
	CreateScorePanel();

	//�����л��ͷ�����
	for (int i = 0; i < 8; i++)
	{
		lifeSprite[i] = Ptr<Sprite>::New();
		lifeSprite[i]->SetTexture(texGameBg2);
		lifeSprite[i]->SetPivot(Vector2f(0.0f, 0.0f));
		lifeSprite[i]->SetPosition(Vector3f(SCORE_LEFT - 5 + 18 * i, 340.0f, 1.0f));
		baseLayer->AddChild(lifeSprite[i].Get());

		bombSprite[i] = Ptr<Sprite>::New();
		bombSprite[i]->SetTexture(texGameBg2);
		bombSprite[i]->SetPivot(Vector2f(0.0f, 0.0f));
		bombSprite[i]->SetPosition(Vector3f(SCORE_LEFT - 5 + 18 * i, 314.0f, 1.0f));
		baseLayer->AddChild(bombSprite[i].Get());
	}

	//����������
	CreatePowerPanel();
}

void GameScene::OnLoad(Ptr<AsyncInfo> info)
{
	Scene::OnLoad(info);

	auto manager = AssetManager::GetInstance();
	texGameBg = manager->CreateTextureFromFile("res/front/gamebg.jpg");
	texGameBg2 = manager->CreateTextureFromFile("res/front/gamebg2.png");
	texFront = manager->CreateTextureFromFile("res/front/front.png");

	auto engine = STGEngine::GetInstance();
	engine->OnLoad();
}

void GameScene::OnStart()
{
	Scene::OnStart();

	auto engine = STGEngine::GetInstance();
	engine->OnStart();

	CreateFront();
	StartStage();

	Ptr<Sprite> black = Ptr<Sprite>::New();
	black->SetTexture(Global::GetInstance()->texBlack);
	black->SetPosition(Vector3f(0.0f, 0.0f, 1.0f));
	black->SetPivot(Vector2f(0.0f, 0.0f));
	black->SetAlpha(1.0f);
	black->AddTween(Ptr<FadeOut>::New(30, Tweener::EASE_OUT).Get());
	blackLayer->AddChild(black.Get());

	auto eventSystem = EventSystem::GetInstance();
	eventSystem->RegisterKeyDownListener(this);
}

void GameScene::OnDestroy()
{
	Scene::OnDestroy();

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);

	auto engine = STGEngine::GetInstance();
	engine->Shutdown();
	engine->SetGameScene(nullptr);
}

void GameScene::CreateScorePanel()
{
	for (int i = 0; i < 10; i++)
	{
		hiScore[i] = Ptr<ScoreNumber>::New();
		hiScore[i]->SetTexture(texGameBg2);
		hiScore[i]->SetPivot(Vector2f(0.0f, 0.0f));
		baseLayer->AddChild(hiScore[i].Get());

		score[i] = Ptr<ScoreNumber>::New();
		score[i]->SetTexture(texGameBg2);
		score[i]->SetPosition(Vector3f(SCORE_LEFT + 13 * i, 382.0f, 1.0f));
		score[i]->SetPivot(Vector2f(0.0f, 0.0f));
		baseLayer->AddChild(score[i].Get());
	}

	hiScore[0]->SetPosition(Vector3f(SCORE_LEFT, 410.0f, 1.0f));
	for (int j = 1; j < 4; j++)
	{
		hiScore[j]->SetPosition(Vector3f(SCORE_LEFT + 18 + 13 * (j - 1), 410.0f, 1.0f));
	}
	for (int j = 4; j < 7; j++)
	{
		hiScore[j]->SetPosition(Vector3f(SCORE_LEFT + 62 + 13 * (j - 4), 410.0f, 1.0f));
	}
	for (int j = 7; j < 10; j++)
	{
		hiScore[j]->SetPosition(Vector3f(SCORE_LEFT + 106 + 13 * (j - 7), 410.0f, 1.0f));
	}

	score[0]->SetPosition(Vector3f(SCORE_LEFT, 382.0f, 1.0f));
	for (int j = 1; j < 4; j++)
	{
		score[j]->SetPosition(Vector3f(SCORE_LEFT + 18 + 13 * (j - 1), 382.0f, 1.0f));
	}
	for (int j = 4; j < 7; j++)
	{
		score[j]->SetPosition(Vector3f(SCORE_LEFT + 62 + 13 * (j - 4), 382.0f, 1.0f));
	}
	for (int j = 7; j < 10; j++)
	{
		score[j]->SetPosition(Vector3f(SCORE_LEFT + 106 + 13 * (j - 7), 382.0f, 1.0f));
	}

	Ptr<Sprite> comma[6];
	for (int i = 0; i < 6; i++)
	{
		comma[i] = Ptr<Sprite>::New();
		comma[i]->SetTexture(texGameBg2);
		comma[i]->SetPivot(Vector2f(0.0f, 0.0f));
		comma[i]->SetTexRect(Rect(226, 231, 8, 24));
		baseLayer->AddChild(comma[i].Get());
	}
	for (int i = 0; i < 3; i++)
	{
		comma[i]->SetPosition(Vector3f(SCORE_LEFT + 13 + 44 * i, 410.0f, 1.0f));
	}
	for (int i = 3; i < 6; i++)
	{
		comma[i]->SetPosition(Vector3f(SCORE_LEFT + 13 + 44 * (i - 3), 382.0f, 1.0f));
	}
}

void GameScene::CreatePowerPanel()
{
	powerSprite[0] = Ptr<PowerNumber>::New();
	powerSprite[0]->SetTexture(texGameBg2);
	powerSprite[0]->SetPivot(Vector2f(0.0f, 0.0f));
	powerSprite[0]->SetPosition(Vector3f(POWER_LEFT, 276.0f, 1.0f));
	baseLayer->AddChild(powerSprite[0].Get());

	Ptr<Sprite> point1 = Ptr<Sprite>::New();
	point1->SetTexture(texGameBg2);
	point1->SetTexRect(Rect(242.0f, 248.0f, 40.0f, 56.0f));
	point1->SetPivot(Vector2f(0.0f, 0.0f));
	point1->SetPosition(Vector3f(POWER_LEFT + 13, 276.0f, 1.0f));
	baseLayer->AddChild(point1.Get());

	for (int i = 1; i < 3; i++)
	{
		powerSprite[i] = Ptr<PowerNumber>::New();
		powerSprite[i]->SetTexture(texGameBg2);
		powerSprite[i]->SetPivot(Vector2f(0.0f, 0.0f));
		powerSprite[i]->SetPosition(Vector3f(POWER_LEFT + 13 * i + 6, 276.0f, 1.0f));
		baseLayer->AddChild(powerSprite[i].Get());
	}

	Ptr<Sprite> gang = Ptr<Sprite>::New();
	gang->SetTexture(texGameBg2);
	gang->SetTexRect(Rect(232.0f, 242.0f, 40.0f, 56.0f));
	gang->SetPivot(Vector2f(0.0f, 0.0f));
	gang->SetPosition(Vector3f(POWER_LEFT + 45, 276.0f, 1.0f));
	baseLayer->AddChild(gang.Get());

	powerSprite[3] = Ptr<PowerNumber>::New();
	powerSprite[3]->SetTexture(texGameBg2);
	powerSprite[3]->SetPivot(Vector2f(0.0f, 0.0f));
	powerSprite[3]->SetPosition(Vector3f(POWER_LEFT + 55, 276.0f, 1.0f));
	baseLayer->AddChild(powerSprite[3].Get());

	Ptr<Sprite> point2 = Ptr<Sprite>::New();
	point2->SetTexture(texGameBg2);
	point2->SetTexRect(Rect(242.0f, 248.0f, 40.0f, 56.0f));
	point2->SetPivot(Vector2f(0.0f, 0.0f));
	point2->SetPosition(Vector3f(POWER_LEFT + 68, 276.0f, 1.0f));
	baseLayer->AddChild(point2.Get());

	for (int i = 4; i < 6; i++)
	{
		powerSprite[i] = Ptr<PowerNumber>::New();
		powerSprite[i]->SetTexture(texGameBg2);
		powerSprite[i]->SetPivot(Vector2f(0.0f, 0.0f));
		powerSprite[i]->SetPosition(Vector3f(POWER_LEFT + 13 * i + 22, 276.0f, 1.0f));
		baseLayer->AddChild(powerSprite[i].Get());
	}
}

void GameScene::UpdateScore()
{
	auto engine = STGEngine::GetInstance();

	long long temp1 = engine->GetScore(), temp2 = engine->GetHiScore();
	for (int i = 0; i < 10; i++)
	{
		score[9 - i]->SetNumber(temp1 % 10);
		temp1 /= 10;
		hiScore[9 - 1]->SetNumber(temp2 % 10);
		temp2 /= 10;
	}
}

void GameScene::UpdateLifeAndBomb()
{
	auto engine = STGEngine::GetInstance();
	int life = engine->GetLife();
	int bomb = engine->GetBomb();

	int lifeInt = (int)life;
	lifeInt = lifeInt < 0 ? 0 : lifeInt;
	for (int i = 0; i < lifeInt; i++)
	{
		lifeSprite[i]->SetTexRect(Rect(7.0f, 25.0f, 180.0f, 204.0f));
	}
	for (int i = lifeInt; i < 8; i++)
	{
		lifeSprite[i]->SetTexRect(Rect(39.0f, 57.0f, 180.0f, 204.0f));
	}

	int bombInt = (int)bomb;
	bombInt = bombInt < 0 ? 0 : bombInt;
	for (int i = 0; i < bombInt; i++)
	{
		bombSprite[i]->SetTexRect(Rect(7.0f, 25.0f, 212.0f, 236.0f));
	}
	for (int i = bombInt; i < 8; i++)
	{
		bombSprite[i]->SetTexRect(Rect(39.0f, 57.0f, 212.0f, 236.0f));
	}
}

void GameScene::UpdatePower()
{
	auto engine = STGEngine::GetInstance();
	int power = engine->GetPower();
	int maxPower = engine->GetMaxPower();
	int temp1 = power;
	int temp2 = maxPower;

	for (int i = 0; i < 3; i++)
	{
		powerSprite[2 - i]->SetNumber(temp1 % 10);
		temp1 /= 10;
		powerSprite[5 - i]->SetNumber(temp2 % 10);
		temp2 /= 10;
	}
}

void GameScene::DrawMaxPoint()
{
	auto engine = STGEngine::GetInstance();
	int maxPoint = engine->GetMaxPoint();

	auto iter = pointSpriteList.GetIterator();
	while (iter->HasNext())
	{
		iter->Next()->MarkDestroy();
	}

	pointSpriteList.Clear();

	int temp = maxPoint;
	for (int i = 0; temp > 0; i++)
	{
		Ptr<PointNumber> pointSprite = Ptr<PointNumber>::New();
		pointSprite->SetTexture(texGameBg2);
		pointSprite->SetPivot(Vector2f(0.0f, 0.0f));
		pointSprite->SetNumber(temp % 10);
		pointSprite->SetPosition(Vector3f(POWER_LEFT + 87.0f - 13.0f * i, 252.0f, 1.0f));
		baseLayer->AddChild(pointSprite.Get());
		pointSpriteList.Add(pointSprite.Get());
		temp /= 10;
	}
}

void GameScene::DrawGraze()
{
	auto engine = STGEngine::GetInstance();
	int graze = engine->GetGraze();

	auto iter = grazeSpriteList.GetIterator();
	while (iter->HasNext())
	{
		iter->Next()->MarkDestroy();
	}

	grazeSpriteList.Clear();

	int temp = graze;
	if (temp == 0)
	{
		Ptr<GrazeNumber> grazeSprite = Ptr<GrazeNumber>::New();
		grazeSprite->SetTexture(texGameBg2);
		grazeSprite->SetPivot(Vector2f(0.0f, 0.0f));
		grazeSprite->SetNumber(0);
		grazeSprite->SetPosition(Vector3f(POWER_LEFT + 87.0f, 228.0f, 1.0f));
		baseLayer->AddChild(grazeSprite.Get());
		grazeSpriteList.Add(grazeSprite);
	}
	else for (int i = 0; temp > 0; i++)
	{
		Ptr<GrazeNumber> grazeSprite = Ptr<GrazeNumber>::New();
		grazeSprite->SetTexture(texGameBg2);
		grazeSprite->SetPivot(Vector2f(0.0f, 0.0f));
		grazeSprite->SetNumber(temp % 10);
		grazeSprite->SetPosition(Vector3f(POWER_LEFT + 87.0f - 13.0f * i, 228.0f, 1.0f));
		baseLayer->AddChild(grazeSprite.Get());
		grazeSpriteList.Add(grazeSprite);
		temp /= 10;
	}
}

void GameScene::ReturnToTitle()
{
	Ptr<Sprite> black = Ptr<Sprite>::New();
	black->SetTexture(Global::GetInstance()->texBlack);
	black->SetPosition(Vector3f(0.0f, 0.0f, 1.0f));
	black->SetPivot(Vector2f(0.0f, 0.0f));
	black->SetAlpha(0.0f);
	black->AddTween(Ptr<FadeTo>::New(1.0f, 60, Tweener::EASE_OUT).Get());
	blackLayer->AddChild(black.Get());

	Ptr<Scheduler> scheduler = GetScheduler();
	Ptr<FrameTimer> timer = Ptr<FrameTimer>::New();
	timer->SetFrame(60);
	timer->run = []() {Game::GetInstance()->LoadScene(Ptr<Title>::New().Get()); };
	scheduler->AddFrameTimer(timer);
}

bool GameScene::IsNewGame()
{
	return STGEngine::GetInstance()->GetGameType() == STGEngine::NEW_GAME;
}

bool GameScene::IsFirstStage()
{
	auto engine = STGEngine::GetInstance();
	return engine->GetStageEnum() == STGEngine::STAGE_01 ||
		engine->GetStageEnum() == STGEngine::STAGE_EX;
}

void GameScene::DrawNewGameItems()
{
	auto engine = STGEngine::GetInstance();

	//draw item get border line
	float lineHeight = STGEngine::GetInstance()->GetPlayer()->GetItemGetHeight();

	Ptr<ItemLine> itemLineText = Ptr<ItemLine>::New();
	itemLineText->SetTexture(this->texFront);
	itemLineText->SetTexRect(Rect(0, 172, 0, 24));
	itemLineText->SetPosition(Vector3f(192, lineHeight, 25));

	Ptr<ItemLine> itemLine = Ptr<ItemLine>::New();
	itemLine->SetTexture(this->texFront);
	itemLine->SetTexRect(Rect(0, 172, 24, 32));
	itemLine->SetPosition(Vector3f(28, lineHeight, 25));

	Ptr<ItemLine> itemLine2 = Ptr<ItemLine>::New();
	itemLine2->SetTexture(this->texFront);
	itemLine2->SetTexRect(Rect(0, 172, 24, 32));
	itemLine2->SetPosition(Vector3f(356, lineHeight, 25));

	GetSTGLayer()->AddChild(itemLine.Get());
	GetSTGLayer()->AddChild(itemLine2.Get());
	GetSTGLayer()->AddChild(itemLineText.Get());

	//draw blinking difficulty on top of the shooting region
	Ptr<Sprite> diff = Ptr<Sprite>::New();
	diff->SetTexture(texGameBg2);
	switch (engine->GetDifficulty())
	{
	case STGEngine::EASY:
		diff->SetTexRect(Rect(0.0f, 96.0f, 0.0f, 32.0f));
		break;
	case STGEngine::NORMAL:
		diff->SetTexRect(Rect(0.0f, 96.0f, 32.0f, 64.0f));
		break;
	case STGEngine::HARD:
		diff->SetTexRect(Rect(0.0f, 96.0f, 64.0f, 96.0f));
		break;
	case STGEngine::LUNATIC:
		diff->SetTexRect(Rect(0.0f, 96.0f, 96.0f, 128.0f));
		break;
	case STGEngine::EXTRA:
		diff->SetTexRect(Rect(0.0f, 96.0f, 128.0f, 160.0f));
		break;
	default:
		break;
	}
	Ptr<TweenSequence> sequence = Ptr<TweenSequence>::New();
	sequence->AddTween(Ptr<Delay>::New(7).Get());
	sequence->AddTween(Ptr<ColorTo>::New(Vector3f(0.5f, 0.5f, 0.5f), 1, Tweener::SIMPLE).Get());
	sequence->AddTween(Ptr<Delay>::New(7).Get());
	sequence->AddTween(Ptr<ColorTo>::New(Vector3f(1.0f, 1.0f, 1.0f), 1, Tweener::SIMPLE).Get());
	sequence->SetLooped(true);
	diff->AddTween(sequence.Get());

	Ptr<FrameTimer> timer = Ptr<FrameTimer>::New();
	timer->SetFrame(120);

	//do not capture smart pointer here, which will cause cycling reference
	Sprite* raw_diff = diff.Get();
	timer->run = [raw_diff]() {
		raw_diff->ClearTweens();
		raw_diff->AddTween(Ptr<FadeOut>::New(30, Tweener::SIMPLE).Get());
	};
	diff->GetScheduler()->AddFrameTimer(timer);

	diff->SetPosition(Vector3f(192.0f, 432.0f, 1.0f));
	GetSTGLayer()->AddChild(diff.Get());
}

void GameScene::StartStage()
{
	if (IsNewGame() && IsFirstStage())
	{
		DrawNewGameItems();

		this->difficulty->SetAlpha(0);
		Ptr<TweenSequence> sequence = Ptr<TweenSequence>::New();
		sequence->AddTween(Ptr<Delay>::New(120).Get());
		sequence->AddTween(Ptr<FadeTo>::New(1.0f, 30, Tweener::SIMPLE).Get());
		this->difficulty->AddTween(sequence.Get());
	}
}

void GameScene::Restart()
{
	auto engine = STGEngine::GetInstance();

	engine->Restart();
	STGFadeIn(60);
	GetSTGLayer()->Resume();
	GetSTGParticleLayer()->Resume();
	GetYesNoMenu()->Clear();

	StartStage();
}

void GameScene::STGFadeIn(int time)
{
	if (blackSTG)
	{
		blackSTG->AddTween(Ptr<FadeOut>::New(time, Tweener::EASE_OUT).Get());
		blackSTG = nullptr;
	}
}

void GameScene::STGFadeOut(int time)
{
	blackSTG = Ptr<Sprite>::New();
	blackSTG->SetTexture(Global::GetInstance()->texBlack);
	blackSTG->SetPosition(Vector3f(0.0f, 0.0f, 1.0f));
	blackSTG->SetPivot(Vector2f(0.0f, 0.0f));
	blackSTG->SetAlpha(0.0f);
	blackSTG->AddTween(Ptr<FadeTo>::New(1.0f, time, Tweener::EASE_OUT).Get());
	blackSTGLayer->AddChild(blackSTG.Get());
}

bool GameScene::OnKeyDown(Ptr<EngineObject> sender, int key)
{
	if (key == VK_ESCAPE)
	{
		if (stgLayer->IsPaused() == false)
		{
			stgLayer->Pause();
			stgParticleLayer->Pause();
			pauseMenu->DoPause();
			return true;
		}
	}

	return false;
}