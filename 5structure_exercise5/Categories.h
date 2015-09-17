#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <string>
#include <vector>

#include "Category.h"
#include "Listing.h"

using namespace std;

class Categories {

  protected:
	typedef vector<Category*> Container;

  public:
	typedef Container::iterator iterator;

  protected:
	Container objects;

  public:
	static const int TOP_LEVEL;
	static const int NO_PARENT;
    
	virtual Category* operator[](const int& number);
	virtual void add(Category* ptr);

	virtual iterator begin();
	virtual iterator end();

};


#endif
