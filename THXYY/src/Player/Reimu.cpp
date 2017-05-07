#include "Reimu.h"
#include "ReimuBullet.h"
#include "ReimuBomb1.h"
#include "ReimuSubPlane.h"

Reimu::Reimu()
{
	auto stgResources = STGResources::GetInstance();

	frame = 0;
	frame_fire = 0;

	SetTexture(stgResources->texReimu);

	SetHiSpeed(4.5f);
	SetLowSpeed(2.0f);
	SetRadius(3.0f);

	const float radiusHigh = 45;

	subPlaneOffsetHigh[0][0] = Vector2f(0, radiusHigh);
	subPlaneOffsetHigh[1][0] = Vector2f(cos(Math::ToRad(45)) * radiusHigh, sin(Math::ToRad(45)) * radiusHigh);
	subPlaneOffsetHigh[1][1] = Vector2f(cos(Math::ToRad(135)) * radiusHigh, sin(Math::ToRad(135)) * radiusHigh);
	subPlaneOffsetHigh[2][0] = Vector2f(cos(Math::ToRad(45)) * radiusHigh, sin(Math::ToRad(45)) * radiusHigh);
	subPlaneOffsetHigh[2][1] = Vector2f(cos(Math::ToRad(90)) * radiusHigh, sin(Math::ToRad(90)) * radiusHigh);
	subPlaneOffsetHigh[2][2] = Vector2f(cos(Math::ToRad(135)) * radiusHigh, sin(Math::ToRad(135)) * radiusHigh);
	subPlaneOffsetHigh[3][0] = Vector2f(cos(Math::ToRad(45)) * radiusHigh, sin(Math::ToRad(45)) * radiusHigh);
	subPlaneOffsetHigh[3][1] = Vector2f(cos(Math::ToRad(75)) * radiusHigh, sin(Math::ToRad(75)) * radiusHigh);
	subPlaneOffsetHigh[3][2] = Vector2f(cos(Math::ToRad(105)) * radiusHigh, sin(Math::ToRad(105)) * radiusHigh);
	subPlaneOffsetHigh[3][3] = Vector2f(cos(Math::ToRad(135)) * radiusHigh, sin(Math::ToRad(135)) * radiusHigh);

	const float radiusLow = 30;

	subPlaneOffsetLow[0][0] = Vector2f(0, radiusLow);
	subPlaneOffsetLow[1][0] = Vector2f(cos(Math::ToRad(60)) * radiusLow, sin(Math::ToRad(60)) * radiusLow);
	subPlaneOffsetLow[1][1] = Vector2f(cos(Math::ToRad(120)) * radiusLow, sin(Math::ToRad(120)) * radiusLow);
	subPlaneOffsetLow[2][0] = Vector2f(cos(Math::ToRad(60)) * radiusLow, sin(Math::ToRad(60)) * radiusLow);
	subPlaneOffsetLow[2][1] = Vector2f(cos(Math::ToRad(90)) * radiusLow, sin(Math::ToRad(90)) * radiusLow);
	subPlaneOffsetLow[2][2] = Vector2f(cos(Math::ToRad(120)) * radiusLow, sin(Math::ToRad(120)) * radiusLow);
	subPlaneOffsetLow[3][0] = Vector2f(cos(Math::ToRad(60)) * radiusLow, sin(Math::ToRad(60)) * radiusLow);
	subPlaneOffsetLow[3][1] = Vector2f(cos(Math::ToRad(80)) * radiusLow, sin(Math::ToRad(80)) * radiusLow);
	subPlaneOffsetLow[3][2] = Vector2f(cos(Math::ToRad(100)) * radiusLow, sin(Math::ToRad(100)) * radiusLow);
	subPlaneOffsetLow[3][3] = Vector2f(cos(Math::ToRad(120)) * radiusLow, sin(Math::ToRad(120)) * radiusLow);
}

Reimu::~Reimu()
{
}

