#ifndef BUILDPAGE_H
#define BUILDPAGE_H

#include <sstream>
#include "Listing.h"

using namespace std;

in_addr getIP(void);
void displayPageHeader(ostringstream &oss);

void displaySortFind (ostringstream &oss, struct in_addr ip, int port);
void displayCategoryFilter(ostringstream &oss, struct in_addr ip, int port);
void displayPostItem (ostringstream &oss, struct in_addr ip, int port);
void displayRegister (ostringstream &oss, struct in_addr ip, int port);
void displayLogin (ostringstream &oss, struct in_addr ip, int port);
void displayLogout (ostringstream &oss, struct in_addr ip, int port);
void displayControlPanel (ostringstream &oss, struct in_addr ip, int port);
void displayAdvertisement (ostringstream &oss, Advertisement* ad, struct in_addr ip, 
             int port);
void displayBidButton(ostringstream &oss, Advertisement* ad, struct in_addr ip, 
					  int port);

void buildpage (ostringstream &oss, int port, Listing::iterator start,
                Listing::iterator finish);

#define CLASSIFIED_CGI "classified.cgi"

#endif
