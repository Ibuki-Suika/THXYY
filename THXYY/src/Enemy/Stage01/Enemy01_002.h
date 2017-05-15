#ifndef ENEMY01_002_H
#define ENEMY01_002_H

#include "../../STGCore/STGCore.h"

class Enemy01_002 : public RedFairy01
{
private:
	int frame = 0;
	int frame_shoot = 0;
	int shoot_count = 0;

public:
	Enemy01_002();
	virtual ~Enemy01_002();

	virtual void Update() override;
};

#endif