#pragma once

#include "../../STGCore/STGCore.h"

class Enemy01_001 : public BlueFairy01
{
private:
	int frame;
	int frame_shoot = 0;
	int shoot_count = 0;

public:
	Enemy01_001();
	virtual ~Enemy01_001();

	virtual void Update() override;
};