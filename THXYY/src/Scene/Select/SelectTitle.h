#ifndef SELECT_TITLE_H
#define SELECT_TITLE_H

#include <THEngine.h>

using namespace THEngine;

class SelectTitle : public Sprite
{
public:
	static Ptr<Texture> tex;

	enum Type
	{
		RANK_SELECT,
		PLAYER_SELECT,
		REPLAY,
		PLAYER_DATA,
		MUSIC_ROOM,
		SPELL_SELECT,
		SAVE_REPLAY,
		MANUAL,
		OPTION,
		STAGE_SELECT
	};

private:
	Type type = RANK_SELECT;

public:
	SelectTitle();
	virtual ~SelectTitle() = default;

	void SetType(Type type);
};

#endif
