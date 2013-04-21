#ifndef WATCH_H
#define WATCH_H

#include <Watch_sm.h>
#include <Display.h>
#include <Time.h>

#include <boost/chrono/chrono.hpp>
namespace chr = boost::chrono;


class Watch
{
	public:
	Watch(Display* display, bool isDebugFsm);

	private:
	Display* display_;
	WatchContext fsm_;

	Time time_;
	chr::steady_clock::time_point last_tick_;

	public:
	void aPressed() { fsm_.A(); }
	void bPressed() { fsm_.B(); }
	void cPressed() { fsm_.C(); }
	void dPressed() { fsm_.D(); }
	void ePressed() { fsm_.E(); }

	void frame();

	public:
	void showTime() { display_->showTime(); }
	void showAlarm() { display_->showAlarm(); }
	void showCountdown() { display_->showCountdown(); }
	void showStopwatch() { display_->showStopwatch(); }
	void incTime()	{ time_.inc(); }

	void resetSeconds() { time_.setSeconds(0); }
	int seconds() const { return time_.seconds(); }

	void incMinutes() { time_.incMinutes(); }
	void incHour() { time_.incHour(); }
	void incYear() { time_.incYear(); }
	void incMonth() { time_.incMonth(); }
	void incDay() { time_.incDay(); }
	
	void invert24Pm() {};	//TODO

};

#endif
