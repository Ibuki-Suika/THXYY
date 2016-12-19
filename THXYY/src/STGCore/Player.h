#ifndef PLAYER_H
#define PLAYER_H

#include <THEngine.h>
#include "PlayerCenter.h"

using namespace THEngine;

class Player : public Sprite
{
public:
	enum MotionState
	{
		STATIC,
		LEFT,
		LEFT_UP,
		LEFT_DOWN,
		UP,
		DOWN,
		RIGHT,
		RIGHT_UP,
		RIGHT_DOWN
	};

	enum State
	{
		NORMAL,
		DETERMINE_DEATH,            //����
		DYING,                      //MISS��
		REINTERING                  //MISS�����µǳ�
	};

	static const int ANIM_INTERVAL = 5;
	static const int TURN_INTERVAL = 2;

private:
	PlayerCenter* center;
	int frame_counter;              //����֡������
	int frame_invincible = 0;       //�޵�֡������
	int invincible_shrink_counter = 0;         //�޵���˸������

protected:
	float hiSpeed;
	float lowSpeed;

	float radius = 3.0f;                //�ж���뾶
	float hiSpeedItemRange = 24.0f;          //����ʱȡ�õ��߷�Χ
	float lowSpeedItemRange = 32.0f;         //����ʱȡ�õ��߷�Χ
	float itemGetHeight = 324.0f;                //���߻����߸߶�

	bool isHiSpeed;
	bool invincible;          //�޵�

	float determineDeathTime;              //����ʱ��

	MotionState motionState;
	State state;

public:
	Player();
	virtual ~Player();

	inline void SetPosition(float x, float y)
	{
		Sprite::SetPosition(Vector3f(x, y, 20.0f));
	}

	inline void SetHiSpeed(float hiSpeed) { this->hiSpeed = hiSpeed; }
	inline float GetHiSpeed() { return hiSpeed; }

	inline void SetLowSpeed(float lowSpeed) { this->lowSpeed = lowSpeed; }
	inline float GetLowSpeed() { return lowSpeed; }

	inline void SetRadius(float radius) { this->radius = radius; }
	inline float GetRadius() { return radius; }

	inline void SetHiSpeedItemRange(float range) { hiSpeedItemRange = range; }
	inline float GetHiSpeedItemRange() { return hiSpeedItemRange; }

	inline void SetLowSpeedItemRange(float range) { lowSpeedItemRange = range; }
	inline float GetLowSpeedItemRange() { return lowSpeedItemRange; }

	inline void SetItemGetHeight(float height) { itemGetHeight = height; }
	inline float GetItemGetHeight() { return itemGetHeight; }

	inline bool IsHiSpeed() { return isHiSpeed; }

	inline bool IsDead() { return state == DYING; }

	virtual void Update() override;

	void Move();
	void Hitten();
	void Biu();

	bool IsDamageable();

	inline bool IsInvincible() { return invincible; }
	inline void SetInvincible(int time)
	{
		invincible = true;
		frame_invincible = time;
		invincible_shrink_counter = 0;
	}

	virtual void Fire() = 0;
	virtual void Bomb() = 0;
};

#endif