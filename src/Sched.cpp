#include <Sched.h>

#include <unistd.h>	// for usleep()

Sched::Sched(Input* input, Watch* watch)
	: input_(input)
	, watch_(watch)
{}

void Sched::run()
{
	while(!shouldStop())
	{
		const unsigned int period_usec = 333333;
		usleep(period_usec);

		input_->frame();
		watch_->frame();
	}
}
