#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

#include "Client.h"

using namespace std;

class Group;

class Group {

protected:
	typedef vector<Client*> Container;

public:
	typedef Container::iterator iterator;

protected:
	Container objects;

public:
    Client *operator[](const string& email);

	virtual void add(Client* ptr);

	virtual iterator begin();
	virtual iterator end();

};

#endif
