#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <Watch.h>

class Input
{
	public:
	Input(Watch* watch, bool isDebug);
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
	const bool isDebug_;
};


#endif
