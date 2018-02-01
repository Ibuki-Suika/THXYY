#ifndef THXYY_H
#define THXYY_H

#include <THEngine.h>

using namespace THEngine;

class STGEngine;
class GameConfig;

class THXYY : public Game
{
private:
	Ptr<STGEngine> engine;
	Ptr<Music> titleMusic;

public:
	THXYY();
	virtual ~THXYY();

	bool CreateGame(const GameConfig& config);

	virtual void OnShutdown() override;
};

#endif