#ifndef TITLE_H
#define TITLE_H

#include <THEngine.h>
#include "ParticleLayer.h"

using namespace THEngine;

class Title : public Scene
{
private:
	Layer* bgrLayer;
	Texture* titleTex;

	Layer* blackLayer = nullptr;
	Sprite* black = nullptr;

	ParticleLayer* particleLayer = nullptr;

	bool needFadeIn = true;

public:
	Title();
	virtual ~Title();

	virtual void OnStart() override;
	virtual void OnLoad(AsyncInfo* info) override;

	inline void SetNeedFadeIn(bool needFadeIn) { this->needFadeIn = needFadeIn; }
};

#endif