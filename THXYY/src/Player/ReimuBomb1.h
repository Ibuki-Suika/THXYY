#ifndef REIMU_BOMB1_H
#define REIMU_BOMB1_H

#include "../STGCore/STGCore.h"

class ReimuBomb1 : public Sprite
{
private:
	class SubSprite;
	
private:
	int frame = 0;
	int lifeTime = 200;
	int frameAttack;      //多少帧后开始索敌
	float initialAngle = 0;

	bool beginAttack = false;
	bool explode = false;

	Vector2f offset = Vector2f(0.0f, 0.0f);

	Ptr<SubSprite> subRed = nullptr;
	Ptr<SubSprite> subGreen = nullptr;
	Ptr<SubSprite> subBlue = nullptr;

private:
	void Attack();
	void CalcDamage();
	void Explode();
	void ClearBullet();

public:
	ReimuBomb1();
	virtual ~ReimuBomb1();

	virtual void Update() override;
	virtual void Draw() override;

	inline void SetInitialAngle(float angle) { initialAngle = angle; }

	inline void SetAttackFrame(int frame) { frameAttack = frame; }

private:
	class SubSprite : public Sprite
	{
	private:
		int frame = 0;

		float r = 0;
		float relativeAngle = 0;

	public:
		SubSprite();
		virtual ~SubSprite();

		virtual void Update() override;
	};

};

#endif