#include "Player.h"
#include "STGEngine.h"
#include "Item\PowerItemSmall.h"

static const int DYING_TIME = 12;
static const int SHRINK_TIME = 3;

Player::Player()
{
	center = nullptr;
	isHiSpeed = true;
	state = NORMAL;
	frame_counter = 0;
	determineDeathTime = 9;
	radius = 3.0f;
	invincible = false;
}

Player::~Player()
{
}

void Player::ProcessInvincible()
{
	if (invincible)
	{
		frame_invincible--;
		if (frame_invincible < 0)
		{
			invincible = false;
			SetColor(Vector3f(1.0f, 1.0f, 1.0f));
		}
		else
		{
			//¼ÆËãÉÁË¸Ð§¹û
			invincible_shrink_counter++;
			if (invincible_shrink_counter == 2 * SHRINK_TIME)
			{
				invincible_shrink_counter = 0;
			}
			if (invincible_shrink_counter >= SHRINK_TIME && invincible_shrink_counter < 2 * SHRINK_TIME)
			{
				SetColor(Vector3f(0.4f, 0.4f, 0.4f));
			}
			else
			{
				SetColor(Vector3f(1.0f, 1.0f, 1.0f));
			}
		}
	}
}

void Player::ProcessCenterPoint()
{
	auto input = Input::GetInstance();
	GameScene* scene = (GameScene*)Game::GetInstance()->GetScene();

	if (input->KeyDown(DIK_LSHIFT) || input->KeyDown(DIK_RSHIFT))
	{
		if (isHiSpeed)
		{
			center = new PlayerCenter();
			float centerScale = GetRadius() / 3.0f;
			center->SetScale(centerScale, centerScale);
			scene->GetSTGLayer()->AddChild(center);
			OnEnterLowSpeed();
		}
		isHiSpeed = false;
	}
	else
	{
		if (!isHiSpeed)
		{
			center->Disappear();
			center = nullptr;
			OnEnterHighSpeed();
		}
		isHiSpeed = true;
	}
}

void Player::Update()
{
	auto input = Input::GetInstance();
	auto engine = STGEngine::GetInstance();
	auto scene = engine->GetGameScene();

	ProcessInvincible();
	ProcessCenterPoint();

	if (bombTimer > 0)
	{
		bombTimer--;
		if (bombTimer == 0)
		{
			enableBomb = true;
		}
	}

	if (enableMove)
	{
		Move();
	}
	if (enableFire && input->KeyDown(DIK_Z))
	{
		Fire();
	}

	if (state == NORMAL)
	{
		int bomb = engine->GetBomb();
		if (input->KeyDown(DIK_X))
		{
			if (bomb >= 1 && enableBomb)
			{
				engine->SetBomb(bomb - 1);
				engine->GetAllItems();
				Bomb();
			}
		}
	}
	else if (state == DETERMINE_DEATH)
	{
		SetSpeed(0);
		frame_counter++;
		if (frame_counter > determineDeathTime)
		{
			Biu();
		}
		else if (input->KeyDown(DIK_X))
		{
			int bomb = engine->GetBomb();
			if (bomb >= 1)
			{
				engine->SetBomb(bomb - 1);
				EnableMove(true);
				EnableFire(true);
				state = NORMAL;
				engine->GetAllItems();
				Bomb();
			}
		}
	}
	else if (state == DYING)
	{
		if (alpha <= 0)
		{
			state = REINTERING;
			motionState = STATIC;
			SetPosition(192.0f, -32.0f);
			SetSpeed(1.2f);
			SetAngle(90.0f);
			SetAlpha(1.0f);
			SetInvincible(250);
			SetupSubPlanes();

			auto life = engine->GetLife();
			if (life > 0)
			{
				engine->SetLife(life - 1);
				engine->SetBomb(3);
			}
			else
			{
				engine->GameOver();
			}
		}
		else
		{
			alpha -= 1.0f / DYING_TIME;
		}
	}
	else if (state == REINTERING)
	{
		if (position.y >= 48.0f)
		{
			position.y = 48.0f;
			state = NORMAL;
			EnableBomb(true);
			EnableMove(true);
			EnableFire(true);
		}
	}

	Sprite::Update();

	position.x = floor(position.x + 0.5f);
	position.y = floor(position.y + 0.5f);

	if (position.x < 8.0f)
	{
		position.x = 8.0f;
	}
	if (position.x > 376.0f)
	{
		position.x = 376.0f;
	}
	if (position.y < 16.0f)
	{
		if (state != REINTERING)
		{
			position.y = 16.0f;
		}
	}
	if (position.y > 432.0f)
	{
		position.y = 432.0f;
	}
}

