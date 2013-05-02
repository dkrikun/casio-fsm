#ifndef WATCH_H
#define WATCH_H

#include <Watch_sm.h>
#include <Time.h>

#include <boost/chrono/chrono.hpp>
namespace chr = boost::chrono;


class Watch
{
	public:
	Watch(bool isDebugFsm, bool isNoCls);

	private:
	WatchContext fsm_;
	bool isNoCls_;

	public:
	// events triggered by Input
	enum Button { A = 0, B,C,D,E };

	void buttonPressed(Button b)
	{
		if(shouldSignalCountdown())
		{
			cancelSignalCountdown();
			return;
		}

		switch(b)
		{
			case A: fsm_.A(); return;
			case B: fsm_.B(); return;
			case C: fsm_.C(); return;
			case D: fsm_.D(); return;
			case E: fsm_.E(); return;
		}
	}

	// frame, called by Sched each cycle
	void frame();

	private:
	// output
	void clearScreen() const { std::cout << "\x1B[2J\x1B[H"; }
	void display() const;

	// top level mode selection
	private:
	enum { TIME = 0, ALARM, COUNTDOWN, STOPWATCH } mode_;
	public:
	void showAlarm() { mode_ = ALARM; }
	void showCountdown() { mode_ = COUNTDOWN; }
	void showStopwatch() { mode_ = STOPWATCH; }
	void showTime() { mode_ = TIME; }

	// increment time each second
	private:
	Time time_;
	chr::steady_clock::time_point last_tick_;
	public:
	void incTime()	{ time_.inc(); }

	// whether to show 24-hours or AM-PM display
	private:
	bool is24hours_;
	public:
	void invert24Pm()
	{ is24hours_ = !is24hours_; };

	// methods to edit specific field in the time setting mode
	void resetSeconds() { time_.setSeconds(0); }
	int seconds() const { return time_.seconds(); }

	void incMinutes() { time_.incMinutes(); }
	void incHour() { time_.incHour(); }
	void incYear() { time_.incYear(); }
	void incMonth() { time_.incMonth(); }
	void incDay() { time_.incDay(); }

	// field being edited
	public:
	enum CurrEdit { NONE = 0, SEC, MIN, HOUR, MONTHDAY, MONTH, YEAR };
	private:
	CurrEdit curr_edit_;
	public:
	void setCurrEdit(CurrEdit value)
	{ curr_edit_ = value; }


	// timeout to auto-return from editing modes if no button
	// has been pressed for a while
	private:
	chr::steady_clock::time_point return_timestamp_;	// last time when a
														// button press has
														// been registered
	public:
	void resetReturnTimeout()
	{ return_timestamp_ = chr::steady_clock::now(); }

	// seconds since last button pressed
	int returnTimeoutElapsed() const
	{
		chr::nanoseconds delta = chr::steady_clock::now() - return_timestamp_;
		return chr::duration_cast<chr::seconds>(delta).count();
	}

	private:
	bool isAlarmSet_;
	bool isHourlySignalSet_;
	Time alarm_;

	public:
	void incAlarmMinutes() { alarm_.incMinutes(); }
	void incAlarmHour() { alarm_.incHour(); }
	void incAlarmMonth() { alarm_.incMonth(true); }
	void incAlarmDay() { alarm_.incDay(true); }

	void setAlarmOn() { isAlarmSet_ = true; }
	// cycle through types
	// both on -> both off -> alarm only -> hourly signal only
	// and returns to both on
	void switchAlarmType()
	{
		if(isAlarmSet_)
		{
			isAlarmSet_ = false;
			isHourlySignalSet_ = !isHourlySignalSet_;
		}
		else
			isAlarmSet_ = true;
	}

	bool shouldAlarm() const
	{
		if(!isAlarmSet_)
			return false;

		const int alarm_duration_sec = 20;
		return ((time_.month() == alarm_.month()) || alarm_.month() == Time::ANY)
			&& ((time_.monthday() == alarm_.monthday())
					|| alarm_.monthday() == Time::ANY)
			&& (time_.hour() == alarm_.hour())
			&& (time_.minutes() == alarm_.minutes())
			&& (time_.seconds() - alarm_.seconds() <= alarm_duration_sec);
	}

	bool shouldSignalHour() const
	{
		if(!isHourlySignalSet_)
			return false;

		return time_.minutes() == 0 && time_.seconds() <= 1;
	}

	private:
	Time countdown_, countdownCurr_;
	bool isCountdownOn_;
	bool wasSignalOn_;
	chr::steady_clock::time_point countdownSignalTimestamp_;

	public:
	// incCountdown* are for editing countdown time
	void incCountdownSeconds() { countdown_.incSeconds(); }
	void incCountdownMinutes() { countdown_.incMinutes(); }
	void incCountdownHour() { countdown_.incHour(); }

	void resetCountdown()
	{
		std::cout << "reset countdown" << std::endl;
		countdownCurr_ = countdown_;
	}

	// invoked every frame
	void decCountdown()
	{
		// reset countdown after the signal is over
		wasSignalOn_ = wasSignalOn_ || shouldSignalCountdown();
		if(wasSignalOn_ && !shouldSignalCountdown())
		{
			assert(!isCountdownOn_);

			wasSignalOn_ = false;
			resetCountdown();
		}

		if(!isCountdownOn_)
			return;

		// first dec, and then check equality to zero,
		// because 00:00:00 is actually means a period of 24 hours,
		// according to the spec
		countdownCurr_.decPartial();
		if(countdownCurr_.seconds() == 0 && countdownCurr_.minutes() == 0
				&& countdownCurr_.hour() == 0
				&& countdownCurr_.monthday() == 0)
		{
			// timestamp initiates countdown signal
			countdownSignalTimestamp_ = chr::steady_clock::now();
			isCountdownOn_ = false;
		}
	}

	void cancelSignalCountdown()
	{
		resetCountdown();
		wasSignalOn_ = false;
		countdownSignalTimestamp_ = chr::steady_clock::time_point();
	}

	// is countdown in progress switch
	void invertCountdownOn()
	{
		if(wasSignalOn_)
		{
			cancelSignalCountdown();
			return;
		}

		isCountdownOn_ = !isCountdownOn_;
	}


	bool isCountdownOn() const { return isCountdownOn_; }


	// signal for 10 sec. when the countdown drops to zero
	private:
	bool shouldSignalCountdown() const
	{
		const chr::seconds delta = chr::duration_cast<chr::seconds>
			(chr::steady_clock::now() - countdownSignalTimestamp_);

		return delta <= chr::seconds(10);
	}
};


#endif
