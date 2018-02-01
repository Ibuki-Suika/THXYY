#include "RankSelectMenuItem.h"

static const int FADE_TIME = 24;
static const int OFFSET = 60;

Ptr<Texture> RankSelectMenuItem::texRank;

RankSelectMenuItem::RankSelectMenuItem()
{
	SetTexture(texRank);
	SetAlpha(0.0f);
	AddTween(Ptr<FadeTo>::New(1.0f, FADE_TIME, Tweener::SIMPLE).Get());
}

void RankSelectMenuItem::SetType(Type type)
{
	this->type = type;
	switch (type)
	{
	case EASY:
		SetTexRect(Rect(0, 256, 0, 128));
		SetPosition(Vector3f(210 - OFFSET, 352, 0));
		AddTween(Ptr<MoveTo>::New(Vector3f(210, 352, 0), FADE_TIME, Tweener::SIMPLE).Get());
		break;
	case NORMAL:
		SetTexRect(Rect(0, 320, 128, 256));
		SetPosition(Vector3f(420 + OFFSET, 256, 0));
		AddTween(Ptr<MoveTo>::New(Vector3f(420, 256, 0), FADE_TIME, Tweener::SIMPLE).Get());
		break;
	case HARD:
		SetTexRect(Rect(0, 352, 256, 384));
		SetPosition(Vector3f(258 - OFFSET, 180, 0));
		AddTween(Ptr<MoveTo>::New(Vector3f(258, 180, 0), FADE_TIME, Tweener::SIMPLE).Get());
		break;
	case LUNATIC:
		SetTexRect(Rect(0, 256, 384, 512));
		SetPosition(Vector3f(388 + LUNATIC, 84, 0));
		AddTween(Ptr<MoveTo>::New(Vector3f(388, 84, 0), FADE_TIME, Tweener::SIMPLE).Get());
		break;
	}
}

void RankSelectMenuItem::Enter()
{

}

void RankSelectMenuItem::Exit()
{
	AddTween(Ptr<FadeOut>::New(FADE_TIME, Tweener::SIMPLE).Get());
	switch (type)
	{
	case EASY:
		AddTween(Ptr<MoveTo>::New(Vector3f(210 - OFFSET, 352, 0), FADE_TIME, Tweener::SIMPLE).Get());
		break;
	case NORMAL:
		AddTween(Ptr<MoveTo>::New(Vector3f(420 + OFFSET, 256, 0), FADE_TIME, Tweener::SIMPLE).Get());
		break;
	case HARD:
		AddTween(Ptr<MoveTo>::New(Vector3f(258 - OFFSET, 180, 0), FADE_TIME, Tweener::SIMPLE).Get());
		break;
	case LUNATIC:
		AddTween(Ptr<MoveTo>::New(Vector3f(388 + OFFSET, 84, 0), FADE_TIME, Tweener::SIMPLE).Get());
		break;
	}
}

