#include <Watch.h>
#include <sstream>

Watch::Watch(bool isDebugFsm)
	: fsm_(*this)
	, last_tick_(chr::steady_clock::now())
	, mode_(TIME)
	, is24hours_(true)
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
		case TIME:
		{
			const char* weekdays[] = { "SU", "MO", "TU", "WE", "TH", "FR", "SA" };

			std::cout << weekdays[time_.weekday()] << "  " << time_.monthday() << "- " << time_.year()%2000 << "\t";

			if(is24hours_)
				std::cout << "24  " << time_.hour();
			else
				std::cout << (time_.hour()<13? "AM  " : "PM  ") << time_.hour()%13;
			std::cout << ":" << time_.minutes() << ":" << time_.seconds()
				<< std::endl;

			return;
		}

		case ALARM: std::cout << "ALARM" << std::endl; return;
		case COUNTDOWN: std::cout << "COUNTDOWN" << std::endl; return;
		case STOPWATCH: std::cout << "STOPWATCH" << std::endl; return;
	}
}
