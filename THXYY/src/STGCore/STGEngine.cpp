#include "STGEngine.h"
#include "Global.h"
#include "Effect\BulletFog.h"
#include "../Player/Reimu.h"
#include "../Stage/Stage01.h"

using namespace THEngine;

STGEngine* STGEngine::instance = nullptr;

STGEngine::STGEngine()
{
	ASSERT(instance == nullptr);

	score = hiScore = 0;

	stgResources = STGResources::GetInstance();
	stgResources->Retain();

	player = nullptr;
	gameScene = nullptr;
	stage = nullptr;
}

STGEngine::~STGEngine()
{
	TH_SAFE_RELEASE(stgResources);
	TH_SAFE_RELEASE(player);
	TH_SAFE_RELEASE(stage);
}

STGEngine* STGEngine::GetInstance()
{
	return instance;
}

STGEngine* STGEngine::Create()
{
	if (instance)
	{
		return nullptr;
	}
	STGEngine* engine =  new STGEngine();
	engine->SetDifficulty(NORMAL);
	instance = engine;
	return engine;
}

void STGEngine::Init()
{
	gameOver = false;
}

void STGEngine::Start()
{
	auto global = Global::GetInstance();

	SetLife(2);
	SetBomb(3);
	SetPower(100);
	SetMaxPower(400);
	SetMaxPoint(10000);
	SetScore(0);
	SetGraze(0);
	SetDifficulty(STGEngine::NORMAL);

	switch (global->playerEnum)
	{
	case Global::REIMU:
		player = new Reimu();
	}
	player->Retain();

	((GameScene*)Game::GetInstance()->GetScene())->GetSTGLayer()->AddChild(player);

	Stage* stage = nullptr;
	switch (global->stageEnum)
	{
	case Global::STAGE_01:
		stage = new Stage01();
	}

	LoadStage(stage);
}

void STGEngine::Clear()
{
	auto iter = enemyList.GetIterator();
	while (iter->HasNext())
	{
		iter->Next()->MarkDestroy();
	}

	auto iter2 = bulletList.GetIterator();
	while (iter2->HasNext())
	{
		iter2->Next()->MarkDestroy();
	}

	auto iter3 = effectList.GetIterator();
	while (iter3->HasNext())
	{
		iter3->Next()->MarkDestroy();
	}

	auto iter4 = playerBulletList.GetIterator();
	while (iter4->HasNext())
	{
		iter4->Next()->MarkDestroy();
	}

	auto iter5 = itemList.GetIterator();
	while (iter5->HasNext())
	{
		iter5->Next()->MarkDestroy();
	}

	auto iter6 = particleList.GetIterator();
	while (iter6->HasNext())
	{
		iter6->Next()->MarkDestroy();
	}

	player->MarkDestroy();

	enemyList.Clear();
	bulletList.Clear();
	effectList.Clear();
	playerBulletList.Clear();
	itemList.Clear();
	particleList.Clear();

	TH_SAFE_RELEASE(player);
	TH_SAFE_RELEASE(stage);
}

void STGEngine::Restart()
{
	Clear();
	Start();
}

void STGEngine::Shutdown()
{
	Clear();
}

void STGEngine::Update()
{
	UpdateList();

	if (stage)
	{
		stage->Update();
	}
}

void STGEngine::UpdateList()
{
	auto iter = enemyList.GetIterator();
	while (iter->HasNext())
	{
		if (iter->Next()->NeedRemove())
		{
			iter->Remove();
		}
	}

	auto iter2 = bulletList.GetIterator();
	while (iter2->HasNext())
	{
		if (iter2->Next()->NeedRemove())
		{
			iter2->Remove();
		}
	}

	auto iter3 = effectList.GetIterator();
	while (iter3->HasNext())
	{
		if (iter3->Next()->NeedRemove())
		{
			iter3->Remove();
		}
	}

	auto iter4 = playerBulletList.GetIterator();
	while (iter4->HasNext())
	{
		if (iter4->Next()->NeedRemove())
		{
			iter4->Remove();
		}
	}

	auto iter5 = itemList.GetIterator();
	while (iter5->HasNext())
	{
		if (iter5->Next()->NeedRemove())
		{
			iter5->Remove();
		}
	}

	auto iter6 = particleList.GetIterator();
	while (iter6->HasNext())
	{
		if (iter6->Next()->NeedRemove())
		{
			iter6->Remove();
		}
	}
}

void STGEngine::LoadStage(Stage* stage)
{
	this->stage = stage;
	this->stage->Retain();
	this->stage->OnLoad();

	player->SetPosition(192.0f, 48.0f);
}

void STGEngine::OnLoad()
{
	Start();
}

void STGEngine::AddEnemy(Enemy* enemy)
{
	enemyList.Add(enemy);
	gameScene->GetSTGLayer()->AddChild(enemy);
}

void STGEngine::AddBullet(Bullet* bullet)
{
	bulletList.Add(bullet);
	gameScene->GetSTGLayer()->AddChild(bullet);
}

void STGEngine::AddEffect(Sprite* effect)
{
	effectList.Add(effect);
	gameScene->GetSTGLayer()->AddChild(effect);
}

void STGEngine::AddItem(Item* item)
{
	itemList.Add(item);
	gameScene->GetSTGLayer()->AddChild(item);
}

void STGEngine::AddParticle(Particle3D* particle)
{
	particleList.Add(particle);
	gameScene->GetSTGParticleLayer()->AddChild(particle);
}

void STGEngine::ShootPlayerBullet(PlayerBullet* playerBullet)
{
	playerBulletList.Add(playerBullet);
	gameScene->GetSTGLayer()->AddChild(playerBullet);
}

void STGEngine::ShootBullet(Bullet* bullet, bool hasFog, int sound)
{
	auto stgResources = STGResources::GetInstance();

	if (hasFog)
	{
		BulletFog* fog = new BulletFog(bullet);
		AddEffect(fog);
	}
	else
	{
		AddBullet(bullet);
	}

	if (sound)
	{
		switch (sound)
		{
		case 1:
			stgResources->soundShoot1->Play();
			break;
		case 2:
			stgResources->soundShoot2->Play();
			break;
		case 3:
			stgResources->soundShoot3->Play();
			break;
		default:
			break;
		}
	}
}

void STGEngine::GameOver()
{
	auto scene = (GameScene*)Game::GetInstance()->GetScene();
	scene->GetPauseMenu()->DoGameOver();
	scene->GetSTGLayer()->Pause();

	gameOver = true;
}

void STGEngine::RemoveAllBullet()
{
	auto iter = bulletList.GetIterator();
	while (iter->HasNext())
	{
		iter->Next()->OnDie();
	}
}