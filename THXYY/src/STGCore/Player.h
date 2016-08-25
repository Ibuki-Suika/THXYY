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

private:
	PlayerCenter* center;
	int frame_counter;              //����֡������
	int frame_invincible = 0;       //�޵�֡������
	int invincible_shrink_counter = 0;         //�޵���˸������

protected:
	float hiSpeed;
	float lowSpeed;

	float radius;

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