#include "ReimuBomb1.h"

ReimuBomb1::ReimuBomb1()
{
	auto stgResources = STGResources::GetInstance();

	SetTexture(stgResources->texReimu);
	SetTexRect(Rect(64, 128, 192, 256));

	position.z = 5.0f;

	subRed = new SubSprite();
	subRed->SetColor(Vector3f(1.0f, 0.0f, 0.0f));
	AddChild(subRed);

	subGreen = new SubSprite();
	subGreen->SetColor(Vector3f(0.0f, 1.0f, 0.0f));
	AddChild(subGreen);

	subBlue = new SubSprite();
	subBlue->SetColor(Vector3f(0.0f, 0.0f, 1.0f));
	AddChild(subBlue);

	int angle = Random(0, 359);

	subRed->SetSpeed(3.0f);
	subRed->SetAngle(angle);
	subRed->SetAcAngle(18.0f);

	subGreen->SetSpeed(3.0f);
	subGreen->SetAngle(angle + 120.0f);
	subGreen->SetAcAngle(18.0f);

	subBlue->SetSpeed(3.0f);
	subBlue->SetAngle(angle + 240.0f);
	subBlue->SetAcAngle(18.0f);

	this->renderTexture = AssetManager::GetInstance()->CreateRenderTexture(128, 128);
}

ReimuBomb1::~ReimuBomb1()
{
	AssetManager::GetInstance()->DestroyTexture(this->renderTexture);
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
		offset.x = r * cos(ToRad(initialAngle));
		offset.y = r * sin(ToRad(initialAngle));

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

	Enemy* nearestEnemy = nullptr;
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

		auto wantAngle = ToAngle(diffX, diffY);
		auto myAngle = StandardizeAngle(angle);
		double diffAngle = fabs(wantAngle - myAngle);
		diffAngle = diffAngle <= 180 ? diffAngle : 360 - diffAngle;
		if ( diffAngle > 5)
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

	AddTween(new ScaleTo(Vector3f(8.0f, 8.0f, 1.0f), 16, Tweener::EASE_OUT));
	AddTween(new FadeOut(16, Tweener::EASE_OUT));

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
	auto app = Application::GetInstance();
	auto renderState = app->GetRenderState();

	Sprite::Draw();
}

///////////////////////////////////////////
ReimuBomb1::SubSprite::SubSprite()
{
	auto stgResources = STGResources::GetInstance();

	SetTexture(stgResources->texReimu);
	SetTexRect(Rect(64, 128, 192, 256));
	SetAlpha(0.33f);

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
		MarkDestroy();
	}
}



