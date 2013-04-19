#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <stdio.h>

#include <Time.h>


class Display
{
	public:
	Display()
		: mode_(TIME)
	{}

	public:
	void clearScreen() { std::cout << "\x1B[2J\x1B[H"; }

	void showTime() { mode_ = TIME; };
	void showAlarm() { mode_ = ALARM; };
	void showCountdown() { mode_ = COUNTDOWN; };
	void showStopwatch() { mode_ = STOPWATCH; };

	// TODO consider by ref
	void setTime(Time time)
	{ time_ = time; }


	void frame()
	{
		switch(mode_)
		{
			case TIME: std::cout << time_.asString() << std::endl; return;
			case ALARM: std::cout << "ALARM" << std::endl; return;
			case COUNTDOWN: std::cout << "COUNTDOWN" << std::endl; return;
			case STOPWATCH: std::cout << "STOPWATCH" << std::endl; return;
		}
	}


	private:
	Time time_;
	enum { TIME = 0, ALARM, COUNTDOWN, STOPWATCH } mode_;
};

#endif
