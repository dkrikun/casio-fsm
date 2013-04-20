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
	Watch(Display* display, bool isDebugFsm)
		: display_(display)
		, fsm_(*this)
		, last_tick_(chr::steady_clock::now())
	{
		fsm_.setDebugFlag(isDebugFsm);
	}

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

	void frame()
	{
		chr::steady_clock::time_point now = chr::steady_clock::now();
		if(now - last_tick_ >= chr::seconds(1))
		{
			last_tick_ = now;
			fsm_.Tick();
		}

		display_->setTime(time_);
		display_->frame();
	}

	public:
	void showTime() { display_->showTime(); }
	void showAlarm() { display_->showAlarm(); }
	void showCountdown() { display_->showCountdown(); }
	void showStopwatch() { display_->showStopwatch(); }
	void incTime()	{ time_.inc(); }

	void resetSeconds() { time_.setSeconds(0); }
	int seconds() const { return time_.seconds(); }

	void incMinutes() { time_.setMinutes(time_.minutes() + 1); }
	void incHour() { time_.setHour(time_.hour() + 1); }
	void incYear() { time_.setYear(time_.year() + 1); }
	void incMonth() { time_.setMonth(time_.month() + 1); }
	void incDay() { time_.setMonthday(time_.monthday() + 1); }
	
	void invert24Pm() {};	//TODO

};

#endif
