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
	shoot_count++;
	if (shoot_count < 3 && frame_shoot == 0.5 * Stage01::FPB)
	{
		frame_shoot = 0;
		shoot_count++;

		for (int i = 0; i < 8; i++)
		{
			Bullet* bullet = new Bullet();
			bullet->SetType(new SmallJadeBlue());
			bullet->SetPosition(position.x, position.y);
			bullet->SetSpeed(5);
			bullet->SetAngle(72 * i + STGUtil::GetAngleToPlayer(this->position.x, this->position.y));
			bullet->AddTween(new SpeedTo(2, 30, Tweener::SIMPLE));

			engine->ShootBullet(bullet, true, 2);
		}
	}

	if (position.x >= 416)
	{
		MarkDestroy();
	}
}