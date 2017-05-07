#ifndef HIT_CHECHER_H
#define HIT_CHECKER_H

#include <THEngine.h>
using namespace THEngine;

class HitChecker
{
public:
	static bool HitRound(Sprite* object, const Vector2f& center,
		float radius, float playerX, float playerY, float playerRadius);

	static bool HitSquare(Sprite* object, const Vector2f& center,
		const Vector2f& halfRange, float playerX, float playerY, float playerRadius);
};

#endif