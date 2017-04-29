#include "STGResources.h"

#define STGRES_LOAD_TEXTURE(texture, path) \
	texture = manager->CreateTextureFromFile(path); \
	if (texture == nullptr) \
	{   \
		return false;  \
	}  \
	texture->Retain();

STGResources* STGResources::instance = nullptr;

STGResources::STGResources()
{
	texPlayerCenter = nullptr;
	texEnemy01 = nullptr;
	texBullet01 = nullptr;
}

STGResources::~STGResources()
{
	UnloadTextures();
	UnloadSounds();
}

STGResources* STGResources::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new STGResources();
	}
	return instance;
}

bool STGResources::LoadTexTures()
{
	auto manager = AssetManager::GetInstance();

	THLog("加载STG纹理。。。");

	STGRES_LOAD_TEXTURE(texPlayerCenter, "res/player/center.png");
	STGRES_LOAD_TEXTURE(texEnemy01, "res/enemy/enemy01.png");
	STGRES_LOAD_TEXTURE(texBullet01, "res/bullet/bullet1.png");
	STGRES_LOAD_TEXTURE(texBullet02, "res/bullet/bullet2.png");
	STGRES_LOAD_TEXTURE(texBullet03, "res/bullet/bullet3.png");
	STGRES_LOAD_TEXTURE(texBullet04, "res/bullet/bullet4.png");
	STGRES_LOAD_TEXTURE(texReimu, "res/player/reimu.png");
	STGRES_LOAD_TEXTURE(texEffBase, "res/effect/eff_base.png");
	STGRES_LOAD_TEXTURE(texPointLight, "res/effect/point_light.png");
	STGRES_LOAD_TEXTURE(texFourAngleStar, "res/effect/four_angle_star.png");

	THLog("加载STG纹理成功。");

	return true;
}

void STGResources::UnloadTextures()
{
	auto manager = AssetManager::GetInstance();

	THLog("释放STG纹理。");

	TH_SAFE_RELEASE(texPlayerCenter);
	TH_SAFE_RELEASE(texEnemy01);
	TH_SAFE_RELEASE(texBullet01);
	TH_SAFE_RELEASE(texBullet02);
	TH_SAFE_RELEASE(texBullet03);
	TH_SAFE_RELEASE(texBullet04);
	TH_SAFE_RELEASE(texReimu);
	TH_SAFE_RELEASE(texEffBase);
	TH_SAFE_RELEASE(texPointLight);
	TH_SAFE_RELEASE(texFourAngleStar);

	texPlayerCenter = nullptr;
	texEnemy01 = nullptr;
	texBullet01 = nullptr;
	texBullet02 = nullptr;
	texBullet03 = nullptr;
	texBullet04 = nullptr;
	texReimu = nullptr;
	texEffBase = nullptr;
	texPointLight = nullptr;
	texFourAngleStar = nullptr;
}

bool STGResources::LoadSounds()
{
	auto audio = Audio::GetInstance();

	soundShoot1 = audio->CreateSound("sound/se_tan00.wav");
	if (soundShoot1 == nullptr)
	{
		return false;
	}

	soundShoot2 = audio->CreateSound("sound/se_tan01.wav");
	if (soundShoot2 == nullptr)
	{
		return false;
	}

	soundShoot3 = audio->CreateSound("sound/se_tan02.wav");
	if (soundShoot3 == nullptr)
	{
		return false;
	}

	soundBiu = audio->CreateSound("sound/se_pldead00.wav");
	if (soundBiu == nullptr)
	{
		return false;
	}

	soundMenuOK = audio->CreateSound("sound/se_ok00.wav");
	if (soundMenuOK == nullptr)
	{
		return false;
	}

	soundMenuSelect = audio->CreateSound("sound/se_select00.wav");
	if (soundMenuSelect == nullptr)
	{
		return false;
	}

	soundItem = audio->CreateSound("sound/se_item00.wav");
	if (soundItem == nullptr)
	{
		return false;
	}

	soundDamage00 = audio->CreateSound("sound/se_damage00.wav");
	if (soundDamage00 == nullptr)
	{
		return false;
	}

	soundDamage01 = audio->CreateSound("sound/se_damage01.wav");
	if (soundDamage01 == nullptr)
	{
		return false;
	}

	soundEnemyDie00 = audio->CreateSound("sound/se_enep00.wav");
	if (soundEnemyDie00 == nullptr)
	{
		return false;
	}

	soundEnemyDie01 = audio->CreateSound("sound/se_enep01.wav");
	if (soundEnemyDie01 == nullptr)
	{
		return false;
	}

	soundPlayerShoot = audio->CreateSound("sound/se_plst00.wav");
	if (soundPlayerShoot == nullptr)
	{
		return false;
	}

	soundBomb = audio->CreateSound("sound/se_nep00.wav");
	if (soundBomb == nullptr)
	{
		return false;
	}

	soundExplode = audio->CreateSound("sound/se_cat00.wav");
	if (soundExplode == nullptr)
	{
		return false;
	}

	return true;
}

void STGResources::UnloadSounds()
{
	auto audio = Audio::GetInstance();

	audio->DestroySound(soundShoot1);
	audio->DestroySound(soundShoot2);
	audio->DestroySound(soundShoot3);
	audio->DestroySound(soundBiu);
	audio->DestroySound(soundMenuOK);
	audio->DestroySound(soundMenuSelect);
	audio->DestroySound(soundItem);
	audio->DestroySound(soundDamage00);
	audio->DestroySound(soundDamage01);
	audio->DestroySound(soundEnemyDie00);
	audio->DestroySound(soundEnemyDie01);
	audio->DestroySound(soundPlayerShoot);
	audio->DestroySound(soundBomb);
	audio->DestroySound(soundExplode);

	soundShoot1 = nullptr;
	soundShoot2 = nullptr;
	soundShoot3 = nullptr;
	soundBiu = nullptr;
	soundMenuOK = nullptr;
	soundMenuSelect = nullptr;
	soundItem = nullptr;
	soundDamage00 = nullptr;
	soundDamage01 = nullptr;
	soundEnemyDie00 = nullptr;
	soundEnemyDie01 = nullptr;
	soundPlayerShoot = nullptr;
	soundBomb = nullptr;
	soundExplode = nullptr;
}