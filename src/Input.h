#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <Watch.h>

class Input
{
	public:
	Input(Watch* watch);
	~Input();

	private:
	Watch* watch_;

	public:
	void displayUsage() const;


	void frame();
# if 0
	void run()
	{
		while(!shouldStop())
			frame();
	}
# endif

	bool shouldStop() const
	{ return shouldStop_; }

	private:
	bool shouldStop_;
};


#endif
