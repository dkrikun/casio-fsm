
#include <Display.h>
#include <Watch.h>
#include <Input.h>
#include <unistd.h>


int main(int, char**)
{

	Display d;
	Watch w(&d);
	Input i(&w);

	while(true)
	{
		sleep(1);
		i.frame();
		if(i.shouldStop())
			break;
		w.frame();
		d.frame();
	}

	return 0;
}
