#include "THObject.h"
#include "THDefine.h"

namespace THEngine
{
	Object::Object()
	{
		refCount = 0;
	}

	Object::~Object()
	{

	}

	void Object::Retain()
	{
		refCount++;
	}

	void Object::Release()
	{
		ASSERT(refCount > 0);
		refCount--;
		if (refCount == 0)
		{
			delete this;
		}
	}
}
