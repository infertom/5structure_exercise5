#ifndef LISTING_H
#define LISTING_H

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

#include "Advertisement.h"

using namespace std;

class Listing;

class Listing {

protected:
	typedef vector<Advertisement*> Container;

public:
	typedef Container::iterator iterator;

protected:
	Container objects;

public:
	virtual Advertisement* operator[](const int& number);

	virtual void add(Advertisement* ptr);

	virtual iterator begin();
	virtual iterator end();

	// return a sorted copy of this Listing
	virtual Listing sort(string field);

	// return a filtered by keyword copy of this Listing
	virtual Listing filter(string keyword);
};

#endif
