#include "BulletFog.h"
#include "../STGResources.h"
#include "../STGEngine.h"

static const int LIFE_TIME = 15;
static const int ARISE_TIME = 15;
static const float INITIAL_ALPHA = 0.0f;

BulletFog::BulletFog(Ptr<Bullet> bullet)
{
	auto texManager = STGResources::GetInstance();

	this->bullet = bullet;

	SetTexture(texManager->texBullet02);

	SetPosition(Vector3f(bullet->GetPosition().x, bullet->GetPosition().y, 2.0f));

	SetAlpha(INITIAL_ALPHA);
	SetScale(2.0f, 2.0f);

	switch (bullet->GetBulletColor())
	{
	case BulletColor::BULLET_RED:
		SetTexRect(Rect(0, 32, 160, 192));
		break;
	case BulletColor::BULLET_PURPLE:
		SetTexRect(Rect(32, 64, 160, 192));
		break;
	case BulletColor::BULLET_BLUE:
		SetTexRect(Rect(64, 96, 160, 192));
		break;
	case BulletColor::BULLET_TEAL:
		SetTexRect(Rect(96, 128, 160, 192));
		break;
	case BulletColor::BULLET_GREEN:
		SetTexRect(Rect(128, 160, 160, 192));
		break;
	case BulletColor::BULLET_YELLOW:
		SetTexRect(Rect(160, 192, 160, 192));
		break;
	case BulletColor::BULLET_ORANGE:
		SetTexRect(Rect(192, 224, 160, 192));
		break;
	case BulletColor::BULLET_GREY:
		SetTexRect(Rect(224, 256, 160, 192));
		break;
	default:
		SetTexRect(Rect(0, 0, 0, 0));
		break;
	}
}

BulletFog::~BulletFog()
{
}

void BulletFog::Update()
{
	Sprite::Update();

	frame++;

	if (frame < ARISE_TIME)
	{
		alpha += (1.0f - INITIAL_ALPHA) / ARISE_TIME;
	}

	SetScaleX(GetScaleX() - 1.5f / LIFE_TIME);
	SetScaleY(GetScaleY() - 1.5f / LIFE_TIME);

	if (frame == LIFE_TIME)
	{
		MarkDestroy();
		STGEngine::GetInstance()->AddBullet(bullet);
	}
}