void Reimu::Update()
{
	Player::Update();

	frame++;

	if (motionState == STATIC || motionState == UP || motionState == DOWN)
	{
		if (frame >= 8 * ANIM_INTERVAL)
		{
			frame = 0;
		}
		int left = 32 * (frame / ANIM_INTERVAL);
		SetTexRect(Rect(left, left + 32, 0, 48));
	}
	else
	{
		if (motionState == LEFT || motionState == LEFT_UP || motionState == LEFT_DOWN)
		{
			if (prevState == STATIC || prevState == UP || prevState == DOWN)
			{
				frame = 0;
			}
			if (frame >= 8 * ANIM_INTERVAL)
			{
				frame = 4 * ANIM_INTERVAL;
			}
			int left = 32 * (frame / ANIM_INTERVAL);
			SetTexRect(Rect(left, left + 32, 48, 96));
		}
		else if (motionState == RIGHT || motionState == RIGHT_UP || motionState == RIGHT_DOWN)
		{
			if (prevState == STATIC || prevState == UP || prevState == DOWN)
			{
				frame = 0;
			}
			if (frame >= 4 * ANIM_INTERVAL + 4 * TURN_INTERVAL)
			{
				frame = 4 * TURN_INTERVAL;
			}

			int left;

			if (frame < 4 * TURN_INTERVAL)
			{
				left = 32 * (frame / TURN_INTERVAL);
			}
			else
			{
				left = 32 * ((frame - 4 * TURN_INTERVAL) / ANIM_INTERVAL) + 128;
			}
			SetTexRect(Rect(left, left + 32, 96, 144));
		}
	}
	prevState = motionState;
}

void Reimu::Fire()
{
	Player::Fire();

	auto engine = STGEngine::GetInstance();

	if (frame_fire == 0)
	{
		STGResources::GetInstance()->soundPlayerShoot->Play();

		ReimuBullet* bullet1 = new ReimuBullet();
		bullet1->SetPosition(position.x - 7.0f, position.y);
		engine->ShootPlayerBullet(bullet1);

		ReimuBullet* bullet2 = new ReimuBullet();
		bullet2->SetPosition(position.x + 7.0f, position.y);
		engine->ShootPlayerBullet(bullet2);
	}

	frame_fire++;
	if (frame_fire == 3)
	{
		frame_fire = 0;
	}
}

void Reimu::Bomb()
{
	auto stgResources = STGResources::GetInstance();

	EnterBombState(210);
	SetInvincible(250);

	auto engine = STGEngine::GetInstance();

	for (int i = 0; i < 8; i++)
	{
		ReimuBomb1* bomb = new ReimuBomb1();
		bomb->SetInitialAngle(-45 * i + 7.5);
		bomb->SetAttackFrame(10 * i + 90);
		engine->AddObject(bomb);
	}

	stgResources->soundBomb->Play();
	stgResources->soundExplode->Play();
}

void Reimu::OnEnterLowSpeed()
{
	Player::OnEnterLowSpeed();

	int powerLevel = GetPowerLevel();
	auto iter = this->subPlaneList.GetIterator();
	int i = 0;
	while (iter->HasNext())
	{
		auto subPlane = iter->Next();
		subPlane->ClearTweens();
		subPlane->AddTween(new MoveTo(Vector3f(subPlaneOffsetLow[powerLevel - 1][i].x, subPlaneOffsetLow[powerLevel - 1][i].y, 0.0f),
			8, Tweener::EASE_OUT));
		i++;
	}
}

void Reimu::OnEnterHighSpeed()
{
	Player::OnEnterHighSpeed();

	int powerLevel = GetPowerLevel();
	auto iter = this->subPlaneList.GetIterator();
	int i = 0;
	while (iter->HasNext())
	{
		auto subPlane = iter->Next();
		subPlane->ClearTweens();
		subPlane->AddTween(new MoveTo(Vector3f(subPlaneOffsetHigh[powerLevel - 1][i].x, subPlaneOffsetHigh[powerLevel - 1][i].y, 0.0f),
			8, Tweener::EASE_OUT));
		i++;
	}
}

//Called in OnStart() to initialize subPlanes.
void Reimu::SetupSubPlanes()
{
	int powerLevel = GetPowerLevel();

	if (this->IsHiSpeed())
	{
		for (int i = 0; i < powerLevel; i++)
		{
			ReimuSubPlane* subPlane = new ReimuSubPlane();
			subPlane->SetPosition(Vector3f(subPlaneOffsetHigh[powerLevel - 1][i].x, subPlaneOffsetHigh[powerLevel - 1][i].y, 0.0f));
			AddSubPlane(subPlane);
		}
	}
	else
	{
		for (int i = 0; i < powerLevel; i++)
		{
			ReimuSubPlane* subPlane = new ReimuSubPlane();
			subPlane->SetPosition(Vector3f(subPlaneOffsetLow[powerLevel - 1][i].x, subPlaneOffsetLow[powerLevel - 1][i].y, 0.0f));
			AddSubPlane(subPlane);
		}
	}
}

void Reimu::OnPowerLevelChanged(int oldPowerLevel, int newPowerLevel)
{
	RemoveAllSubPlanes();
	SetupSubPlanes();
}