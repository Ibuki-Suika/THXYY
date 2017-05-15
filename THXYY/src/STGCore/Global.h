#ifndef GLOBAL_H
#define GLOBAL_H

#include <THEngine.h>

using namespace THEngine;

class Global : public Object
{
public:
	enum StageEnum
	{
		STAGE_01,
		STAGE_02,
		STAGE_03,
		STAGE_04,
		STAGE_05,
		STAGE_06,
		STAGE_EX
	};

	enum PlayerEnum
	{
		REIMU,
		MARISA,
		AYA,
		REISEN
	};

private:
	static Global* instance;

public:
	StageEnum stageEnum;
	PlayerEnum playerEnum;
	Music* titleMusic = nullptr;
	Texture* texBlack = nullptr;

public:
	Global();
	virtual ~Global();

	static Global* GetInstance();

	bool Load();
};

#endif