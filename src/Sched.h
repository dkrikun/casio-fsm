#ifndef SCHED_H
#define SCHED_H

#include <Input.h>
#include <Watch.h>
#include <Display.h>

#include <unistd.h>	// for sleep()
#include <iostream>

class Sched
{
	public:
	Sched(Input* input, Watch* watch, Display* display)
		: input_(input)
		, watch_(watch)
		, display_(display)
	{}

	public:
	void run()
	{
		unsigned int period_counter = 0;
		while(!shouldStop())
		{
			const unsigned int period_usec = 333333;
			usleep(period_usec);

			// clear screen, normally this should be done in Display
			// but we want to fsm debug output to be shown (and not wiped away by this
			// clear screen)
			display_->clearScreen();

			// check input each 33.3 msec
			input_->frame();

			// tick the clock once per sec
			if(period_counter++ == 2)
			{
				watch_->frame();
				period_counter = 0;
			}
		}
	}

	bool shouldStop() const
	{ return input_->shouldStop(); }

	private:
	Input* input_;
	Watch* watch_;
	Display* display_;
};

#endif
