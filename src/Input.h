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
	void displayUsage() const
	{
		std::cout << "usage: a,b,c,d,e - buttons labeled A,B,C,D,E\n"
			<< "\tu - display this message\n"
			<< "\tq - quit application"
			<< std::endl;
	}


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
