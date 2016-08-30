#include "THMenuItem.h"

namespace THEngine
{
	MenuItem::MenuItem()
	{
		SetColor(colorUnselected);
	}

	MenuItem::~MenuItem()
	{

	}

	void MenuItem::Update()
	{
		Sprite::Update();

		if (isTwinkling)
		{
			twinkleCounter++;
			if (twinkleCounter >= twinkleTime)
			{
				twinkleCounter = 0;
				isTwinkling = false;

				if (shineEnabled)
				{
					TweenSequence* sequence = new TweenSequence();
					sequence->AddTween(new ColorTo(shineColor, shineTime, Tweener::EASE_OUT));
					sequence->AddTween(new ColorTo(Vector3f(1.0f, 1.0f, 1.0f), shineTime, Tweener::EASE_OUT));
					sequence->SetLooped(true);

					tweenShine = sequence;
					AddTween(tweenShine);
				}

				return;
			}
			if (twinkleCounter % (2 * twinkleInterval) == 0)
			{
				SetColor(Vector3f(1.0f,1.0f,1.0f));
			}
			else if (twinkleCounter % (2 * twinkleInterval) == twinkleInterval)
			{
				SetColor(Vector3f(0.25f, 0.25f, 0.25f));
			}
		}
	}

	void MenuItem::OnSelect()
	{
		selected = true;

		if (shineEnabled)
		{
			TweenSequence* sequence = new TweenSequence();
			sequence->AddTween(new ColorTo(Vector3f(1.0f, 1.0f, 1.0f), shineTime, Tweener::EASE_OUT));
			sequence->AddTween(new ColorTo(shineColor, shineTime, Tweener::EASE_OUT));
			sequence->SetLooped(true);

			tweenShine = sequence;
			AddTween(tweenShine);
		}

		if (vibrateEnabled)
		{
			float x1 = Random(0, xVibrateRange);
			float x2 = Random(0, xVibrateRange);
			float y1 = Random(0, yVibrateRange);
			float y2 = Random(0, yVibrateRange);

			TweenSequence* sequence = new TweenSequence();
			sequence->AddTween(new MoveBy(Vector3f(-x1, -y1, 0.0f), vibrateTime, Tweener::SIMPLE));
			sequence->AddTween(new MoveBy(Vector3f(x1 + x2, y1 + y2, 0.0f), vibrateTime, Tweener::SIMPLE));
			sequence->AddTween(new MoveBy(Vector3f(-x2, -y2, 0.0f), vibrateTime, Tweener::SIMPLE));

			tweenVibrate = sequence;
			AddTween(tweenVibrate);
		}
	}

	void MenuItem::OnClick()
	{
		if (twinkleEnabled)
		{
			isTwinkling = true;
		}

		if (tweenShine)
		{
			KillTween(tweenShine);
			tweenShine = nullptr;
		}
	}

	void MenuItem::OnDeselect()
	{
		if (tweenShine)
		{
			KillTween(tweenShine);
			tweenShine = nullptr;
		}

		SetColor(colorUnselected);
	}
}