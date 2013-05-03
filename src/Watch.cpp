#include <Watch.h>

Watch::Watch(bool isDebugFsm, bool isNoCls)
	: fsm_(*this)
	, isNoCls_(isNoCls)
	, mode_(TIME)
	, last_tick_(chr::steady_clock::now())
	, is24hours_(true)
	, curr_edit_(NONE)
	, isAlarmSet_(false)
	, isHourlySignalSet_(false)
	, isCountdownOn_(false)
	, wasSignalOn_(false)
	, countdownSignalTimestamp_(chr::steady_clock::time_point())
	, isCountdownRepeat_(false)
{
	fsm_.setDebugFlag(isDebugFsm);
}

void Watch::frame()
{
	if(!isNoCls_)
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
	// can't get blinking work, instead underline the field being edited
	const char* underline_start = "\33[4m";
	const char* underline_end = "\33[m";

	# define maybe_underline(x,y)\
	do { \
	if(curr_edit_ == (x)) std::cout << underline_start; \
	std::cout << (y); \
	if(curr_edit_ == (x)) std::cout << underline_end; \
	} while(0)

	if(shouldAlarm())
		std::cout << "*alarm*  ";

	if(shouldSignalHour())
		std::cout << "*hour*  ";

	if(shouldSignalCountdown())
		std::cout << "*countdown*  ";

	if(isAlarmSet_)
		std::cout << "(a) ";
	if(isHourlySignalSet_)
		std::cout << "(h) ";

	switch(mode_)
	{
		case TIME:
		{
			const char* weekdays[] =
				{ "SU", "MO", "TU", "WE", "TH", "FR", "SA" };

			// if any field is being edited, i.e. in the time setting mode
			// display year instead of weekday
			if(curr_edit_ == NONE)
				std::cout << weekdays[time_.weekday()];
			else
				maybe_underline(YEAR, time_.year()%2000);

			std::cout << "  ";
			maybe_underline(MONTH,time_.month());
			std::cout << "- ";
			maybe_underline(MONTHDAY,time_.monthday());
			std::cout << "\t ";

			if(is24hours_)
			{
				std::cout << "24  ";
				maybe_underline(HOUR,time_.hour());
			}
			else
			{
				std::cout << (time_.hour()<12? "AM  " : "PM  ");
				int am_pm_hours = time_.hour()%12;
				if(am_pm_hours == 0)
					am_pm_hours = 12;
				maybe_underline(HOUR,am_pm_hours);
			}
			std::cout << ":";
			maybe_underline(MIN,time_.minutes());
			std::cout << ":";
			maybe_underline(SEC,time_.seconds());
			std::cout << std::endl;

			return;
		}

		case ALARM:
		{
			std::cout << "AL  ";
			if(alarm_.month() == Time::ANY)
				maybe_underline(MONTH,"-");
			else
				maybe_underline(MONTH,alarm_.month());
			std::cout << "- ";
			if(alarm_.monthday() == Time::ANY)
				maybe_underline(MONTHDAY,"--");
			else
				maybe_underline(MONTHDAY,alarm_.monthday());
			std::cout << "\t ";
			if(is24hours_)
			{
				std::cout << "24  ";
				maybe_underline(HOUR,alarm_.hour());
			}
			else
			{
				std::cout << (alarm_.hour()<12? "AM  " : "PM  ");
				int am_pm_hours = alarm_.hour()%12;
				if(am_pm_hours == 0)
					am_pm_hours = 12;
				maybe_underline(HOUR,am_pm_hours);
			}
			std::cout << ":";
			maybe_underline(MIN,alarm_.minutes());
			std::cout << ":";
			maybe_underline(SEC,alarm_.seconds());
			std::cout << std::endl;

			return;
		}

		case COUNTDOWN:
		{
			std::cout << "T`A  ";
			if(is24hours_)
				std::cout << time_.hour();
			else
			{
				int am_pm_hours = alarm_.hour()%12;
				if(am_pm_hours == 0)
					am_pm_hours = 12;
				std::cout << am_pm_hours;
			}
			std::cout << ":" << time_.minutes();
			std::cout << "\t ";
			if(isCountdownRepeat_)
				std::cout << " au ";
			else
				std::cout << "    ";
			const Time& to_display = curr_edit_ != NONE?
				countdown_ : countdownCurr_;
			maybe_underline(HOUR, to_display.hour());
			std::cout << ":";
			maybe_underline(MIN, to_display.minutes());
			std::cout << ":";
			maybe_underline(SEC, to_display.seconds());
			std::cout << std::endl;

			return;
		}
		case STOPWATCH: std::cout << "STOPWATCH" << std::endl; return;
	}
	# undef maybe_underline
}
