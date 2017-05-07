#include "THScheduler.h"

namespace THEngine
{
	Scheduler::Scheduler()
	{
	}

	Scheduler::Scheduler(const Scheduler& scheduler) : Object(scheduler)
	{
		auto iter = const_cast<Scheduler&>(scheduler).frameTimerList.GetIterator();
		while (iter->HasNext())
		{
			auto timer = iter->Next();
			AddTimer((FrameTimer*)timer->Clone());
		}
	}

	Scheduler::~Scheduler()
	{
	}

	void Scheduler::Update()
	{
		auto iter = frameTimerList.GetIterator();
		while (iter->HasNext())
		{
			auto timer = iter->Next();

			if (timer->IsPaused() == false)
			{
				timer->frameLeft--;
				if (timer->frameLeft == 0)
				{
					timer->run();
					iter->Remove();
				}
			}
		}
	}

	void Scheduler::AddTimer(int delay, TimerFunc run)
	{
		FrameTimer* timer = new FrameTimer();
		timer->SetFrame(delay);
		timer->run = run;
		AddTimer(timer);
	}
}