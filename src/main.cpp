
#include <Display.h>
#include <Watch.h>
#include <Input.h>
#include <Sched.h>


int main(int, char**)
{

	Display d;
	Watch w(&d);
	Input i(&w);

	Sched sched(&i, &w, &d);
	sched.run();

	return 0;
}
