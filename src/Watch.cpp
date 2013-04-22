#include <Watch.h>

Watch::Watch(bool isDebugFsm)
	: fsm_(*this)
	, last_tick_(chr::steady_clock::now())
	, mode_(TIME)
{
	fsm_.setDebugFlag(isDebugFsm);
}

void Watch::frame()
{
	clearScreen();

	// invoke fsm_.Tick() for each second passed since last frame()
	// this is in order to compensate for Sched's too slow clock, just in
	// case it *might* be
	chr::steady_clock::time_point now = chr::steady_clock::now();
	if(now - last_tick_ >= chr::seconds(1))
	{
		size_t num_cycles = (now - last_tick_)/chr::seconds(1);

		last_tick_ = now;
		for(; num_cycles > 0; --num_cycles)
			fsm_.Tick();
	}

	display();
}

void Watch::display() const
{
	switch(mode_)
	{
		case TIME: std::cout << time_.asString() << std::endl; return;
		case ALARM: std::cout << "ALARM" << std::endl; return;
		case COUNTDOWN: std::cout << "COUNTDOWN" << std::endl; return;
		case STOPWATCH: std::cout << "STOPWATCH" << std::endl; return;
	}
}
