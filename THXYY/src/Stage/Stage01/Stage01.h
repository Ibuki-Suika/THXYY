#ifndef STAGE01_H
#define STAGE01_H

#include "../../STGCore/STGCore.h"

class Stage01 : public Stage
{
private:
	static Texture* texRoad;

	CubeMap* sky = nullptr;

	int frame = 0;

	Mesh* house = nullptr;

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