#ifndef ADVERTISEMENT_H
#define ADVERTISEMENT_H

#include <queue>
#include <iostream>
#include <string>
#include "Date.h"
#include "Bid.h"

using namespace std;

class Advertisement;

istream &operator>>(istream &stream, Advertisement &a);

class Advertisement {

  private:
	
    int number;
	int quantity;
    string title;
    string seller_email;
    string body;

    Date start;
    Date close;
    priority_queue<Bid> bids;

  public:

    Advertisement(void);
    Advertisement(const Advertisement &a);
    Advertisement (string title, string seller_email, string body, 
                   Date start, Date close, int quantity);

    virtual void setStart (const Date &start);
    virtual void setClose (const Date &close);
    virtual void setTitle (string title);
    virtual void setBody (string body);
    virtual void setNumber (int number);
    virtual void setEmail (string email);
	virtual void setQuantity (int quantity);

    virtual Date getStart () const;
    virtual Date getClose () const;
	virtual string getTitle() const;
	virtual string getBody() const;
    virtual string getEmail() const;
    virtual int getNumber () const;
	virtual int getQuantity() const;
    
	virtual bool operator==(const Advertisement&) const;

	virtual priority_queue<Bid>& getBids(void);
	virtual vector<Bid> getTopDutchBids (void) const;

};

#endif
