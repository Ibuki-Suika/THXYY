#ifndef STGRESOURCES_H
#define STGRESOURCES_H

#include <THEngine.h>

using namespace THEngine;

class STGResources : public Object, public Singleton<STGResources>
{
	friend class Singleton<STGResources>;
public:
	Ptr<Texture> texPlayerCenter;
	Ptr<Texture> texEnemy01;
	Ptr<Texture> texBullet01;
	Ptr<Texture> texBullet02;
	Ptr<Texture> texBullet03;
	Ptr<Texture> texBullet04;
	Ptr<Texture> texReimu;
	Ptr<Texture> texEffBase;
	Ptr<Texture> texPointLight;
	Ptr<Texture> texFourAngleStar;

	Ptr<Sound> soundShoot1;
	Ptr<Sound> soundShoot2;
	Ptr<Sound> soundShoot3;
	Ptr<Sound> soundBiu;
	Ptr<Sound> soundMenuOK;
	Ptr<Sound> soundMenuSelect;
	Ptr<Sound> soundItem;
	Ptr<Sound> soundDamage00;
	Ptr<Sound> soundDamage01;
	Ptr<Sound> soundEnemyDie00;
	Ptr<Sound> soundEnemyDie01;
	Ptr<Sound> soundPlayerShoot;
	Ptr<Sound> soundBomb;
	Ptr<Sound> soundExplode;

private:
	STGResources() = default;

public:
	virtual ~STGResources();

	bool LoadTexTures();
	void UnloadTextures();

	bool LoadSounds();
	void UnloadSounds();
};

#endif