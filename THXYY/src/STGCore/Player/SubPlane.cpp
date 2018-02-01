#include "SubPlane.h"

SubPlane::SubPlane()
{

}

SubPlane::~SubPlane()
{

}

void SubPlane::Update()
{
	Sprite::Update();
}

void SubPlane::Disappear()
{
	ClearTweens();

	Ptr<ScaleTo> scaleTo = Ptr<ScaleTo>::New(Vector3f(0, 0, 1), 16, Tweener::SIMPLE);
	scaleTo->onFinished = [this](){
		this->MarkDestroy();
	};
	AddTween(scaleTo.Get());
}