#ifndef BULLET_TYPE_H
#define BULLET_TYPE_H

#include <THEngine.h>
#include "BulletColor.h"
using namespace THEngine;

class Bullet;

class BulletType : public Object
{
protected:
	Bullet* bullet = nullptr;  //don't use smart pointer here

	inline void SetBullet(Bullet* bullet) { this->bullet = bullet; }

public:
	BulletType() = default;
	virtual ~BulletType() = default;

	virtual bool Hit(float xPlayer, float yPlayer, float radius) const = 0;
	virtual Ptr<Texture> GetTexture() const = 0;
	virtual Rect GetTexRect() const = 0;
	virtual BulletColor GetBulletColor() const = 0;

	friend class Bullet;
};

#endif
