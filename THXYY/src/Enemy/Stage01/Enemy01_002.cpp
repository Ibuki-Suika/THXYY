#include "Enemy01_002.h"

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

	if (position.x <= -32)
	{
		MarkDestroy();
	}
}