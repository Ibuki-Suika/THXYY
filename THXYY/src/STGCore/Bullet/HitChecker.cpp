#include "HitChecker.h"

bool HitChecker::HitRound(Sprite* object, const Vector2f& center,
	float radius, float playerX, float playerY, float playerRadius)
{
	float r = playerRadius + radius;
	Vector2f playerCenter(playerX - object->GetPosition().x, playerY - object->GetPosition().y);
	playerCenter = Math::VecRotate2D(playerCenter, -object->GetRotation());
	playerCenter.x -= center.x;
	playerCenter.y -= center.y;
	return playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y < r * r;
}

bool HitChecker::HitSquare(Sprite* object, const Vector2f& center,
	const Vector2f& halfRange, float playerX, float playerY, float playerRadius)
{
	Vector2f playerCenter(playerX - object->GetPosition().x, playerY - object->GetPosition().y);
	playerCenter = Math::VecRotate2D(playerCenter, -object->GetRotation());
	playerCenter.x -= center.x;
	playerCenter.y -= center.y;
	return (fabs(playerCenter.x) < playerRadius + halfRange.x)
		&& (fabs(playerCenter.y) < playerRadius + halfRange.y);
}