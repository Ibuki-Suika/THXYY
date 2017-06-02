#ifndef STAGE01_H
#define STAGE01_H

#include "../../STGCore/STGCore.h"

class Stage01 : public Stage
{
private:
	static Texture* texRoad;
	Texture* texLogo = nullptr;
	CubeMap* sky = nullptr;

	int frame = 0;

	Mesh* house = nullptr;

public:
	static const int BPM;
	static const float SPB;
	static const float FPB;

private:
	void ShowLogo(int startFrame);
	void AddEnemy001(int startFrame);
	void AddEnemy002(int startFrame);
	void AddEnemy003(int startFrame);

public:
	Stage01();
	virtual ~Stage01();

	virtual void Update() override;
	virtual void UpdateBackground() override;
	virtual void OnStart() override;
	virtual void OnLoad() override;

	void InitBackground();
	void SetupCamera();
	void SetupFog();
	void InitBackgroundObjects();

	void CreateHouses();
};

#endif