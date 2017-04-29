#ifndef STGRESOURCES_H
#define STGRESOURCES_H

#include <THEngine.h>

using namespace THEngine;

class STGResources : public Object
{
public:
	static STGResources* instance;

	static STGResources* GetInstance();

	Texture* texPlayerCenter = nullptr;
	Texture* texEnemy01 = nullptr;
	Texture* texBullet01 = nullptr;
	Texture* texBullet02 = nullptr;
	Texture* texBullet03 = nullptr;
	Texture* texBullet04 = nullptr;
	Texture* texReimu = nullptr;
	Texture* texEffBase = nullptr;
	Texture* texPointLight = nullptr;
	Texture* texFourAngleStar = nullptr;

	Sound* soundShoot1 = nullptr;
	Sound* soundShoot2 = nullptr;
	Sound* soundShoot3 = nullptr;
	Sound* soundBiu = nullptr;
	Sound* soundMenuOK = nullptr;
	Sound* soundMenuSelect = nullptr;
	Sound* soundItem = nullptr;
	Sound* soundDamage00 = nullptr;
	Sound* soundDamage01 = nullptr;
	Sound* soundEnemyDie00 = nullptr;
	Sound* soundEnemyDie01 = nullptr;
	Sound* soundPlayerShoot = nullptr;
	Sound* soundBomb = nullptr;
	Sound* soundExplode = nullptr;

private:
	STGResources();

public:
	virtual ~STGResources();

	bool LoadTexTures();
	void UnloadTextures();

	bool LoadSounds();
	void UnloadSounds();
};

#endif