#include <sstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <signal.h>
#include <cstdio>

#include "main.h"
#include "buildpage.h"
#include "buildbidpage.h"
#include "bidhistory.h"
#include "Client.h"
#include "Advertisement.h"
#include "Listing.h"
#include "Group.h"

using namespace std;

void buildbidpage (ostringstream &oss, int port, int number) {

	in_addr ip;
	ip = getIP();

	displayPageHeader(oss);

	Advertisement *ad = NULL;
	ad = advertisements[number];
   
	oss << "<table border=0 width=100%>" << endl;
	oss << "<tr><td valign=top width=50%>" << endl;
	oss << "<b>" << ad->getTitle() << "</b><br>" << endl;
	displayBidHistory(oss, ad);

	oss << "<td valign=top>" << endl;
	displayBidForm(oss, ip, port, number);
	oss << "</tr></table>" << endl;
 
	oss << "</body>" << endl;
	oss << "</html>" << endl;
}

void displayBidForm(ostringstream &oss, struct in_addr ip, int port, int number) {

	Advertisement *ad = NULL;
	ad = advertisements[number];

	oss << "<FORM ACTION=" << CLASSIFIED_CGI << " METHOD=POST>" << endl;
	oss << "<INPUT NAME=PORT TYPE=hidden VALUE=" << port << ">" << endl;
	oss << "<INPUT NAME=IP TYPE=hidden VALUE=" << inet_ntoa(ip) << ">" << endl;
	oss << "<INPUT NAME=email TYPE=hidden VALUE=" << active_user << ">" << endl;
	oss << "<INPUT NAME=number TYPE=hidden VALUE=" << number << ">" << endl;

	oss << "<b><center>Place Bid</center></b><br>" << endl;
	oss << "<table border=0 width=100%>" << endl;
	oss << "<tr><td align=right>Bid amount:" << endl;

	float high_bid = 0;
	if (ad->getBids().size() > 0) {
		high_bid = ad->getBids().top().getAmount();
	}
	oss << "<td><INPUT NAME=amount TYPE=text SIZE=5 VALUE="
		<< high_bid + 1 << "></tr>" << endl;
 
	oss << "<tr><td align=right>Quantity:" << endl;
	if  (ad->getQuantity() > 1) {
		oss << "<td><INPUT NAME=quantity SIZE=5 TYPE=text VALUE=1></tr>" << endl;
	}
	else {
		oss << "<td><INPUT NAME=quantity TYPE=hidden VALUE=1>1</tr>" << endl;
	}

	oss << "<tr><td align=center colspan=2>" << endl;
	oss << "<INPUT NAME=COMMAND TYPE=submit VALUE=\"Submit bid\">" << endl;
	oss << "</FORM>" << "</tr></table>" << endl;
}
