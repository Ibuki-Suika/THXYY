#include "Enemy.h"
#include "../STGEngine.h"
#include "../Item/PowerItemSmall.h"
#include "../Item/ScoreItem.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	prevX = position.x;

	Sprite::Update();

	UpdateMotionState();

	auto engine = STGEngine::GetInstance();

	auto list = engine->GetPlayerBulletList();

	auto iter = list->GetIterator();
	while (iter->HasNext())
	{
		auto playerBullet = iter->Next();
		auto playerBulletPos = playerBullet->GetPosition();
		auto difX = position.x - playerBulletPos.x;
		auto difY = position.y - playerBulletPos.y;
		auto dist = hitRange + playerBullet->GetHitRange();

		if (difX * difX + difY * difY < dist * dist)
		{
			OnHitten(playerBullet->GetDamage());
			playerBullet->MarkDestroy();
			iter->Remove();
		}
	}
}

void Enemy::UpdateMotionState()
{
	frameForAnim++;

	if (fabs(position.x - prevX) < 1e-2)
	{
		switch (prevMotionState)
		{
		case LEFT:
			motionState = LEFT_TO_STATIC;
			frameForAnim = 0;
			break;
		case RIGHT:
			motionState = RIGHT_TO_STATIC;
			frameForAnim = 0;
			break;
		case STATIC_TO_LEFT:
			motionState = LEFT_TO_STATIC;
			frameForAnim = 4 * ANIM_INTERVAL - frameForAnim;
		case STATIC_TO_RIGHT:
			motionState = RIGHT_TO_STATIC;
			frameForAnim = 4 * ANIM_INTERVAL - frameForAnim;
		case LEFT_TO_STATIC:
		case RIGHT_TO_STATIC:
			if (frameForAnim >= 4 * ANIM_INTERVAL)
			{
				motionState = STATIC;
				frameForAnim = 0;
			}
			break;
		default:
			break;
		}
	}
	else if (position.x - prevX > 0)
	{
		switch (prevMotionState)
		{
		case STATIC:
		case LEFT_TO_STATIC:
			motionState = STATIC_TO_RIGHT;
			frameForAnim = 0;
			break;
		case LEFT:
			motionState = RIGHT;
			break;
		case STATIC_TO_LEFT:
			motionState = STATIC_TO_RIGHT;
			break;
		case RIGHT_TO_STATIC:
			motionState = STATIC_TO_RIGHT;
			frameForAnim = 4 * ANIM_INTERVAL - frameForAnim;
		case STATIC_TO_RIGHT:
			if (frameForAnim >= 4 * ANIM_INTERVAL)
			{
				motionState = RIGHT;
				frameForAnim = 0;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch (prevMotionState)
		{
		case STATIC:
		case RIGHT_TO_STATIC:
			motionState = STATIC_TO_LEFT;
			frameForAnim = 0;
			break;
		case RIGHT:
			motionState = LEFT;
			break;
		case STATIC_TO_RIGHT:
			motionState = STATIC_TO_LEFT;
			break;
		case LEFT_TO_STATIC:
			motionState = STATIC_TO_LEFT;
			frameForAnim = 4 * ANIM_INTERVAL - frameForAnim;
		case STATIC_TO_LEFT:
			if (frameForAnim >= 4 * ANIM_INTERVAL)
			{
				motionState = LEFT;
				frameForAnim = 0;
			}
			break;
		default:
			break;
		}
	}

	if (frameForAnim >= 4 * ANIM_INTERVAL)
	{
		frameForAnim = 0;
	}

	prevMotionState = motionState;
}

void Enemy::OnDie()
{
	auto engine = STGEngine::GetInstance();
	auto stgResources = STGResources::GetInstance();

	engine->SetScore(engine->GetScore() + score);

	DropItems();

	stgResources->soundEnemyDie00->Play();

	Ptr<Particle3D> effect[10];
	for (int i = 0; i < 10; i++)
	{
		int effectLife = 40;

		effect[i] = Ptr<Particle3D>::New();
		effect[i]->SetTexture(stgResources->texFourAngleStar);
		effect[i]->SetPosition(position);
		effect[i]->SetLife(effectLife);
		effect[i]->SetTexRect(Rect(96, 128, 32, 64));

		float effectAngle = Math::ToRad(engine->Random(0, 359));
		float dist = engine->Random(0, 60);

		float effectScale = engine->Random(4, 14) / 10.0f;
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

	Ptr<Sprite> dieEffect = Ptr<Sprite>::New();
	dieEffect->SetPosition(position);
	dieEffect->SetTexture(stgResources->texEffBase);	
	dieEffect->AddTween(Ptr<ScaleTo>::New(Vector3f(2.0f, 2.0f, 1.0f), 10, Tweener::SIMPLE).Get());
	dieEffect->AddTween(Ptr<FadeOut>::New(10, Tweener::SIMPLE).Get());
	engine->AddEffect(dieEffect);
	switch (enemyColor)
	{
	case BLUE:
	{
		dieEffect->SetTexRect(Rect(192, 256, 16, 80));
		for (int i = 0; i < 10; i++)
		{
			effect[i]->SetTexRect(Rect(64, 96, 0, 32));
		}
		break;
	}
	case RED:
	{
		dieEffect->SetTexRect(Rect(128, 192, 16, 80));
		for (int i = 0; i < 10; i++)
		{
			effect[i]->SetTexRect(Rect(0, 32, 0, 32));
		}
		break;
	}
	case GREEN:
	{
		dieEffect->SetTexRect(Rect(64, 128, 80, 144));
		for (int i = 0; i < 10; i++)
		{
			effect[i]->SetTexRect(Rect(0, 32, 32, 64));
		}
		break;
	}
	case YELLOW:
	{
		dieEffect->SetTexRect(Rect(0, 64, 80, 144));
		for (int i = 0; i < 10; i++)
		{
			effect[i]->SetTexRect(Rect(32, 64, 32, 64));
		}
		break;
	}
	}
}

void Enemy::OnDestroy()
{
}

void Enemy::OnHitten(float damage)
{
	if (life <= 0)
	{
		return;
	}

	life -= damage;

	if (life <= 0)
	{
		OnDie();
		MarkDestroy();
	}

	STGResources::GetInstance()->soundDamage01->Play();
}

void Enemy::DropItems()
{
	auto engine = STGEngine::GetInstance();

	for (int i = 0; i < powerItemSmallNum; i++)
	{
		float maxOffset = 5 * powerItemSmallNum;
		if (maxOffset > 40)
		{
			maxOffset = 40;
		}
		float posX = engine->Random(-maxOffset, maxOffset);
		float posY = engine->Random(-maxOffset, maxOffset);

		Ptr<PowerItemSmall> item = Ptr<PowerItemSmall>::New();
		item->SetPosition(position.x + posX, position.y + posY);
		item->AddTween(Ptr<MoveBy>::New(Vector3f(0, 20, 0), 40, Tweener::EASE_OUT).Get());
		item->AddTween(Ptr<Rotate2D>::New(720.0f, 40, Tweener::EASE_OUT).Get());
		engine->AddItem(item.Get());
	}

	for (int i = 0; i < scoreItemNum; i++)
	{
		float maxOffset = 5 * scoreItemNum;
		if (maxOffset > 40)
		{
			maxOffset = 40;
		}
		float posX = engine->Random(-maxOffset, maxOffset);
		float posY = engine->Random(-maxOffset, maxOffset);

		Ptr<ScoreItem> item = Ptr<ScoreItem>::New();
		item->SetPosition(position.x + posX, position.y + posY);
		item->AddTween(Ptr<MoveBy>::New(Vector3f(0, 20, 0), 40, Tweener::EASE_OUT).Get());
		item->AddTween(Ptr<Rotate2D>::New(720.0f, 40, Tweener::EASE_OUT).Get());
		engine->AddItem(item.Get());
	}
}

void Enemy::SetItem(ItemType type, int count)
{
	switch (type)
	{
	case POWER_SMALL:
		powerItemSmallNum = count;
		break;
	case SCORE:
		scoreItemNum = count;
		break;
	}
}