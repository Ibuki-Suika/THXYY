#include "PauseMenuItem.h"
#include "../../STGCore/STGCore.h"

Ptr<Texture> PauseMenuItem::texPauseMenu;

PauseMenuItem::PauseMenuItem(Type type)
{
	this->type = type;

	auto stgResources = STGResources::GetInstance();

	SetTexture(texPauseMenu);
	SetPivot(Vector2f(0.0f, 0.0f));

	switch (type)
	{
	case PAUSE:
		SetTexRect(Rect(0, 128, 0, 64));
		SetColor(Vector3f(1.0f, 1.0f, 1.0f));
		break;
	case GAME_OVER:
		SetTexRect(Rect(128, 256, 0, 64));
		SetColor(Vector3f(1.0f, 1.0f, 1.0f));
		break;
	case REPLAY_OVER:
		SetTexRect(Rect(256, 384, 0, 64));
		SetColor(Vector3f(1.0f, 1.0f, 1.0f));
		break;
	case REALLY:
		SetTexRect(Rect(256, 448, 192, 256));
		SetColor(Vector3f(1.0f, 1.0f, 1.0f));
		break;
	case RESUME:
		SetTexRect(Rect(0, 128, 64, 128));
		break;
	case CONTINUE:
		SetTexRect(Rect(128, 256, 64, 128));
		SetSelectable(false);
		break;
	case RETURN_TO_TITLE:
		SetTexRect(Rect(256, 384, 64, 128));
		break;
	case RETRY:
		SetTexRect(Rect(0, 192, 128, 192));
		break;
	case SAVE_REPLAY:
		SetTexRect(Rect(192, 448, 128, 192));
		SetSelectable(false);
		break;
	case NO:
		SetTexRect(Rect(0, 128, 192, 256));
		break;
	case YES:
		SetTexRect(Rect(128, 256, 192, 256));
		break;
	}
}

PauseMenuItem::~PauseMenuItem()
{

}

void PauseMenuItem::Update()
{
	MenuItem::Update();
}