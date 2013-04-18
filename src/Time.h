#ifndef TIME_H
#define TIME_H

#include <string>

struct Time
{
	public:
	Time();

	void inc();

	void setSeconds(int value)
	{ sec_ = value; checkInvariant(); }

	void setMinutes(int value)
	{ min_ = value; checkInvariant(); }

	void setHour(int value)
	{ hour_ = value; checkInvariant(); }

	void setMonthday(int value)
	{
		int delta = value - monthday_;
		monthday_ = value;
		weekday_ = (weekday_ + delta)%7;

		checkInvariant();
	}

	void setMonth(int value)
	{ month_ = value; checkInvariant(); }

	void setYear(int value)
	{ year_ = value; checkInvariant(); }


	int seconds() const { return sec_; }
	int minutes() const { return min_; }
	int hour() const { return hour_; }
	int weekday() const { return weekday_; }
	int month() const { return month_; }
	int monthday() const { return monthday_; }
	int year() const { return year_; }

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
