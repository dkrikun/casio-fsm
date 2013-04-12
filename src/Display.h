#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>

class Display
{
	public:
	void showTime() { std::cout << "ShowTime" << std::endl; };
	void showAlarm() { std::cout << "ShowAlarm" << std::endl; };
	void showCountdown() { std::cout << "ShowCountdown" << std::endl; };
	void showStopwatch() { std::cout << "ShowStopwatch" << std::endl; };
};

#endif
