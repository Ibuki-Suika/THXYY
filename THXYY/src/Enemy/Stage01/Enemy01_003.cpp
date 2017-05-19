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
			Bullet* bullet = new Bullet();
			bullet->SetPosition(x, y);
			bullet->SetSpeed(0.5 + j);
			bullet->SetAngle(baseAngle + 15 * i + 2 * j);
			bullet->AddTween(new SpeedTo(0.0f, 45, Tweener::SIMPLE));
			bullet->GetScheduler()->AddFrameTimer(90, [bullet]() {
				bullet->SetAngle(bullet->GetAngle() + 60);
				bullet->AddTween(new SpeedTo(-1.5f, 45, Tweener::SIMPLE));
			});

			switch (color)
			{
			case GREEN:
				bullet->SetType(new LinDanGreen());
				break;
			case PURPLE:
				bullet->SetType(new LinDanPurple());
				break;
			}

			engine->ShootBullet(bullet);
		}
	}
}