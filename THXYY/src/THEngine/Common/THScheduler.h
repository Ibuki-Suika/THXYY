#ifndef THSCHEDULER_H
#define THSCHEDULER_H

#include "THObject.h"
#include "THList.h"
#include "THFrameTimer.h"

namespace THEngine
{
	class Scheduler : public Object
	{
	private:
		LinkedList<FrameTimer*> frameTimerList;

		using TimerFunc = std::function<void()>;

	public:
		Scheduler();
		Scheduler(const Scheduler& scheduler);
		virtual ~Scheduler();

		void Update();

		inline void AddTimer(FrameTimer* timer) { frameTimerList.Add(timer); }
		void AddTimer(int delay, TimerFunc run);
	};
}

#endif