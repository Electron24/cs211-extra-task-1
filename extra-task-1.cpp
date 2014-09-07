#include <iostream>
#include <cmath>
#include <string>
#include <assert.h>

using namespace std;

double const eps = DBL_EPSILON;

double seconds_difference(double time_1, double time_2)
{
	// your implementation goes here...
	/*
	Return the number of seconds later that a time in seconds
	time_2 is than a time in seconds time_1.
	>>> seconds_difference(1800.0, 3600.0)
	1800.0
	>>> seconds_difference(3600.0, 1800.0)
	-1800.0
	>>> seconds_difference(1800.0, 2160.0)
	360.0
	>>> seconds_difference(1800.0, 1800.0)
	0.0
	*/
	return time_2 - time_1;
}
double hours_difference(double time_1, double time_2)
{
	/*
	Return the number of hours later that a time in seconds
	time_2 is than a time in seconds time_1.
	>>> hours_difference(1800.0, 3600.0)
	0.5
	>>> hours_difference(3600.0, 1800.0)
	-0.5
	>>> hours_difference(1800.0, 2160.0)
	0.1
	>>> hours_difference(1800.0, 1800.0)
	0.0
	*/
	return seconds_difference(time_1, time_2) / 3600;
}
double to_float_hours(int hours, int minutes, int seconds)
{
	/*
	Return the total number of hours in the specified number
	of hours, minutes, and seconds.
	Precondition: 0 <= minutes < 60 and 0 <= seconds < 60
	>>> to_float_hours(0, 15, 0)
	0.25
	>>> to_float_hours(2, 45, 9)
	2.7525
	>>> to_float_hours(1, 0, 36)
	1.01
	*/
	return hours + minutes / 60.0 + seconds / 3600.0;
}
double to_24_hour_clock(double hours)
{
	/*
	hours is a number of hours since midnight. Return the
	hour as seen on a 24-hour clock.
	Precondition: hours >= 0
	>>> to_24_hour_clock(24)
	0
	>>> to_24_hour_clock(48)
	0
	>>> to_24_hour_clock(25)
	1
	>>> to_24_hour_clock(4)be
	4
	>>> to_24_hour_clock(28.5)
	4.5
	You may wish to inspect various function in <cmath> to work
	with integer and fractional part of a hours separately.
	*/
	return fmod<double, double>(hours, 24.0);

}
/*
Implement three functions
* get_hours
* get_minutes
* get_seconds
They are used to determine the hours part, minutes part and seconds part
of a time in seconds. E.g.:
>>> get_hours(3800)
1
>>> get_minutes(3800)
3
>>> get_seconds(3800)
20
In other words, if 3800 seconds have elapsed since midnight,
it is currently 01:03:20 (hh:mm:ss).
*/
int get_hours(int t)
{
	return t / 3600;
}

int get_minutes(int t)
{
	return (t - get_hours(t) * 3600) / 60;
}


int get_seconds(int t)
{
	return t - get_hours(t) * 3600 - get_minutes(t) * 60;
}

string get_hms(int t)
{
	return to_string(get_hours(t)) + ":" + to_string(get_minutes(t)) + ":" + to_string(get_seconds(t));
}

double time_to_utc(int utc_offset, double time)
{
	/*
	Return time at UTC+0, where utc_offset is the number of hours away from
	UTC+0.
	You may be interested in:
	https://en.wikipedia.org/wiki/Coordinated_Universal_Time
	>>> time_to_utc(+0, 12.0)
	12.0
	>>> time_to_utc(+1, 12.0)
	11.0
	>>> time_to_utc(-1, 12.0)
	13.0
	>>> time_to_utc(-11, 18.0)
	5.0
	>>> time_to_utc(-1, 0.0)
	1.0
	>>> time_to_utc(-1, 23.0)
	0.0
	*/
	return  to_24_hour_clock(seconds_difference(utc_offset, time));
}
double time_from_utc(int utc_offset, double time)
{
	/*
	Return UTC time in time zone utc_offset.
	>>> time_from_utc(+0, 12.0)
	12.0
	>>> time_from_utc(+1, 12.0)
	13.0
	>>> time_from_utc(-1, 12.0)
	11.0
	>>> time_from_utc(+6, 6.0)
	12.0
	>>> time_from_utc(-7, 6.0)
	23.0
	>>> time_from_utc(-1, 0.0)
	23.0
	>>> time_from_utc(-1, 23.0)
	22.0
	>>> time_from_utc(+1, 23.0)
	0.0
	*/
	return to_24_hour_clock((utc_offset + time < 0) ? 24 + utc_offset + time : utc_offset + time);
}

int main()
{
	assert(fabs(seconds_difference(1800.0, 3600.0) - 1800.0) < eps);
	assert(fabs(seconds_difference(3600.0, 1800.0) + 1800.0) < eps);
	assert(fabs(seconds_difference(1800.0, 2160.0) - 360.0) < eps);
	assert(fabs(seconds_difference(1800.0, 1800.0) - 0.0) < eps);

	assert(fabs(hours_difference(1800.0, 3600.0) - 0.5) < eps);
	assert(fabs(hours_difference(3600.0, 1800.0) + 0.5) < eps);
	assert(fabs(hours_difference(1800.0, 2160.0) - 0.1) < eps);
	assert(fabs(hours_difference(1800.0, 1800.0) - 0.0) < eps);

	assert(fabs(to_float_hours(0, 15, 0) - 0.25) < eps);
	assert(fabs(to_float_hours(2, 45, 9) - 2.7525) < eps);
	assert(fabs(to_float_hours(1, 0, 36) - 1.01) < eps);

	assert(fabs(to_24_hour_clock(24) - 0.0) < eps);
	assert(fabs(to_24_hour_clock(48) - 0.0) < eps);
	assert(fabs(to_24_hour_clock(25) - 1.0) < eps);
	assert(fabs(to_24_hour_clock(4) - 4.0) < eps);
	assert(fabs(to_24_hour_clock(28.5) - 4.5) < eps);

	assert(get_hours(3800) == 1);
	assert(get_minutes(3800) == 3);
	assert(get_seconds(3800) == 20);

	assert(fabs(time_to_utc(+0, 12.0) - 12.0) < eps);
	assert(fabs(time_to_utc(+1, 12.0) - 11.0) < eps);
	assert(fabs(time_to_utc(-1, 12.0) - 13.0) < eps);
	assert(fabs(time_to_utc(-11, 18.0) - 5.0) < eps);
	assert(fabs(time_to_utc(-1, 0.0) - 1.0) < eps);
	assert(fabs(time_to_utc(-1, 23.0) - 0.0) < eps);

	assert(fabs(time_from_utc(+0, 12.0) - 12.0) < eps);
	assert(fabs(time_from_utc(+1, 12.0) - 13.0) < eps);
	assert(fabs(time_from_utc(-1, 12.0) - 11.0) < eps);
	assert(fabs(time_from_utc(+6, 6.0) - 12.0) < eps);
	assert(fabs(time_from_utc(-7, 6.0) - 23.0) < eps);
	assert(fabs(time_from_utc(-1, 0.0) - 23.0) < eps);
	assert(fabs(time_from_utc(-1, 23.0) - 22.0) < eps);
	assert(fabs(time_from_utc(+1, 23.0) - 0.0) < eps);
}