void Player::Move()
{
	auto input = Input::GetInstance();
	auto engine = STGEngine::GetInstance();
	auto scene = engine->GetGameScene();

	if (isHiSpeed == false)
	{
		SetSpeed(GetLowSpeed());
	}
	else
	{
		SetSpeed(GetHiSpeed());
	}

	if (input->KeyDown(DIK_LEFT))
	{
		if (input->KeyDown(DIK_UP))
		{
			SetAngle(135.0f);
			motionState = LEFT_UP;
		}
		else if (input->KeyDown(DIK_DOWN))
		{
			SetAngle(-135.0f);
			motionState = LEFT_DOWN;
		}
		else
		{
			SetAngle(180.0f);
			motionState = LEFT;
		}
	}
	else if (input->KeyDown(DIK_RIGHT))
	{
		if (input->KeyDown(DIK_UP))
		{
			SetAngle(45.0f);
			motionState = RIGHT_UP;
		}
		else if (input->KeyDown(DIK_DOWN))
		{
			SetAngle(-45.0f);
			motionState = RIGHT_DOWN;
		}
		else
		{
			SetAngle(0.0f);
			motionState = RIGHT;
		}
	}
	else if (input->KeyDown(DIK_UP))
	{
		SetAngle(90.0f);
		motionState = UP;
	}
	else if (input->KeyDown(DIK_DOWN))
	{
		SetAngle(-90.0f);
		motionState = DOWN;
	}
	else
	{
		SetSpeed(0.0f);
		motionState = STATIC;
	}
}

void Player::Hitten()
{
	state = DETERMINE_DEATH;
	frame_counter = 0;
	EnableFire(false);
	EnableMove(false);

	STGResources::GetInstance()->soundBiu->Play();
}

void Player::Biu()
{
	state = DYING;

	EnableMove(false);
	EnableFire(false);
	EnableBomb(false);

	auto engine = STGEngine::GetInstance();
	auto stgResources = STGResources::GetInstance();

	RemoveAllSubPlanes();
	engine->RemoveAllBullet();

	for (int i = 0; i < 30; i++)
	{
		Sprite* light = new Sprite();
		light->SetTexture(stgResources->texPointLight);
		light->SetTexRect(Rect(96, 128, 0, 32));
		light->SetPosition(position);

		float scale = engine->Random(25, 75) / 100.0f;
		light->SetScale(scale, scale);
		light->AddTween(new ScaleTo(Vector3f(0, 0, 1), 40, Tweener::SIMPLE));

		float lightAngle = Math::ToRad(engine->Random(0, 359));
		float distance = engine->Random(0, 120);
		light->AddTween(new MoveTo(Vector3f(position.x + cos(lightAngle)*distance,
			position.y + sin(lightAngle)*distance, position.z), 40, Tweener::EASE_OUT));
		light->AddTween(new FadeOut(40, Tweener::EASE_OUT));

		engine->AddEffect(light);
	}

	Sprite* dieEffect = new Sprite();
	dieEffect->SetPosition(position);
	dieEffect->SetTexture(stgResources->texEffBase);
	dieEffect->SetTexRect(Rect(128, 192, 16, 80));
	dieEffect->AddTween(new ScaleTo(Vector3f(2.0f, 2.0f, 1.0f), 10, Tweener::SIMPLE));
	dieEffect->AddTween(new FadeOut(10, Tweener::SIMPLE));
	engine->AddEffect(dieEffect);

	for (int i = 0; i < 9; i++)
	{
		float itemAngle = Math::ToRad(30 + 15 * i);
		float distance = 80;

		PowerItemSmall* item = new PowerItemSmall();
		item->SetPosition(position.x, position.y);
		item->AddTween(new MoveBy(Vector3f(distance*cos(itemAngle),
			distance*sin(itemAngle), 0), 40, Tweener::EASE_OUT));
		item->AddTween(new Rotate2D(720.0f, 40, Tweener::EASE_OUT));
		engine->AddItem(item);
	}

	if (engine->GetPower() < 50)
	{
		engine->SetPower(0);
	}
	else
	{
		engine->SetPower(engine->GetPower() - 50);
	}
}

bool Player::IsDamageable()
{
	return state == NORMAL && invincible == false;
}

void Player::OnDestroy()
{
}

void Player::Fire()
{
	auto iter = this->subPlaneList.GetIterator();
	while (iter->HasNext())
	{
		auto subPlane = iter->Next();
		subPlane->Fire();
	}
}

void Player::EnterBombState(int bombTime)
{
	EnableBomb(false);
	bombTimer = bombTime;
}

int Player::GetPowerLevel()
{
	auto engine = STGEngine::GetInstance();
	return engine->GetPower() / 100;
}

void Player::OnStart()
{
	Sprite::OnStart();

	SetupSubPlanes();
}

void Player::OnPowerLevelChanged(int oldPowerLevel, int newPowerLevel)
{
}

void Player::OnEnterLowSpeed()
{
}

void Player::OnEnterHighSpeed()
{
}

void Player::AddSubPlane(SubPlane* subPlane)
{
	this->subPlaneList.Add(subPlane);
	AddChild(subPlane);
}

void Player::RemoveSubPlane(int index)
{
	SubPlane* subPlane = this->subPlaneList.Get(index);
	this->subPlaneList.RemoveAt(index);
	subPlane->Disappear();
}

void Player::RemoveAllSubPlanes()
{
	auto iter = this->subPlaneList.GetIterator();
	while (iter->HasNext())
	{
		auto subPlane = iter->Next();
		subPlane->Disappear();
	}
	this->subPlaneList.Clear();
}