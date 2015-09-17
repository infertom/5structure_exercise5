#ifndef DATE_H
#define DATE_H

#include <iostream>

using namespace std;

class Date;

ostream &operator<<(ostream&, const Date&);
istream &operator>>(istream&, Date&);

class Date {

  private:
    int month;
    int day;
    int year;
	int hour;
	int minute;
	int second;

  public:
    
    Date(void);
    Date (int month, int day, int year, int hour, int minute, int second);
    
	virtual void setMonth(int&);	    
	virtual void setDay(int&);
	virtual void setYear(int&);
	virtual void setHour(int&);
	virtual void setMinute(int&);
	virtual void setSecond(int&);
	
	virtual int getMonth(void) const;	    
	virtual int getDay(void) const;	    
	virtual int getYear(void) const;	    
	virtual int getHour(void) const;	    
	virtual int getMinute(void) const;	    
	virtual int getSecond(void) const;	    

    virtual bool operator== (const Date &rhs);
    virtual bool operator< (const Date &left);

};

#endif
