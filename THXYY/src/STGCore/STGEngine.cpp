#include "STGEngine.h"
#include "Global.h"
#include "Effect\BulletFog.h"
#include "../Player/Reimu.h"
#include "../Stage/Stage01/Stage01.h"

using namespace THEngine;

STGEngine::~STGEngine()
{
	STGResources::DestroyInstance();
}

void STGEngine::ResetRandomSeed(int seed)
{
	this->randomGenerator->Reset(seed);
}

int STGEngine::GetRandomSeed()
{
	return this->randomGenerator->GetSeed();
}

int STGEngine::Random(int a, int b)
{
	return this->randomGenerator->Next(a, b);
}

bool STGEngine::Init()
{
	gameOver = false;
	this->randomGenerator->Reset(time(NULL));
	return true;
}

void STGEngine::Start()
{
	auto global = Global::GetInstance();

	SetLife(2);
	SetBomb(3);
	SetPower(0);
	SetMaxPower(400);
	SetMaxPoint(10000);
	SetScore(0);
	SetGraze(0);

	switch (global->playerEnum)
	{
	case Global::REIMU:
		player = Ptr<Reimu>::New().Get();
		break;
	}

	((GameScene*)Game::GetInstance()->GetScene().Get())->GetSTGLayer()->AddChild(player.Get());

	StartStage(this->stage);
}

void STGEngine::Clear()
{
	gameScene->GetSTGLayer()->Clear();
	gameScene->GetBackgroundLayer()->Clear();
	gameScene->GetSTGParticleLayer()->Clear();

	enemyList.Clear();
	bulletList.Clear();
	effectList.Clear();
	playerBulletList.Clear();
	itemList.Clear();
	particleList.Clear();
	backgroundList.Clear();
}

void STGEngine::Restart()
{
	Clear();
	OnLoad();
	Start();
}

void STGEngine::Shutdown()
{
	Clear();
}

void STGEngine::Update()
{
	UpdateList();

	if (stage != nullptr)
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

	auto iter7 = backgroundList.GetIterator();
	while (iter7->HasNext())
	{
		if (iter7->Next()->NeedRemove())
		{
			iter7->Remove();
		}
	}
}

void STGEngine::LoadStage(Ptr<Stage> stage)
{
	this->stage = stage;
	this->stage->OnLoad();
}

void STGEngine::StartStage(Ptr<Stage> stage)
{
	stage->OnStart();

	player->SetPosition(192.0f, 48.0f);
}

void STGEngine::OnStart()
{
	Start();
}

void STGEngine::OnLoad()
{
	auto global = Global::GetInstance();

	Ptr<Stage> stage = nullptr;
	switch (global->stageEnum)
	{
	case Global::STAGE_01:
		stage = Ptr<Stage01>::New().Get();
	}

	LoadStage(stage);
}

void STGEngine::AddEnemy(Ptr<Enemy> enemy)
{
	enemyList.Add(enemy);
	gameScene->GetSTGLayer()->AddChild(enemy.Get());
}

void STGEngine::AddBullet(Ptr<Bullet> bullet)
{
	bulletList.Add(bullet);
	gameScene->GetSTGLayer()->AddChild(bullet.Get());
}

void STGEngine::AddEffect(Ptr<Sprite> effect)
{
	effectList.Add(effect);
	gameScene->GetSTGLayer()->AddChild(effect.Get());
}

void STGEngine::AddItem(Ptr<Item> item)
{
	itemList.Add(item);
	gameScene->GetSTGLayer()->AddChild(item.Get());
}

void STGEngine::AddParticle(Ptr<Particle3D> particle)
{
	particleList.Add(particle);
	gameScene->GetSTGParticleLayer()->AddChild(particle.Get());
}

void STGEngine::AddBackgroundObject(Ptr<GameObject> object)
{
	backgroundList.Add(object);
	gameScene->GetBackgroundLayer()->AddChild(object);
}

void STGEngine::ShootPlayerBullet(Ptr<PlayerBullet> playerBullet)
{
	playerBulletList.Add(playerBullet);
	gameScene->GetSTGLayer()->AddChild(playerBullet.Get());
}

void STGEngine::ShootBullet(Ptr<Bullet> bullet, bool hasFog, int sound)
{
	auto stgResources = STGResources::GetInstance();

	if (hasFog)
	{
		Ptr<BulletFog> fog = Ptr<BulletFog>::New(bullet);
		AddEffect(fog.Get());
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

void STGEngine::SetBackgroundCamera(Ptr<Camera> camera)
{
	gameScene->GetBackgroundLayer()->SetFirstCamera(camera);
}

Ptr<Camera> STGEngine::GetBackgroundCamera()
{
	return gameScene->GetBackgroundLayer()->GetFirstCamera();
}

void STGEngine::GameOver()
{
	auto scene = (GameScene*)Game::GetInstance()->GetScene().Get();
	scene->GetPauseMenu()->DoGameOver();
	scene->GetSTGLayer()->Pause();
	scene->GetBackgroundLayer()->Pause();
	scene->GetSTGParticleLayer()->Pause();

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

void STGEngine::GetAllItems()
{
	auto iter = itemList.GetIterator();
	while (iter->HasNext())
	{
		auto item = iter->Next();
		item->gotFromHigh = true;
		item->GoToPlayer();
	}
}