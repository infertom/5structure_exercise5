#include "Date.h"

ostream &operator<<(ostream& io, const Date& d)
{
    io<<d.getMonth()<<"/"<<d.getDay()<<"/"<<d.getYear()<<" "<<d.getHour()<<":"<<d.getMinute()<<":"<<d.getSecond()<<endl;
	return io;
}

istream &operator>>(istream& in, Date& d)
{
	char str[100];
	int x = 0, st = 0;
	in>>str;
	while ( !(str[st] >= '0' && str[st] <= '9') ) st++;
	while ( str[st++] != '/' ) x = x * 10 + (str[st-1] - '0');
	d.setMonth(x);x = 0;
	while ( str[st++] != '/' ) x = x * 10 + (str[st-1] - '0');
	d.setDay(x);x = 0;
	while ( str[st++] != '\0' ) x = x * 10 + (str[st-1] - '0');
	d.setYear(x);x = 0;

	in>>str;
	st = 0;
	while ( str[st++] != ':' ) x = x * 10 + (str[st-1] - '0');
	d.setHour(x);x = 0;
	while ( str[st++] != ':' ) x = x * 10 + (str[st-1] - '0');
	d.setMinute(x);x = 0;
	while ( str[st++] != '\0' ) x = x * 10 + (str[st-1] - '0');
	d.setSecond(x);x = 0;

	return in;
}

Date::Date():month(0),day(0),year(0),hour(0),minute(0),second(0)
{

}

Date::Date(int month, int day, int year, int hour, int minute, int second)
{
	setMonth(month);
	setDay(day);
	setYear(year);
	setHour(hour);
	setMinute(minute);
	setSecond(second);
}


void Date::setMonth(int &m)
{
	month = m;
}

void Date::setDay(int &d)
{
	day = d;
}

void Date::setYear(int &y)
{
	year = y;
}

void Date::setHour(int &h)
{
	hour = h;
}

void Date::setMinute(int &m)
{
	minute = m;
}

void Date::setSecond(int &s)
{
	second = s;
}


int Date::getMonth() const
{
	return month;
}

int Date::getDay() const
{
	return day;
}

int Date::getYear() const
{
	return year;
}

int Date::getHour() const
{
	return hour;
}

int Date::getMinute() const
{
	return minute;
}

int Date::getSecond() const
{
	return second;
}

bool Date::operator==(const Date &rhs)
{
	if ( month == rhs.getMonth() && day == rhs.getDay() && year == rhs.getYear() && hour == rhs.getHour() && minute == rhs.getMinute() && second == rhs.getSecond() ) return true;
	else return false;
}

bool Date::operator<(const Date &rhs)
{
    int x = rhs.getYear();
    x = x * 100 + rhs.getMonth();
    x = x * 100 + rhs.getDay();
    x = x * 100 + rhs.getHour();
    x = x * 100 + rhs.getMinute();
    x = x * 100 + rhs.getSecond();

    int y = year;
    y = y * 100 + month;
    y = y * 100 + day;
    y = y * 100 + hour;
    y = y * 100 + minute;
    y = y * 100 + second;

	if ( y < x ) return true;
	else return false;
}
