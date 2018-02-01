#pragma once

#include <THEngine.h>

using namespace THEngine;

class TitleMenuItem : public MenuItem
{
public:
	enum Type
	{
		GAME_START,
		EXTRA_START,
		PRACTICE_START,
		SPELL_PRACTICE,
		REPLAY,
		PLAYER_DATA,
		MUSIC_ROOM,
		OPTION,
		MANUAL,
		QUIT
	};

public:
	static Ptr<Texture> texTitleMenu;

private:
	Type type;

public:
	TitleMenuItem(Type type);
	virtual ~TitleMenuItem();

	virtual void OnSelect() override;
	virtual void OnDeselect() override;
};