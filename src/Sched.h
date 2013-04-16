#ifndef SCHED_H
#define SCHED_H

#include <Input.h>
#include <Watch.h>
#include <Display.h>

#include <unistd.h>	// for sleep()

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
		while(!shouldStop())
		{
			sleep(1);
			input_->frame();
			watch_->frame();
			display_->frame();
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
