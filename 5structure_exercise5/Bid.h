#ifndef BID_H
#define BID_H

#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

class Bid;

istream &operator>>(istream &stream, Bid &b);

class Bid {

  private:

    string email;
    float amount;
	int quantity;
	Date date;

  public:
  
    Bid(void);
    Bid(const Bid &b);
    Bid (string email, float amount, int quantity, Date date);

    virtual string getEmail () const ;
    virtual float getAmount () const;
	virtual int getQuantity () const;
	virtual Date getDate () const;
	
	virtual void setEmail(const string&);
	virtual void setAmount(const float&);
	virtual void setQuantity(const int&);
	virtual void setDate(const Date&);

    virtual bool operator< (const Bid &rhs) const;
    virtual bool operator== (const Bid &rhs) const;
};

#endif
