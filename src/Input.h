#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <Watch.h>

#include <stdio.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <unistd.h>


void init_keyboard();
void close_keyboard();
int kbhit();
int readch();

class Input
{
	public:
	Input(Watch* watch)
		: watch_(watch)
	{}

	private:
	Watch* watch_;

	public:
	void DisplayUsage()
	{
		std::cout << "usage: a,b,c,d - buttons labeled A,B,C,D\n"
			<< "\tl - backlight\n"
			<< "\tu - display this message\n"
			<< "\tq - quit application"
			<< std::endl;
	}


	void Run()
	{
		init_keyboard();
		DisplayUsage();

		while(true)
		{
			if(!kbhit())
				continue;

			char ch = readch();
			std::cout << "ch=" << ch << std::endl;

			if(ch == 'q' || ch == 'Q')
				break;

			bool recognized = false;
			if(ch == 'u' || ch == 'U')
			{
				recognized = true;
				DisplayUsage();
				continue;
			}

			if(ch == 'a' || ch == 'A')
			{
				recognized = true;
				watch_->aPressed();
			}

			if(ch == 'b' || ch == 'B')
			{
				recognized = true;
				watch_->bPressed();
			}	

			if(ch == 'c' || ch == 'C')
			{
				recognized = true;
				watch_->cPressed();
			}

			if(ch == 'd' || ch == 'D')
			{
				recognized = true;
				watch_->dPressed();
			}	

			if(ch == 'l' || ch == 'L')
			{
				recognized = true;
				watch_->lightPressed();
			}

			
			if(!recognized)
			{
				std::cout << "not recognized input: " << ch << "\n";
				DisplayUsage();
			}
		}
		
		close_keyboard();
	}
};


#endif
