#ifndef BUILDBIDPAGE_H
#define BUILDBIDPAGE_H

#include <sstream>

using namespace std;

void buildbidpage (ostringstream &oss, int port, int number);
void displayBidForm(ostringstream &oss, struct in_addr ip, int port, int number);

#define CLASSIFIED_CGI "classified.cgi"

#endif
