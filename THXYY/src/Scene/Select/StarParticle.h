#ifndef STAR_PARTICLE_H
#define STAR_PARTICLE_H

#include <THEngine.h>

using namespace THEngine;

class StarParticle : public Particle3D
{
public:
	StarParticle();
	virtual ~StarParticle() = default;

	static Texture* tex;
};

#endif