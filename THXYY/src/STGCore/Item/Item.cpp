#include "Item.h"
#include "../STGEngine.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Update()
{
	frame++;

	auto engine = STGEngine::GetInstance();

	auto player = engine->GetPlayer();
	auto playerPos = player->GetPosition();

	auto difX = position.x - playerPos.x;
	auto difY = position.y - playerPos.y;

	if (goToPlayer && player->IsDead() == false)
	{
		if (GetSpeed() > 7.0f)
		{
			SetSpeed(7.0f);
			SetAcSpeed(0.0f);
		}
		if (difX*difX + difY*difY < 64)
		{
			OnGot();
			return;
		}
		SetAngle(Math::ToAngle(-difX, -difY));
		SetRotation(GetAngle());
	}

	Sprite::Update();

	if (goToPlayer && player->IsDead() == false)   //Already disposed
	{
		return;
	}

	if (frame > 40)
	{
		SetAngle(270.0f);
		SetAcSpeed(0.05f);
		SetRotation(0.0f);
	}

	if (GetSpeed() > 1.5f)
	{
		SetSpeed(1.5f);
		SetAcSpeed(0.0f);
	}

	if (player->IsDead())
	{
		return;
	}

	float dist;
	if (player->IsHiSpeed())
	{
		dist = hitRange + player->GetHiSpeedItemRange();
		if (difX*difX + difY*difY < dist*dist)
		{
			GoToPlayer();
		}
	}
	else
	{
		dist = hitRange + player->GetLowSpeedItemRange();
		if (difX*difX + difY*difY < dist*dist)
		{
			GoToPlayer();
		}
	}

	if (playerPos.y > player->GetItemGetHeight())
	{
		gotFromHigh = true;
		GoToPlayer();
	}

	if (position.y < -32 || position.y > 480)
	{
		MarkDestroy();
	}
}

void Item::GoToPlayer()
{
	goToPlayer = true;
	ClearTweens();
	SetAcSpeed(1.0f);
}

void Item::OnGot()
{
	auto stgResources = STGResources::GetInstance();
	stgResources->soundItem->Play();

	MarkDestroy();
}