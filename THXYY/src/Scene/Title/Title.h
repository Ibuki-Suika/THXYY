#ifndef TITLE_H
#define TITLE_H

#include <THEngine.h>
#include "ParticleLayer.h"

using namespace THEngine;

class Title : public Scene
{
private:
	Ptr<Layer> bgrLayer;
	Ptr<Texture> titleTex;
	Ptr<Texture> texLogo;

	Ptr<Layer> blackLayer;
	Ptr<Sprite> black;

	Ptr<ParticleLayer> particleLayer;

	bool needFadeIn = true;

private:
	void CreateLogo();

public:
	Title();
	virtual ~Title();

	virtual void OnStart() override;
	virtual void OnLoad(Ptr<AsyncInfo> info) override;

	inline void SetNeedFadeIn(bool needFadeIn) { this->needFadeIn = needFadeIn; }
};

#endif