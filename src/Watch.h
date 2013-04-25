#ifndef WATCH_H
#define WATCH_H

#include <Watch_sm.h>
#include <Time.h>

#include <boost/chrono/chrono.hpp>
namespace chr = boost::chrono;


class Watch
{
	public:
	Watch(bool isDebugFsm);

	private:
	WatchContext fsm_;

	Time time_;
	chr::steady_clock::time_point last_tick_;
	enum { TIME = 0, ALARM, COUNTDOWN, STOPWATCH } mode_;
	bool is24hours_;

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

	public:
	// various actions, invoked from within the fsm
	void showAlarm() { mode_ = ALARM; }
	void showCountdown() { mode_ = COUNTDOWN; }
	void showStopwatch() { mode_ = STOPWATCH; }
	void showTime() { mode_ = TIME; }

	void incTime()	{ time_.inc(); }

	void resetSeconds() { time_.setSeconds(0); }
	int seconds() const { return time_.seconds(); }

	void incMinutes() { time_.incMinutes(); }
	void incHour() { time_.incHour(); }
	void incYear() { time_.incYear(); }
	void incMonth() { time_.incMonth(); }
	void incDay() { time_.incDay(); }
	
	void invert24Pm()
	{
		is24hours_ = !is24hours_;
	};

};

#endif
