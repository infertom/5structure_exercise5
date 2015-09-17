#include "Categories.h"

Category* Categories::operator[](const int &number)
{
	for ( iterator it = objects.begin(); it != objects.end(); it++){
		if ( (*it)->getNumber() == number ) return *it;
	}
	return NULL;
}

void Categories::add(Category* ptr)
{
    objects.push_back(ptr);
}

Categories::iterator Categories::begin()
{
    return objects.begin();
}

Categories::iterator Categories::end()
{
    return objects.end();
}
