#pragma once

#include <THEngine.h>
#include "../Bullet/Bullet.h"

using namespace THEngine;

class BulletFog : public Sprite
{
protected:
	int frame = 0;
	Ptr<Bullet> bullet;

public:
	BulletFog(Ptr<Bullet> bullet);
	virtual ~BulletFog();

	virtual void Update() override;
};