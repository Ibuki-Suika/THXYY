#ifndef ENEMY01_003_H
#define ENEMY01_003_H

#include "../../STGCore/STGCore.h"

class Enemy01_003 : public ButterFly
{
	int frame = 0;

	enum ShootColor
	{
		GREEN,
		PURPLE
	};

public:
	Enemy01_003();
	virtual ~Enemy01_003();

	virtual void Update() override;

	void Shoot(float x, float y, ShootColor color);
};

#endif