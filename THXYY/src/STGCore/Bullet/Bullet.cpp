#include "Bullet.h"
#include "BulletType.h"
#include "../STGEngine.h"

Bullet::Bullet()
{
	dirSame = true;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Sprite::Update();

	auto engine = STGEngine::GetInstance();

	auto player = engine->GetPlayer();
	if (player->IsInvincible())
	{
		if (Hit(player->GetPosition().x, player->GetPosition().y, player->GetRadius()))
		{
			MarkDestroy();
		}
	}
	else if (player->IsDamageable())
	{
		if (Hit(player->GetPosition().x, player->GetPosition().y, player->GetRadius()))
		{
			player->Hitten();
			MarkDestroy();
		}
	}

	if (dirSame)
	{
		SetRotation(angle - 90);
	}

	if (autoDelete)
	{
		if (position.x < -32 || position.x > 416 || position.y < -32 || position.y > 480)
		{
			MarkDestroy();
		}
	}
}

void Bullet::OnDie()
{
	MarkDestroy();

	auto engine = STGEngine::GetInstance();
	auto stgResources = STGResources::GetInstance();

	Ptr<Particle3D> effect[1];
	for (int i = 0; i < 1; i++)
	{
		int effectLife = 40;

		effect[i] = Ptr<Particle3D>::New();
		effect[i]->SetTexture(stgResources->texFourAngleStar);
		effect[i]->SetPosition(position);
		effect[i]->SetLife(effectLife);

		switch (GetBulletColor())
		{
		case BulletColor::BULLET_RED:
			effect[i]->SetTexRect(Rect(0, 32, 0, 32));
			break;
		case BulletColor::BULLET_PURPLE:
			effect[i]->SetTexRect(Rect(32, 64, 0, 32));
			break;
		case BulletColor::BULLET_BLUE:
			effect[i]->SetTexRect(Rect(64, 96, 0, 32));
			break;
		case BulletColor::BULLET_TEAL:
			effect[i]->SetTexRect(Rect(96, 128, 0, 32));
			break;
		case BulletColor::BULLET_GREEN:
			effect[i]->SetTexRect(Rect(0, 32, 32, 64));
			break;
		case BulletColor::BULLET_YELLOW:
			effect[i]->SetTexRect(Rect(32, 64, 32, 64));
			break;
		case BulletColor::BULLET_ORANGE:
			effect[i]->SetTexRect(Rect(64, 96, 32, 64));
			break;
		case BulletColor::BULLET_GREY:
			effect[i]->SetTexRect(Rect(96, 128, 32, 64));
			break;
		}

		float effectAngle = Math::ToRad(engine->Random(0, 359));
		float dist = engine->Random(0, 20);

		float effectScale = engine->Random(20, 50) / 100.0f;
		effect[i]->SetScale(Vector3f(effectScale, effectScale, 1));

		effect[i]->SetRotatingAxis(Vector3f(engine->Random(0, 100), engine->Random(0, 100), engine->Random(0, 100)));
		effect[i]->SetRotatingSpeed(engine->Random(50, 100) / 10.0f);
		effect[i]->SetAlpha(0.6f);

		Ptr<TweenSequence> sequence = Ptr<TweenSequence>::New();
		sequence->AddTween(Ptr<Delay>::New(effectLife / 2).Get());
		sequence->AddTween(Ptr<ScaleTo>::New(Vector3f(0, 0, 1), 30, Tweener::SIMPLE).Get());
		effect[i]->AddTween(sequence.Get());

		effect[i]->AddTween(Ptr<MoveBy>::New(Vector3f(dist*cos(effectAngle), dist*sin(effectAngle), 0),
			effectLife, Tweener::EASE_OUT).Get());

		engine->AddParticle(effect[i]);
	}
}

bool Bullet::Hit(float playerX, float playerY, float playerRadius)
{
	return this->bulletType->Hit(playerX, playerY, playerRadius);
}

void Bullet::SetType(Ptr<BulletType> type)
{
	auto stgResources = STGResources::GetInstance();

	this->bulletType = type;
	type->SetBullet(this);
	SetTexture(type->GetTexture());
	SetTexRect(type->GetTexRect());
	SetBulletColor(type->GetBulletColor());
}