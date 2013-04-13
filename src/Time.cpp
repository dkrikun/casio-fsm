#include <Time.h>

#include <assert.h>
#include <sstream>


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

	const int max_monthday = month_ == 1? (isLeapYear()? 28 : 29)
		: ((month_ == 0 || month_ == 2 || month_ == 4 || month_ == 6
			|| month_ == 7 || month_ == 9 || month_ == 11)? 31 : 30);
	if(monthday_ < max_monthday)
		return;

	monthday_ = 0; ++month_;
	if(month_<12)
		return;
	month_ = 0;
	if(year_<2099)
		++year_;


	checkInvariant();
}


std::string Time::asString(bool is24hours) const
{
	std::stringstream ss;

	const char* weekdays[] = { "SU", "MO", "TU", "WE", "TH", "FR", "SA" };

	ss << weekdays[weekday_] << "  " << monthday_ << "- " << year_%2000 << "\t";

	if(is24hours)
		ss << "24  " << hour_;
	else
		ss << (hour_<13? "AM  " : "PM  ") << hour_%13;
	ss << ":" << min_ << ":" << sec_;

	return ss.str();
}

void Time::checkInvariant() const
{
	assert(sec_>=0 && sec_<60);
	assert(min_>=0 && min_<60);
	assert(hour_>=0 && hour_<24);
	assert(weekday_>=0 && weekday_<7);
	assert(month_>=0 && month_<12);
	assert(year_>=2000 && year_<2100);		// accorcding to the watch spec
	
	assert(monthday_>=0);
	if(month_ == 0 || month_ == 2 || month_ == 4 || month_ == 6
			|| month_ == 7 || month_ == 9 || month_ == 11)
		assert(monthday_<31);
	else if(month_ == 1)
		assert(monthday_<(isLeapYear()? 28 : 29));
	else
		assert(monthday_<30);
}
	
