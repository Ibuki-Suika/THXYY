#ifndef ITEM_LINE_H
#define ITEM_LINE_H

#include <THEngine.h>

using namespace THEngine;

class ItemLine : public Sprite
{
private:
	int frame = 0;
	bool bright = true;

public:
	ItemLine() = default;
	virtual ~ItemLine() = default;

	virtual void Update() override;
};

#endif
