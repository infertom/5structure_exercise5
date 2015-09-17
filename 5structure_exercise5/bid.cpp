#include "Bid.h"

istream &operator>>(istream &stream, Bid &b)
{
	string email;
	float amout;
	int quantity;
	Date date;
	stream>>email>>amout>>quantity>>date;
	b.setEmail(email);
	b.setAmount(amout);
	b.setQuantity(quantity);
	b.setDate(date);

	return stream;
}

Bid::Bid():email(""),amount(0),quantity(0),date()
{

}

Bid::Bid(const Bid &b)
{
	email = b.getEmail();
	amount = b.getAmount();
	quantity = b.getQuantity();
	date = b.getDate();
}

Bid::Bid (string email, float amount, int quantity, Date date)
{
	this->email = email;
	this->amount = amount;
	this->quantity = quantity;
	this->date = date;
}

string Bid::getEmail () const
{
	return email;
}

float Bid::getAmount () const
{
	return amount;
}

int Bid::getQuantity () const
{
	return quantity;
}

Date Bid::getDate () const
{
	return date;
}

void Bid::setEmail(const string &email)
{
	this->email = email;
}

void Bid::setAmount(const float &amout)
{
	this->amount = amout;
}

void Bid::setQuantity(const int &quantity)
{
	this->quantity = quantity;
}

void Bid::setDate(const Date &date)
{
	this->date = date;
}

bool Bid::operator< (const Bid &rhs) const
{
	return (amount < rhs.getAmount());
}

bool Bid::operator== (const Bid &rhs) const
{
	return (amount == rhs.getAmount());
}