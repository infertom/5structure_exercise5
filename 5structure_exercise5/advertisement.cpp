#include "Advertisement.h"
#include <cstring>

istream &operator>>(istream &stream, Advertisement &a)
{
	string str, temp;
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
	str = "";
	while ( stream >> temp && temp != "" ) str = str + temp + " ";
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
	return (a.getNumber() == number);
}

priority_queue<Bid>& Advertisement::getBids(void)
{
	return bids;
}

/************************************************************************/
/* getTopDutchBids                                                                     */
/************************************************************************/

vector<Bid> ansBidVector;
Bid tempBid;
priority_queue<Bid> tempBids;
int tempQuantity;

//基于优先级队列
void fun_1()
{
	int sumQuantity = 0;

	while ( !tempBids.empty() && sumQuantity < tempQuantity )
	{
		tempBid = tempBids.top();
		tempBids.pop();
		sumQuantity += tempBid.getQuantity();

		if ( sumQuantity <= tempQuantity ) {
			ansBidVector.push_back(tempBid);
		}
		else sumQuantity -= tempBid.getQuantity();
	}
}


const int MAXN = 1000 + 10;
double bag[MAXN];
int vis[MAXN][MAXN];
Bid t[MAXN];
//基于背包算法
void fun_2()
{
	int n = 1;
	memset(bag, 0, sizeof bag);
	memset(vis, -1, sizeof vis);

	while ( !tempBids.empty() )
	{
		tempBid = tempBids.top();
		tempBids.pop();
		int k = tempBid.getQuantity();
		for (int i = tempQuantity; i; i--){
			if ( i >= k && bag[i] < bag[i-k] + tempBid.getAmount() ){
				bag[i] = bag[i-k] + tempBid.getAmount();
				vis[n][i] = n;
			}
			else vis[n][i] = vis[n-1][i];
			//printf("(%d %d)%d  ", n, i, vis[n][i]);
		}
		cout<<endl;
		t[n++] = tempBid;
	}

	n--;
	while ( tempQuantity && ~vis[n][tempQuantity] )
	{
		tempBid = t[vis[n][tempQuantity]];
		n = vis[n][tempQuantity] - 1;
		tempQuantity -= tempBid.getQuantity();
		ansBidVector.insert(ansBidVector.begin(), tempBid);
	}
}
/*
5
110 4
100 2
70 1
60 1
*/

vector<Bid> Advertisement::getTopDutchBids (void) const
{
	ansBidVector.clear();
	tempBids = this->bids;
	tempQuantity = quantity;

	//基于优先级队列
	//fun_1();
	//基于背包算法
	fun_2();

	return ansBidVector;
}