#pragma once

#include <THEngine.h>

using namespace THEngine;

class SakuraParticle : public Particle3D
{
public:
	SakuraParticle();
	SakuraParticle(int type);
	virtual ~SakuraParticle();

	virtual void Update() override;

	void InitWithType(int type);
};