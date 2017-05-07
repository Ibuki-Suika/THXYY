#include "STGUtil.h"
#include "STGEngine.h"

float STGUtil::GetAngleToPlayer(float x, float y)
{
	auto player = STGEngine::GetInstance()->GetPlayer();
	auto& playerPos = player->GetPosition();

	float dx = playerPos.x - x;
	float dy = playerPos.y - y;
	return Math::ToAngle(dx, dy);
}