#ifndef THXYY_H
#define THXYY_H

#include "THEngine/THEngine.h"
#include "STGCore\STGCore.h"

using namespace THEngine;

class THXYY : public Game
{
private:
	STGEngine* engine;
	Music* titleMusic = nullptr;

public:
	THXYY();
	virtual ~THXYY();

	bool CreateGame(int width, int height, bool fullScreen);

	virtual void OnShutdown() override;
};

#endif