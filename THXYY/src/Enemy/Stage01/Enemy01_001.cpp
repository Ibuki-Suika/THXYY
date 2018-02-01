#include "Enemy01_001.h"
#include "../../Stage/Stage01/Stage01.h"

Enemy01_001::Enemy01_001()
{
	frame = 0;
	life = 10;

	SetItem(POWER_SMALL, 8);
	SetItem(SCORE, 8);
}

Enemy01_001::~Enemy01_001()
{
}

void Enemy01_001::Update()
{
	BlueFairy01::Update();

	auto engine = STGEngine::GetInstance();

	frame++;
	frame_shoot++;
	if (shoot_count < 3 && frame_shoot == 0.5 * Stage01::FPB)
	{
		frame_shoot = 0;
		shoot_count++;

		for (int i = 0; i < 12; i++)
		{
			Ptr<Bullet> bullet = Ptr<Bullet>::New();
			bullet->SetType(Ptr<SmallJadeBlue>::New().Get());
			bullet->SetPosition(position.x, position.y);
			bullet->SetSpeed(8);
			bullet->SetAngle(30 * i + STGUtil::GetAngleToPlayer(this->position.x, this->position.y));
			bullet->AddTween(Ptr<SpeedTo>::New(5, 30, Tweener::SIMPLE).Get());

			engine->ShootBullet(bullet, true, 2);
		}
	}

	if (position.x >= 416)
	{
		MarkDestroy();
	}
}