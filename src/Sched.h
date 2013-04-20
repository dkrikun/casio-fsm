#ifndef SCHED_H
#define SCHED_H

#include <Input.h>
#include <Watch.h>
#include <Display.h>

class Sched
{
	public:
	Sched(Input* input, Watch* watch, Display* display);

	public:
	void run();

	bool shouldStop() const
	{ return input_->shouldStop(); }

	private:
	Input* input_;
	Watch* watch_;
	Display* display_;
};

#endif
