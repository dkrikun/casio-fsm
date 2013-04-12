
#include <Display.h>
#include <Watch.h>
#include <Input.h>


int main(int, char**)
{

	Display d;
	Watch w(&d);
	Input i(&w);


	i.Run();

	return 0;
}
