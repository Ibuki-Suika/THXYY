#include "Global.h"

Global::~Global()
{
}

bool Global::Load()
{
	auto manager = AssetManager::GetInstance();
	texBlack = manager->CreateTextureFromFile("res/front/black.jpg");
	if (texBlack == nullptr)
	{
		return false;
	}

	this->titleMusic = Audio::GetInstance()->CreateMusic("bgm/title.wav");

	return true;
}