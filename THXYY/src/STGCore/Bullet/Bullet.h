#ifndef BULLET_H
#define BULLET_H

#include <THEngine.h>
#include "BulletColor.h"
using namespace THEngine;

class BulletType;

class Bullet : public Sprite
{
protected:
	Ptr<BulletType> bulletType;
	BulletColor bulletColor;

	bool dirSame;                //朝向与运动方向相同
	bool autoDelete = true;             //出屏即消

public:
	Bullet();
	virtual ~Bullet();

	inline void SetBulletColor(BulletColor bulletColor) { this->bulletColor = bulletColor; }
	inline BulletColor GetBulletColor() const { return this->bulletColor; }

	bool Hit(float playerX, float playerY, float playerRadius);

	inline void SetPosition(float x, float y)
	{
		Sprite::SetPosition(Vector3f(x, y, 5.0f));
	}

	inline void SetDirSame(bool dirSame) { this->dirSame = dirSame; }
	inline void SetAutoDelete(bool autoDelete) { this->autoDelete = autoDelete; }

	void SetType(Ptr<BulletType> type);

	virtual void Update() override;

	void OnDie();
};

#endif