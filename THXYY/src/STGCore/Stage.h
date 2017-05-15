#ifndef STAGE_H
#define STAGE_H

#include <THEngine.h>

using namespace THEngine;

class Stage : public Object
{
private:
	Music* bgm = nullptr;

public:
	Stage();
	virtual ~Stage();

	virtual void Update();

	virtual void UpdateBackground();

	virtual void OnStart();

	virtual void OnLoad();

	inline Music* GetBGM() const { return this->bgm; }
	inline void SetBGM(Music* bgm) { this->bgm = bgm; }
};

#endif