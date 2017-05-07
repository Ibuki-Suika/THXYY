#include "StarParticle.h"

Texture* StarParticle::tex = nullptr;

StarParticle::StarParticle()
{
	SetTexture(tex);
	SetTexRect(Rect(0, 32, 96, 128));

	SetLife(300);
	float x = Math::Random(-100, 740);
	float y = Math::Random(360, 500);
	float z = 50;

	SetPosition(Vector3f(x, y, z));
	float rad = Math::ToRad(Math::Random(0, 90) + 225);
	SetDirection(Vector3f(cos(rad), sin(rad), 0));

	SetRotatingAxis(Vector3f(0, 0, 1));
	SetRotatingSpeed(Math::Random(100, 500) / 100.0f);
	SetSpeed(0.3f + Math::Random(0, 120) / 100.0f);
	SetAlpha(0);
	float scale = Math::Random(50, 100) / 100.0f;
	SetScale(Vector3f(scale, scale, 1));

	TweenSequence* sequence = new TweenSequence();
	sequence->AddTween(new FadeTo(0.35f, 100, Tweener::EASE_OUT));
	sequence->AddTween(new Delay(100));
	sequence->AddTween(new FadeOut(100, Tweener::EASE_OUT));
	AddTween(sequence);
}