#include "RankSelectMenuItem.h"

static const int FADE_TIME = 24;
static const int OFFSET = 60;

Texture* RankSelectMenuItem::texRank = nullptr;

RankSelectMenuItem::RankSelectMenuItem()
{
	SetTexture(texRank);
	SetAlpha(0.0f);
	AddTween(new FadeTo(1.0f, FADE_TIME, Tweener::SIMPLE));
}

void RankSelectMenuItem::SetType(Type type)
{
	this->type = type;
	switch (type)
	{
	case EASY:
		SetTexRect(Rect(0, 256, 0, 128));
		SetPosition(Vector3f(210 - OFFSET, 352, 0));
		AddTween(new MoveTo(Vector3f(210, 352, 0), FADE_TIME, Tweener::SIMPLE));
		break;
	case NORMAL:
		SetTexRect(Rect(0, 320, 128, 256));
		SetPosition(Vector3f(420 + OFFSET, 256, 0));
		AddTween(new MoveTo(Vector3f(420, 256, 0), FADE_TIME, Tweener::SIMPLE));
		break;
	case HARD:
		SetTexRect(Rect(0, 352, 256, 384));
		SetPosition(Vector3f(258 - OFFSET, 180, 0));
		AddTween(new MoveTo(Vector3f(258, 180, 0), FADE_TIME, Tweener::SIMPLE));
		break;
	case LUNATIC:
		SetTexRect(Rect(0, 256, 384, 512));
		SetPosition(Vector3f(388 + LUNATIC, 84, 0));
		AddTween(new MoveTo(Vector3f(388, 84, 0), FADE_TIME, Tweener::SIMPLE));
		break;
	}
}

void RankSelectMenuItem::Enter()
{

}

void RankSelectMenuItem::Exit()
{
	AddTween(new FadeOut(FADE_TIME, Tweener::SIMPLE));
	switch (type)
	{
	case EASY:
		AddTween(new MoveTo(Vector3f(210 - OFFSET, 352, 0), FADE_TIME, Tweener::SIMPLE));
		break;
	case NORMAL:
		AddTween(new MoveTo(Vector3f(420 + OFFSET, 256, 0), FADE_TIME, Tweener::SIMPLE));
		break;
	case HARD:
		AddTween(new MoveTo(Vector3f(258 - OFFSET, 180, 0), FADE_TIME, Tweener::SIMPLE));
		break;
	case LUNATIC:
		AddTween(new MoveTo(Vector3f(388 + OFFSET, 84, 0), FADE_TIME, Tweener::SIMPLE));
		break;
	}
}

