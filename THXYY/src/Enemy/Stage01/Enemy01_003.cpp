#include "Enemy01_003.h"

Enemy01_003::Enemy01_003()
{
	SetLife(6000);

	SetItem(POWER_SMALL, 20);
	SetItem(SCORE, 20);
}

Enemy01_003::~Enemy01_003()
{
}

void Enemy01_003::Update()
{
	ButterFly::Update();

	frame++;

	if (frame == 150)
	{
		float radius = 120;
		for (int i = 0; i < 5; i++)
		{
			float angle = 90 + i * 72;
			float rad = Math::ToRad(angle);
			float dx = radius * cos(rad);
			float dy = radius * sin(rad);
			Shoot(this->position.x + dx, this->position.y + dy, i % 2 ? GREEN : PURPLE);
		}
	}

	if (frame > 300 && this->position.y > 480)
	{
		MarkDestroy();
	}
}

void Enemy01_003::Shoot(float x, float y, ShootColor color)
{
	auto engine = STGEngine::GetInstance();

	float baseAngle = engine->Random(0, 359);
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Ptr<Bullet> bullet = Ptr<Bullet>::New();
			bullet->SetPosition(x, y);
			bullet->SetSpeed(0.5 + j);
			bullet->SetAngle(baseAngle + 15 * i + 2 * j);
			bullet->AddTween(Ptr<SpeedTo>::New(0.0f, 45, Tweener::SIMPLE).Get());
			bullet->GetScheduler()->AddFrameTimer(90, [bullet]() {
				bullet->SetAngle(bullet->GetAngle() + 60);
				bullet->AddTween(Ptr<SpeedTo>::New(-1.5f, 45, Tweener::SIMPLE).Get());
			});

			switch (color)
			{
			case GREEN:
				bullet->SetType(Ptr<LinDanGreen>::New().Get());
				break;
			case PURPLE:
				bullet->SetType(Ptr<LinDanPurple>::New().Get());
				break;
			}

			engine->ShootBullet(bullet);
		}
	}
}