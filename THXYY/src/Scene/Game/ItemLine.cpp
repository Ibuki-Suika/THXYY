#include "ItemLine.h"

void ItemLine::Update()
{
	Sprite::Update();

	frame++;

	if (frame < 120 && frame % 8 == 0)
	{
		this->bright = !bright;
		if (this->bright)
		{
			SetColor(Vector3f(1.0f, 0.14f, 0.0f));
		}
		else
		{
			SetColor(Vector3f(1.0f, 1.0f, 1.0f));
		}
	}

	if (frame == 120)
	{
		AddTween(new FadeOut(30, Tweener::SIMPLE));
	}
}