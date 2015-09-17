#include "Advertisement.h"

istream &operator>>(istream &stream, Advertisement &a)
{
	string str;
	int q;
	Date d;
	stream>>str;
	a.setTitle(str);
	stream>>str;
	a.setEmail(str);
	stream>>q;
	a.setQuantity(q);
	stream>>d;
	a.setStart(d);
	stream>>d;
	a.setClose(d);
	stream>>str;
	a.setBody(str);

	return stream;
}

Advertisement::Advertisement():number(0),quantity(0),title(""),seller_email(""),body("")
{

}

Advertisement::Advertisement(const Advertisement &a)
{
	number = a.getNumber();
	quantity = a.getQuantity();
	title = a.getTitle();
	seller_email = a.getEmail();
	body = a.getBody();
	start = a.getStart();
	close = a.getClose();
}

Advertisement::Advertisement(string title, string seller_email, string body, 
	Date start, Date close, int quantity)
{
	this->title = title;
	this->seller_email = seller_email;
	this->body = body;
	this->start = start;
	this->close = close;
	this->quantity = quantity;
}

void Advertisement::setStart (const Date &start)
{
	this->start = start;
}

void Advertisement::setClose (const Date &close)
{
	this->close = close;
}

void Advertisement::setTitle (string title)
{
	this->title = title;
}

void Advertisement::setBody (string body)
{
	this->body = body;
}

void Advertisement::setNumber (int number)
{
	this->number = number;
}

void Advertisement::setEmail (string email)
{
	this->seller_email = email;
}

void Advertisement::setQuantity (int quantity)
{
	this->quantity = quantity;
}

Date Advertisement::getStart () const
{
	return start;
}

Date Advertisement::getClose () const
{
	return close;
}

string Advertisement::getTitle() const
{
	return title;
}

string Advertisement::getBody() const
{
	return body;
}

string Advertisement::getEmail() const
{
	return seller_email;
}

int Advertisement::getNumber () const
{
	return number;
}

int Advertisement::getQuantity() const
{
	return quantity;
}

bool Advertisement::operator==(const Advertisement &a) const
{
	if ( a.getNumber() == this->number ) return true;
	else return false;
}