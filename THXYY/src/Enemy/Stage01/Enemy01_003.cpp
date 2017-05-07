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

	if (frame == 300)
	{
		MarkDestroy();
	}
}