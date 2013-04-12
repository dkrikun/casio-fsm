#ifndef WATCH_H
#define WATCH_H

#include <Watch_sm.h>
#include <Display.h>

class Watch
{
	public:
	Watch(Display* display)
		: display_(display)
		, fsm_(*this)
	{}

	private:
	Display* display_;
	WatchContext fsm_;

	public:
	void aPressed() { /*fsm_->A();*/ }
	void bPressed() { /*fsm_->B();*/ }
	void cPressed() { fsm_.C(); }
	void dPressed() { /*fsm_->D();*/ }
	void lightPressed() { /*fsm_->Light();*/ }

	public:
	void showTime() { display_->showTime(); }
	void showAlarm() { display_->showAlarm(); }
	void showCountdown() { display_->showCountdown(); }
	void showStopwatch() { display_->showStopwatch(); }
};

#endif
