#include "ReimuSubPlane.h"
#include "ReimuSubPlaneBullet.h"

const float ReimuSubPlane::ROTATION_SPEED = 6.0f;

ReimuSubPlane::ReimuSubPlane()
{
	auto stgResources = STGResources::GetInstance();

	SetTexture(stgResources->texReimu);
	SetTexRect(Rect(80, 96, 144, 160));
}

ReimuSubPlane::~ReimuSubPlane()
{

}

void ReimuSubPlane::Update()
{
	Sprite::Update();

	this->rotation += ROTATION_SPEED;
}

void ReimuSubPlane::Fire()
{
	if (this->frame_shoot == 0)
	{
		auto engine = STGEngine::GetInstance();
		auto player = engine->GetPlayer();

		Ptr<ReimuSubPlaneBullet> bullet = Ptr<ReimuSubPlaneBullet>::New();
		bullet->SetPosition(player->GetPosition().x + this->GetPosition().x, player->GetPosition().y + this->GetPosition().y);
		engine->ShootPlayerBullet(bullet.Get());
	}
	this->frame_shoot++;
	if (this->frame_shoot == 4)
	{
		this->frame_shoot = 0;
	}
}
