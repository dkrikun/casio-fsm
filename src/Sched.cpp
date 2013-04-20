#include <Sched.h>

#include <unistd.h>	// for sleep()
#include <iostream>

Sched::Sched(Input* input, Watch* watch, Display* display)
	: input_(input)
	, watch_(watch)
	, display_(display)
{}

void Sched::run()
{
	while(!shouldStop())
	{
		const unsigned int period_usec = 333333;
		usleep(period_usec);

		// clear screen, normally this should be done in Display
		// but we want to fsm debug output to be shown (and not wiped away by this
		// clear screen)
		display_->clearScreen();

		input_->frame();
		watch_->frame();
	}
}
