#ifndef GLOBAL_H
#define GLOBAL_H

#include <THEngine.h>

using namespace THEngine;

class Global : public Object, public Singleton<Global>
{
	friend class Singleton<Global>;
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
public:
	StageEnum stageEnum;
	PlayerEnum playerEnum;
	Ptr<Music> titleMusic;
	Ptr<Texture> texBlack;

private:
	Global() = default;

public:
	virtual ~Global();

	bool Load();
};

#endif