#include "Enemy01_002.h"
#include "../../Stage/Stage01/Stage01.h"

Enemy01_002::Enemy01_002()
{
	life = 10;

	SetItem(POWER_SMALL, 8);
	SetItem(SCORE, 8);

	SetPosition(440, 400);
}

Enemy01_002::~Enemy01_002()
{
}

void Enemy01_002::Update()
{
	RedFairy01::Update();

	auto engine = STGEngine::GetInstance();

	frame++;
	frame_shoot++;
	if (shoot_count < 3 && frame_shoot == 0.5 * Stage01::FPB)
	{
		frame_shoot = 0;
		shoot_count++;
		for (int i = 0; i < 12; i++)
		{
			Bullet* bullet = new Bullet();
			bullet->SetType(new SmallJadeRed());
			bullet->SetPosition(position.x, position.y);
			bullet->SetSpeed(8);
			bullet->SetAngle(30 * i + STGUtil::GetAngleToPlayer(this->position.x, this->position.y) + 15);
			bullet->AddTween(new SpeedTo(5, 30, Tweener::SIMPLE));

			engine->ShootBullet(bullet, true, 2);
		}
	}

	if (position.x <= -32)
	{
		MarkDestroy();
	}
}