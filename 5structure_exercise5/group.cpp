#include "Group.h"

Client * Group::operator[](const string &email)
{
	for (iterator it = objects.begin(); it != objects.end(); it++){
		if ( (*it)->getEmail() == email ) return *it;
	}
}

void Group::add(Client* ptr)
{
	objects.push_back(ptr);
}

Group::iterator Group::begin()
{
	return objects.begin();
}

Group::iterator Group::end()
{
	return objects.end();
}