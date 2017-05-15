#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Update()
{
	UpdateBackground();
}

void Stage::UpdateBackground()
{
}

void Stage::OnStart()
{
	if (this->bgm)
		this->bgm->Play();
}

void Stage::OnLoad()
{
}