#ifndef TH_DATA_STACK_H
#define TH_DATA_STACK_H

#include "../Common/THCommon.h"
#include "../Math/Matrix.h"

namespace THEngine
{
	class DataStack : public Object
	{
	private:
		static DataStack* instance;

		Vector3f position;

	private:
		DataStack();

		static DataStack* GetInstance();

		void Reset();

	public:
		virtual ~DataStack();

		friend class Game;
		friend class Layer;
		friend class GameObject;
	};
}

#endif