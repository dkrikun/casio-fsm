#ifndef TIME_H
#define TIME_H

#include <string>

struct Time
{
	public:
	Time();

	void inc();
	std::string asString(bool is24hours = true) const;

	private:
	int sec_;
	int min_;
	int hour_;
	int weekday_;
	int month_;
	int monthday_;
	int year_;

	private:
	void checkInvariant() const;

	bool isLeapYear() const
	{
		return (!year_ % 4 && year_ % 100) || (!year_ % 400);
	}
};


#endif
