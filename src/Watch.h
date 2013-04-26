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
	void aPressed() { fsm_.A(); }
	void bPressed() { fsm_.B(); }
	void cPressed() { fsm_.C(); }
	void dPressed() { fsm_.D(); }
	void ePressed() { fsm_.E(); }

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


	// timeout to auto-return from time setting to time keeping mode, if no button
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
};

#endif
