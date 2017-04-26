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

class STGEngine : public Object
{
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
	static STGEngine* instance;
	Difficulty difficulty;
	GameType gameType;
	long long score;
	long long hiScore;
	int life;
	int bomb;
	int power;
	int maxPower;
	int maxPoint;
	int graze;

	bool gameOver = false;

	LinkedList<Enemy*> enemyList;
	LinkedList<Bullet*> bulletList;
	LinkedList<Sprite*> effectList;
	LinkedList<PlayerBullet*> playerBulletList;
	LinkedList<Item*> itemList;
	LinkedList<Particle3D*> particleList;
	LinkedList<GameObject*> backgroundList;

	STGResources* stgResources;

	Player* player;

	GameScene* gameScene;

	Stage* stage = nullptr;

	StageEnum stageEnum;

private:
	STGEngine();

public:
	virtual ~STGEngine();
	static STGEngine* GetInstance();
	static STGEngine* Create();

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

	inline Player* GetPlayer() { return player; }

	inline void SetGameScene(GameScene* scene)
	{
		this->gameScene = scene;
	}
	inline GameScene* GetGameScene() { return gameScene; }

	inline void SetStageEnum(StageEnum stageEnum) { this->stageEnum = stageEnum; }
	inline StageEnum GetStageEnum() { return stageEnum; }

	inline LinkedList<Enemy*>* GetEnemyList() { return &enemyList; }
	inline LinkedList<Bullet*>* GetBulletList() { return &bulletList; }
	inline LinkedList<PlayerBullet*>* GetPlayerBulletList() { return &playerBulletList; }

	inline bool IsGameOver() { return gameOver; }

	void AddEnemy(Enemy* enemy);
	void AddBullet(Bullet* bullet);
	void AddEffect(Sprite* effect);
	void AddItem(Item* item);
	void AddParticle(Particle3D* particle);
	void AddBackgroundObject(GameObject* object);

	void ShootPlayerBullet(PlayerBullet* playerBullet);

	inline void AddObject(Sprite* object)
	{
		gameScene->GetSTGLayer()->AddChild(object);
	}

	inline void ShootBullet(Bullet* bullet)
	{
		ShootBullet(bullet, true, 1);
	}

	inline void ShootBullet(Bullet* bullet, bool hasFog)
	{
		ShootBullet(bullet, hasFog, 1);
	}

	void ShootBullet(Bullet* bullet, bool hasFog, int sound);

	void SetBackgroundCamera(Camera* camera);
	Camera* GetBackgroundCamera();

	void GetAllItems();

	void Update();

	void UpdateList();

	void Init();

	void Start();

	void Clear();

	void Restart();

	void Shutdown();

	void LoadStage(Stage* stage);
	void StartStage(Stage* stage);

	void OnStart();

	void OnLoad();

	void GameOver();

	void RemoveAllBullet();

	friend class API;
};

#endif