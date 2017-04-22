#include "SelectTitle.h"

Texture* SelectTitle::tex = nullptr;

SelectTitle::SelectTitle()
{
	SetTexture(this->tex);
}

void SelectTitle::SetType(SelectTitle::Type type)
{
	this->type = type;
	switch (type)
	{
	case RANK_SELECT:
		SetTexRect(Rect(0, 256, 0, 96));
		break;
	case PLAYER_SELECT:
		SetTexRect(Rect(0, 256, 96, 192));
		break;
	case REPLAY:
		SetTexRect(Rect(0, 256, 192, 288));
		break;
	case PLAYER_DATA:
		SetTexRect(Rect(0, 256, 288, 384));
		break;
	case MUSIC_ROOM:
		SetTexRect(Rect(0, 256, 384, 480));
		break;
	case SPELL_SELECT:
		SetTexRect(Rect(256, 512, 0, 96));
		break;
	case SAVE_REPLAY:
		SetTexRect(Rect(256, 512, 96, 192));
		break;
	case MANUAL:
		SetTexRect(Rect(256, 512, 192, 288));
		break;
	case OPTION:
		SetTexRect(Rect(256, 512, 288, 384));
		break;
	case STAGE_SELECT:
		SetTexRect(Rect(256, 512, 384, 480));
		break;
	}
}