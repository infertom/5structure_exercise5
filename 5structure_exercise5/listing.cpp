#include "Listing.h"

Advertisement * Listing::operator[](const int &number)
{
	iterator it = objects.begin() + number;
	return *it;
}

void Listing::add(Advertisement* ptr)
{
	objects.push_back(ptr);
}

Listing::iterator Listing::begin()
{
	return objects.begin();
}

Listing::iterator Listing::end()
{
	return objects.end();
}

/************************************************************************/
/* copy listing                                                                     */
/************************************************************************/

Listing * tempListing;
void copyFun(Advertisement * a)
{
	tempListing->add(a);
}

void mCopy(Listing * a)
{
	tempListing = new Listing();
	for_each(a->begin(), a->end(), copyFun);
}

/************************************************************************/
/* sort listing                                                                     */
/************************************************************************/

string tempField;
bool mCmp(const Advertisement * a, const Advertisement * b)
{
	if ( tempField == "email" ){
		return ( a->getEmail() < b->getEmail() );
	}
	if ( tempField == "start" ){
		return ( a->getStart() < b->getStart() );
	}
	if ( tempField == "close" ){
		return ( a->getClose() < b->getClose() );
	}
	if ( tempField == "quantity" ){
		return ( a->getQuantity() < b->getQuantity() );
	}
}

// return a sorted copy of this Listing
Listing Listing::sort(string field)
{
//	tempListing = new Listing();
//	for_each(objects.begin(), objects.end(), copyFun);
	
	tempField = field;
	mCopy(this);
	std::sort(tempListing->begin(), tempListing->end(), mCmp);
	
	return (*tempListing);
	

	/*
	std::sort(this->begin(), this->end(), mCmp);

	return (*this);
	*/
}





/************************************************************************/
/* find keyword                                                                     */
/************************************************************************/
string tempKey;
void findKeyFun(Advertisement * a)
{
	string body = a->getBody();
	string name = a->getTitle();
	if ( !(body.find(tempKey, 0) == string::npos && name.find(tempKey, 0) == string ::npos) ){
		tempListing->add(a);
	}
}

// return a filtered by keyword copy of this Listing
Listing Listing::filter(string keyword)
{
// 	tempListing = new Listing();
// 	for_each(objects.begin(), objects.end(), copyFun);
//	mCopy(this);
	tempKey = keyword;
	tempListing = new Listing();
	for_each(this->begin(), this->end(), findKeyFun);

	return (*tempListing);
	
}