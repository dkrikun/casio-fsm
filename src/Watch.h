#ifndef WATCH_H
#define WATCH_H

#include <Watch_sm.h>
#include <Display.h>
#include <Time.h>


class Watch
{
	public:
	Watch(Display* display)
		: display_(display)
		, fsm_(*this)
	{
		fsm_.setDebugFlag(true);
	}

	private:
	Display* display_;
	WatchContext fsm_;
	Time time_;

	public:
	void aPressed() { /*fsm_->A();*/ }
	void bPressed() { /*fsm_->B();*/ }
	void cPressed() { fsm_.C(); }
	void dPressed() { /*fsm_->D();*/ }
	void ePressed() { /*fsm_->E();*/ }

	void frame()
	{
		fsm_.Tick();
		display_->setTime(time_);
	}

	public:
	void showTime() { display_->showTime(); }
	void showAlarm() { display_->showAlarm(); }
	void showCountdown() { display_->showCountdown(); }
	void showStopwatch() { display_->showStopwatch(); }
	void incTime()	{ time_.inc(); }

};

#endif
