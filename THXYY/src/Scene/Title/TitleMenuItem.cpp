#include "TitleMenuItem.h"

Texture* TitleMenuItem::texTitleMenu = nullptr;

TitleMenuItem::TitleMenuItem(Type type)
{
	SetTexture(texTitleMenu);
	SetColorUnSelectable(Vector3f(0.35f, 0.35f, 0.35f));

	switch (type)
	{
	case GAME_START:
		SetTexRect(Rect(0, 128, 0, 32));
		break;
	case EXTRA_START:
		SetTexRect(Rect(0, 128, 32, 64));
		SetSelectable(false);
		break;
	case PRACTICE_START:
		SetTexRect(Rect(0, 128, 96, 128));
		break;
	case SPELL_PRACTICE:
		SetTexRect(Rect(0, 128, 128, 160));
		break;
	case REPLAY:
		SetTexRect(Rect(0, 128, 160, 192));
		break;
	case PLAYER_DATA:
		SetTexRect(Rect(0, 128, 192, 224));
		break;
	case MUSIC_ROOM:
		SetTexRect(Rect(0, 128, 224, 256));
		break;
	case OPTION:
		SetTexRect(Rect(0, 128, 256, 288));
		break;
	case MANUAL:
		SetTexRect(Rect(0, 128, 288, 320));
		break;
	case QUIT:
		SetTexRect(Rect(0, 128, 320, 352));
		break;
	}
}

TitleMenuItem::~TitleMenuItem()
{
}

void TitleMenuItem::OnSelect()
{
	MenuItem::OnSelect();
}

void TitleMenuItem::OnDeselect()
{
	MenuItem::OnDeselect();
}