#include "ReimuBomb1.h"

ReimuBomb1::ReimuBomb1()
{
	auto stgResources = STGResources::GetInstance();

	SetTexture(stgResources->texReimu);
	SetTexRect(Rect(64, 128, 192, 256));

	position.z = 5.0f;

	subRed = Ptr<SubSprite>::New();
	subRed->SetColor(Vector3f(1.0f, 0.0f, 0.0f));
	AddChild(subRed.Get());

	subGreen = Ptr<SubSprite>::New();
	subGreen->SetColor(Vector3f(0.0f, 1.0f, 0.0f));
	AddChild(subGreen.Get());

	subBlue = Ptr<SubSprite>::New();
	subBlue->SetColor(Vector3f(0.0f, 0.0f, 1.0f));
	AddChild(subBlue.Get());

	int angle = STGEngine::GetInstance()->Random(0, 359);

	subRed->SetSpeed(1.0f);
	subRed->SetAngle(angle);
	subRed->SetAcAngle(18.0f);

	subGreen->SetSpeed(1.0f);
	subGreen->SetAngle(angle + 120.0f);
	subGreen->SetAcAngle(18.0f);

	subBlue->SetSpeed(1.0f);
	subBlue->SetAngle(angle + 240.0f);
	subBlue->SetAcAngle(18.0f);

	SetAlpha(0);
}

ReimuBomb1::~ReimuBomb1()
{
}

void ReimuBomb1::Update()
{
	Sprite::Update();

	if (explode)
	{
		return;
	}

	if (lifeTime == 0)
	{
		Explode();
		explode = true;
	}
	else
	{
		lifeTime--;
	}

	frame++;

	auto engine = STGEngine::GetInstance();
	auto player = engine->GetPlayer();

	if (frameAttack == 0 && beginAttack == false)
	{
		beginAttack = true;
		SetSpeed(8.0f);
		SetAngle(initialAngle - 90);
	}
	else
	{
		frameAttack--;
	}

	if (frame <= 20)
	{
		float scale = 1.5f * frame / 20.0f;
		SetScale(scale, scale);
	}

	if (beginAttack == false)
	{
		float r = 1.0f * frame;
		initialAngle -= 6;
		offset.x = r * cos(Math::ToRad(initialAngle));
		offset.y = r * sin(Math::ToRad(initialAngle));

		auto playerPos = player->GetPosition();
		this->position.x = playerPos.x + offset.x;
		this->position.y = playerPos.y + offset.y;
	}
	else
	{
		Attack();
	}

	CalcDamage();
	ClearBullet();
}

void ReimuBomb1::Attack()
{
	auto engine = STGEngine::GetInstance();
	auto enemyList = engine->GetEnemyList();

	Ptr<Enemy> nearestEnemy = nullptr;
	float minDist = 999999.0f;
	auto iter = enemyList->GetIterator();
	while (iter->HasNext())
	{
		auto enemy = iter->Next();
		auto enemyPos = enemy->GetPosition();
		auto diffX = enemyPos.x - position.x;
		auto diffY = enemyPos.y - position.y;
		float dist = sqrt(diffX * diffX + diffY * diffY);
		if (dist < minDist)
		{
			nearestEnemy = enemy;
			minDist = dist;
		}
	}

	if (nearestEnemy)
	{
		auto enemyPos = nearestEnemy->GetPosition();
		auto diffX = enemyPos.x - position.x;
		auto diffY = enemyPos.y - position.y;

		auto wantAngle = Math::ToAngle(diffX, diffY);
		auto myAngle = Math::StandardizeAngle(angle);
		double diffAngle = fabs(wantAngle - myAngle);
		diffAngle = diffAngle <= 180 ? diffAngle : 360 - diffAngle;
		if (diffAngle > 5)
		{
			if (myAngle < 180)
			{
				if (wantAngle < 180 + myAngle)
				{
					if (wantAngle > myAngle)
					{
						angle += 5;
					}
					else
					{
						angle -= 5;
					}
				}
				else
				{
					angle -= 5;
				}
			}
			else
			{
				if (wantAngle < myAngle - 180)
				{
					angle += 5;
				}
				else
				{
					if (wantAngle > myAngle)
					{
						angle += 5;
					}
					else
					{
						angle -= 5;
					}
				}
			}
		}
		else
		{
			SetAngle(wantAngle);
		}
	}

	else
	{
		if (speed > 1)
		{
			speed -= 0.2f;
		}
	}
}

void ReimuBomb1::CalcDamage()
{
	auto engine = STGEngine::GetInstance();
	auto enemyList = engine->GetEnemyList();

	auto iter = enemyList->GetIterator();
	while (iter->HasNext())
	{
		auto enemy = iter->Next();
		auto enemyPos = enemy->GetPosition();
		auto diffX = enemyPos.x - position.x;
		auto diffY = enemyPos.y - position.y;

		if (fabs(diffX) < 32 && fabs(diffY) < 32)
		{
			enemy->OnHitten(60);
		}
	}
}

void ReimuBomb1::Explode()
{
	auto stgResources = STGResources::GetInstance();

	AddTween(Ptr<FadeOut>::New(16, Tweener::EASE_OUT).Get());

	stgResources->soundShoot1->Play();
}

void ReimuBomb1::ClearBullet()
{
	auto engine = STGEngine::GetInstance();
	auto bulletList = engine->GetBulletList();

	auto iter = bulletList->GetIterator();
	while (iter->HasNext())
	{
		auto bullet = iter->Next();
		auto bulletPos = bullet->GetPosition();
		auto diffX = bulletPos.x - position.x;
		auto diffY = bulletPos.y - position.y;

		if (diffX * diffX + diffY * diffY < 32 * 32)
		{
			bullet->OnDie();
		}
	}
}

void ReimuBomb1::Draw()
{
	auto renderState = Device::GetInstance()->GetRenderState();

	Sprite::Draw();
}

///////////////////////////////////////////
ReimuBomb1::SubSprite::SubSprite()
{
	auto stgResources = STGResources::GetInstance();

	SetTexture(stgResources->texReimu);
	SetTexRect(Rect(64, 128, 192, 256));
	SetBlendMode(BlendMode::ADD);

	position.z = 10.0f;
}

ReimuBomb1::SubSprite::~SubSprite()
{
}

void ReimuBomb1::SubSprite::Update()
{
	Sprite::Update();

	frame++;

	if (frame <= 20)
	{
		float scale = 1.5f * frame / 20.0f;
		SetScale(scale, scale);
	}

	if (frame == 200)
	{
		AddTween(Ptr<ScaleTo>::New(Vector3f(8.0f, 8.0f, 1.0f), 16, Tweener::EASE_OUT).Get());
		AddTween(Ptr<FadeOut>::New(16, Tweener::EASE_OUT).Get());
		SetSpeed(0);
		SetAcSpeed(0);
	}
}