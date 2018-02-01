#ifndef STAGE_H
#define STAGE_H

#include <THEngine.h>

using namespace THEngine;

class Stage : public Object
{
private:
	Ptr<Music> bgm;

public:
	Stage();
	virtual ~Stage();

	virtual void Update();

	virtual void UpdateBackground();

	virtual void OnStart();

	virtual void OnLoad();

	inline Ptr<Music> GetBGM() const { return this->bgm; }
	inline void SetBGM(Ptr<Music> bgm) { this->bgm = bgm; }
};

#endif