#pragma once

#include <THEngine.h>

using namespace THEngine;

class PauseMenuItem : public MenuItem
{
public:
	enum Type
	{
		PAUSE,
		RESUME,
		RETURN_TO_TITLE,
		SAVE_REPLAY,
		CONTINUE,
		YES,
		NO,
		GAME_OVER,
		REPLAY_OVER,
		REALLY,
		RETRY
	};

public:
	static Ptr<Texture> texPauseMenu;

private:
	Type type;
	
public:
	PauseMenuItem(Type type);
	virtual ~PauseMenuItem();

	virtual void Update() override;
};