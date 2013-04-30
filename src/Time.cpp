#include <Time.h>

#include <assert.h>


Time::Time()
	: sec_(0), min_(0), hour_(0), weekday_(0)
	, month_(0), monthday_(0), year_(2000)
{}

void Time::inc()
{
	++sec_;
	if(sec_<60)
		return;
	sec_=0; ++min_;
	if(min_<60)
		return;
	min_=0; ++hour_;
	if(hour_<24)
		return;
	hour_=0;
	++weekday_;
	if(weekday_==7)
		weekday_=0;

	if(monthday_ < maxMonthday())
		return;

	monthday_ = 0; ++month_;
	if(month_<12)
		return;
	month_ = 0;
	if(year_<2099)
		++year_;


	checkInvariant();
}

int Time::maxMonthday() const
{
	return month_ == 1? (isLeapYear()? 28 : 29)
		: ((month_ == 0 || month_ == 2 || month_ == 4 || month_ == 6
			|| month_ == 7 || month_ == 9 || month_ == 11)? 31 : 30);
}

void Time::checkInvariant() const
{
	assert(sec_>=0 && sec_<60);
	assert(min_>=0 && min_<60);
	assert(hour_>=0 && hour_<24);
	assert(weekday_>=0 && weekday_<7);
	assert((month_>=0 && month_<12) || month_ == ANY);
	assert(year_>=2000 && year_<2100);		// accorcding to the watch spec
	
	if(monthday_ != ANY)
	{
		assert(monthday_>=0);
		if(month_ == 0 || month_ == 2 || month_ == 4 || month_ == 6
				|| month_ == 7 || month_ == 9 || month_ == 11)
			assert(monthday_<31);
		else if(month_ == 1)
			assert(monthday_<(isLeapYear()? 28 : 29));
		else
			assert(monthday_<30);
	}
}
	
