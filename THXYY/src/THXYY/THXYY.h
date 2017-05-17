#ifndef THXYY_H
#define THXYY_H

#include <THEngine.h>

using namespace THEngine;

class STGEngine;
class GameConfig;

class THXYY : public Game
{
private:
	STGEngine* engine;
	Music* titleMusic = nullptr;

public:
	THXYY();
	virtual ~THXYY();

	bool CreateGame(const GameConfig& config);

	virtual void OnShutdown() override;
};

#endif