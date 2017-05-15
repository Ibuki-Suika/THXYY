#include "Global.h"

Global* Global::instance = nullptr;

Global::Global()
{
}

Global::~Global()
{
	TH_SAFE_RELEASE(texBlack);
}

Global* Global::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Global();
	}
	return instance;
}

bool Global::Load()
{
	auto manager = AssetManager::GetInstance();
	texBlack = manager->CreateTextureFromFile("res/front/black.jpg");
	if (texBlack == nullptr)
	{
		return false;
	}
	texBlack->Retain();

	this->titleMusic = Audio::GetInstance()->CreateMusic("bgm/title.wav");

	return true;
}