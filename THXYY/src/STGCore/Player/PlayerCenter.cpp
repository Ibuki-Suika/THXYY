#include "PlayerCenter.h"
#include <STGEngine.h>

PlayerCenter::PlayerCenter()
{
	auto stgResources = STGResources::GetInstance();

	SetTexture(stgResources->texPlayerCenter);

	state = ARISE;

	alpha = 0.0f;
}

PlayerCenter::~PlayerCenter()
{
}

void PlayerCenter::Update()
{
	Sprite::Update();

	auto engine = STGEngine::GetInstance();
	auto scene = engine->GetGameScene();
	auto player = engine->GetPlayer();

	Vector3f pos = player->GetPosition();
	pos.z = 1.0f;
	SetPosition(pos);

	if (state == ARISE)
	{
		alpha += 1.0f / ARISE_TIME;
		if (alpha >= 1.0f)
		{
			state = NORMAL;
			alpha = 1.0f;
		}
	}
	else if (state == DISAPPEAR)
	{
		alpha -= 1.0f / DISAPPEAR_TIME;
		if (alpha < 0.0f)
		{
			MarkDestroy();
		}
	}
}

void PlayerCenter::Disappear()
{
	state = DISAPPEAR;
}