#ifndef STAGE_H
#define STAGE_H

#include <THEngine.h>

using namespace THEngine;

class Stage : public Object
{
public:
	Stage();
	virtual ~Stage();

	virtual void Update();

	virtual void UpdateBackground();

	virtual void OnStart();

	virtual void OnLoad();
};

#endif