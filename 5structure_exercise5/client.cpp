#include "Client.h"

istream &operator>>(istream &stream, Client &c)
{
    string temp;
    stream>>temp;
    c.setFname(temp);
    stream>>temp;
    c.setLname(temp);
    stream>>temp;
    c.setEmail(temp);
    stream>>temp;
    c.setPasswd(temp);

	return stream;
}

Client::Client():fname(""),lname(""),email(""),passwd("")
{

}

Client::Client(Client const &c)
{
    fname = c.getFname();
    lname = c.getLname();
    email = c.getEmail();
    passwd = c.getPasswd();
}

Client::Client (string &fname, string &lname, string &email, string &passwd)
{
    this->fname = fname;
    this->lname = lname;
    this->email = email;
    this->passwd = passwd;
}

void Client::setFname(const string &fname)
{
    this->fname = fname;
}

void Client::setLname(const string &lname)
{
    this->lname = lname;
}

void Client::setEmail(const string &email)
{
    this->email = email;
}

void Client::setPasswd(const string &passwd)
{
    this->passwd = passwd;
}

string Client::getFname () const
{
    return fname;
}

string Client::getLname () const
{
    return lname;
}

string Client::getEmail () const
{
    return email;
}

string Client::getPasswd () const
{
    return passwd;
}

bool Client::verifyPasswd(string passwd)
{
    if ( passwd == this->passwd ) return true;
    else return false;
}
