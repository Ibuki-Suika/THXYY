#ifndef THBIUEFFECT_H
#define THBIUEFFECT_H

#include "../THCommon.h"

//��ը����Ч��
class THBiuEffect1:public RenderObject{
protected:
	int frame;
public:
	THBiuEffect1();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
};

#endif