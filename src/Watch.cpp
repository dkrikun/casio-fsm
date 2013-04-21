#include <Watch.h>

Watch::Watch(Display* display, bool isDebugFsm)
	: display_(display)
	, fsm_(*this)
	, last_tick_(chr::steady_clock::now())
{
	fsm_.setDebugFlag(isDebugFsm);
}

void Watch::frame()
{
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

	display_->setTime(time_);
	display_->frame();
}

