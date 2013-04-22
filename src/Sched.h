#ifndef SCHED_H
#define SCHED_H

#include <Input.h>
#include <Watch.h>

class Sched
{
	public:
	Sched(Input* input, Watch* watch);

	public:
	void run();

	bool shouldStop() const
	{ return input_->shouldStop(); }

	private:
	Input* input_;
	Watch* watch_;
};

#endif
