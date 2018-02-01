#ifndef STGENGINE_H
#define STGENGINE_H

#include <THEngine.h>
#include "Player\Player.h"
#include "Player\PlayerBullet.h"
#include "Stage.h"
#include "../Scene/Game/GameScene.h"
#include "STGResources.h"
#include "Enemy\Enemy.h"
#include "Bullet\Bullet.h"
#include "Item\Item.h"

using namespace THEngine;

class STGEngine : public Object, public Singleton<STGEngine>
{
	friend class Singleton<STGEngine>;
public:
	enum Difficulty
	{
		EASY,
		NORMAL,
		HARD,
		LUNATIC,
		EXTRA
	};

	enum StageEnum
	{
		STAGE_01,
		STAGE_02,
		STAGE_03,
		STAGE_04,
		STAGE_05,
		STAGE_06,
		STAGE_EX
	};

	enum GameType
	{
		NEW_GAME,
		PRACTICE,
		SPELL_PRACTICE
	};

private:
	STGEngine() = default;

private:
	Ptr<RandomGenerator> randomGenerator = Ptr<RandomGenerator>::New(time(NULL));

	Difficulty difficulty;
	GameType gameType;
	long long score = 0;
	long long hiScore = 0;
	int life;
	int bomb;
	int power;
	int maxPower;
	int maxPoint;
	int graze;

	bool gameOver = false;

	LinkedList<Ptr<Enemy>> enemyList;
	LinkedList<Ptr<Bullet>> bulletList;
	LinkedList<Ptr<Sprite>> effectList;
	LinkedList<Ptr<PlayerBullet>> playerBulletList;
	LinkedList<Ptr<Item>> itemList;
	LinkedList<Ptr<Particle3D>> particleList;
	LinkedList<Ptr<GameObject>> backgroundList;

	Ptr<STGResources> stgResources = STGResources::GetInstance();

	Ptr<Player> player;

	Ptr<GameScene> gameScene;

	Ptr<Stage> stage;

	StageEnum stageEnum;

public:
	virtual ~STGEngine();
	bool Init();

	inline void SetDifficulty(Difficulty diff) { this->difficulty = diff; }
	inline Difficulty GetDifficulty() { return difficulty; }

	inline void SetGameType(GameType gameType) { this->gameType = gameType; }
	inline GameType GetGameType() const { return this->gameType; }

	inline void SetScore(long long score) { this->score = score; }
	inline long long GetScore() { return score; }

	inline void SetHiScore(long long hiScore) { this->hiScore = hiScore; }
	inline long long GetHiScore() { return hiScore; }

	inline void SetLife(int life) { this->life = life; }
	inline int GetLife() { return life; }

	inline void SetBomb(int bomb) { this->bomb = bomb; }
	inline int GetBomb() { return bomb; }

	inline void SetPower(int power) { this->power = power; }
	inline int GetPower() { return power; }

	inline void SetMaxPower(int power) { this->maxPower = power; }
	inline int GetMaxPower() { return maxPower; }

	inline void SetMaxPoint(int point) { this->maxPoint = point; }
	inline int GetMaxPoint() { return maxPoint; }

	inline void SetGraze(int graze) { this->graze = graze; }
	inline int GetGraze() { return graze; }

	inline Ptr<Player> GetPlayer() { return player; }

	inline void SetGameScene(Ptr<GameScene> scene)
	{
		this->gameScene = scene;
	}
	inline Ptr<GameScene> GetGameScene() { return gameScene; }

	inline void SetStageEnum(StageEnum stageEnum) { this->stageEnum = stageEnum; }
	inline StageEnum GetStageEnum() { return stageEnum; }

	inline LinkedList<Ptr<Enemy>>* GetEnemyList() { return &enemyList; }
	inline LinkedList<Ptr<Bullet>>* GetBulletList() { return &bulletList; }
	inline LinkedList<Ptr<PlayerBullet>>* GetPlayerBulletList() { return &playerBulletList; }

	inline bool IsGameOver() { return gameOver; }

	void AddEnemy(Ptr<Enemy> enemy);
	void AddBullet(Ptr<Bullet> bullet);
	void AddEffect(Ptr<Sprite> effect);
	void AddItem(Ptr<Item> item);
	void AddParticle(Ptr<Particle3D> particle);
	void AddBackgroundObject(Ptr<GameObject> object);

	void ShootPlayerBullet(Ptr<PlayerBullet> playerBullet);

	inline void AddObject(Ptr<Sprite> object)
	{
		gameScene->GetSTGLayer()->AddChild(object.Get());
	}

	inline void ShootBullet(Ptr<Bullet> bullet)
	{
		ShootBullet(bullet, true, 1);
	}

	inline void ShootBullet(Ptr<Bullet> bullet, bool hasFog)
	{
		ShootBullet(bullet, hasFog, 1);
	}

	void ShootBullet(Ptr<Bullet> bullet, bool hasFog, int sound);

	void SetBackgroundCamera(Ptr<Camera> camera);
	Ptr<Camera> GetBackgroundCamera();

	void GetAllItems();

	void Update();

	void UpdateList();

	int Random(int a, int b);
	void ResetRandomSeed(int seed);
	int GetRandomSeed();

	void Start();

	void Clear();

	void Restart();

	void Shutdown();

	void LoadStage(Ptr<Stage> stage);
	void StartStage(Ptr<Stage> stage);

	void OnStart();

	void OnLoad();

	void GameOver();

	void RemoveAllBullet();

	friend class API;
};

#endif