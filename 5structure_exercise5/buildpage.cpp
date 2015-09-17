#include <sstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <signal.h>
#include <stdio.h>
#include <ctime>

#include "main.h"
#include "buildpage.h"
#include "Client.h"
#include "Advertisement.h"
#include "Listing.h"
#include "Group.h"

using namespace std;

void buildpage (ostringstream &oss, int port,  Listing::iterator start, 
                Listing::iterator finish) {

	in_addr ip;
	ip = getIP();

	displayPageHeader(oss);

	oss << "<TABLE width=100% cellpadding=3 cellspacing=3>" << endl;
	oss << "<TR>" << endl;
	oss << "<td width=50% class=advertisement>" << endl;
	displaySortFind(oss, ip, port);
	displayCategoryFilter(oss, ip, port);
 
	oss << "<table width=100%>" << endl;
	if (start == finish) {
		oss << "<tr><td><b>No items</b></td></tr>" << endl;  
	}
	else {
		for (Listing::iterator it = start; it != finish; it++) {
			oss << "<tr><td class=advertisement>" << endl;
			displayAdvertisement (oss, *it, ip, port);	   
			oss << "</td></tr>" << endl;
		}
	}
	oss << "</table>";
		  
	oss << "<td class=controlpanel>" << endl;
	displayControlPanel(oss, ip, port);
	oss << "</td></tr>" << endl;

	// Page Footer
	oss << "</TABLE>" << endl;
	oss << "</BODY>" << endl;
	oss << "</HTML>" << endl;

}

void displayPageHeader(ostringstream &oss) {

	// HTTP Content-type header
	oss << "Content-type: text/html" << "\r\n\r\n";

	// Start generating the page
	oss << "<HTML>" << endl;
	oss << "<HEAD>" << endl;
	oss << "<TITLE>" << endl;
	oss << "iCarnegie Auctions" << endl;
	oss << "</TITLE>" << endl;
	oss << "<link rel=\"stylesheet\" type=\"text/css\" href=\"/auction.css\" />" << endl;
	oss << "</HEAD>" << endl;
	oss << endl;
	oss << "<BODY>" << endl;
	oss << "<CENTER><H2>iCarnegie Auctions</H2></CENTER>" << endl;
}

void displayPostItem (ostringstream &oss, struct in_addr ip, int port) {

    oss << "<B><CENTER>" << "Post an Ad" << "</CENTER></B><BR>" << endl;

    oss << "<FORM ACTION=" << CLASSIFIED_CGI << " METHOD=POST>" << endl;
    oss << "<table border=0 width=100%>" << endl;
	oss << "<INPUT NAME=PORT TYPE=hidden VALUE=" << port << ">" << endl;
    oss << "<INPUT NAME=IP TYPE=hidden VALUE=" << inet_ntoa(ip) << ">" << endl;
    oss << "<INPUT NAME=email TYPE=hidden VALUE=" << active_user << ">" << endl;
    oss << "<tr><td align=right>Title:<td>" << endl;
	oss << "<INPUT NAME=title TYPE=text WIDTH=20 MAXWIDTH=20></tr>" << endl;

    oss << "<tr><td align=right>Category:<td>" << endl;
	oss << "<SELECT NAME=category>" << endl;
  
	for (Categories::iterator it = categories.begin();
       it != categories.end();
       it++) {
		oss << "<OPTION value=\"" << (*it)->getNumber() << "\">" 
			<< (*it)->getName() << "</OPTION>" << endl;
	}
	oss << "</SELECT></tr>" << endl;

	oss << "<tr><td align=right>Length:<td><SELECT NAME=days>" << endl;
	oss << "<OPTION value=3>3 days" << endl;
	oss << "<OPTION SELECTED value=5>5 days" << endl;
	oss << "<OPTION value=7>7 days" << endl;
	oss << "</SELECT></tr>" << endl;
	oss << "<tr><td align=right>Quantity:<td>" << endl;
	oss << "<INPUT NAME=quantity VALUE=1 TYPE=text SIZE=5 MAXLENGTH=4></tr>" << endl;
    oss << "<tr><td valign=top align=right>Description:<td>" << endl;
    oss << "<TEXTAREA NAME=body COLS=20 ROWS=4>" << endl;
    oss << "</TEXTAREA></tr>" << endl;
    oss << "<tr><td align=center colspan=2><INPUT NAME=COMMAND VALUE=Add TYPE=submit></tr>" << endl;
    oss << "</FORM></table>" << endl;
}

void displaySortFind (ostringstream &oss, struct in_addr ip, int port) {

    oss << "<FORM ACTION=" << CLASSIFIED_CGI << " METHOD=POST>" << endl;
    oss << "<INPUT NAME=PORT TYPE=hidden VALUE=" << port << ">" << endl;
	oss << "<INPUT NAME=IP TYPE=hidden VALUE=" << inet_ntoa(ip) << ">" << endl;
	oss << "<INPUT NAME=COMMAND VALUE=\"Sort\" TYPE=submit>" << endl;
	oss << "&nbsp;&nbsp;" << endl;
	oss << "<SELECT NAME=field>" << endl;
	oss << "<OPTION value=\"close\">By close date" << endl;
	oss << "<OPTION value=\"start\">By start date" << endl;
	oss << "<OPTION value=\"email\">By seller email" << endl;  
	oss << "<OPTION value=\"quantity\">By quantity" << endl;  
	oss << "<OPTION value=\"highest\">By highest Bid" << endl;  
	oss << "<OPTION value=\"lowest\">By lowest Bid" << endl;    
	oss << "</SELECT>" << endl;
	oss << "&nbsp;&nbsp;&nbsp;&nbsp;" << endl;
	oss << "<INPUT NAME=COMMAND VALUE=\"Find\" TYPE=submit>" << endl;
	oss << "&nbsp;&nbsp;" << endl;
	oss << "<INPUT NAME=keyword TYPE=text SIZE=15 MAXLENGTH=20>" << endl;
	oss << "</FORM>" << endl;
}

void displayCategoryAdd(ostringstream &oss, struct in_addr ip, int port) {

  oss << "<B><CENTER>" << "Add Sub-Category" << "</CENTER></B><BR>" << endl;
  oss << "<FORM ACTION=" << CLASSIFIED_CGI << " METHOD=POST>" << endl;
  oss << "<INPUT NAME=PORT TYPE=hidden VALUE=" << port << ">" << endl;
  oss << "<INPUT NAME=IP TYPE=hidden VALUE=" << inet_ntoa(ip) << ">" << endl;

  oss << "<table width=100%><tr><td align=right>Parent category:<td>" << endl;
  oss << "<SELECT NAME=parent>" << endl;

  for (Categories::iterator it = categories.begin();
       it != categories.end();
       it++) {
    oss << "<OPTION value=\"" << (*it)->getNumber() << "\">" 
		<< (*it)->getName() << "</OPTION>" << endl;
  }
  oss << "</SELECT></tr>" << endl;

  oss << "<tr><td align=right>New category:<td>" << endl;
  oss << "<INPUT NAME=newcategory TYPE=text></tr>" << endl;
  oss << "<tr><td colspan=2 align=center>" << endl;
  oss << "<INPUT NAME=COMMAND TYPE=submit VALUE=\"Add subcategory\">" << endl;
  oss << "</tr></table></FORM>" << endl;
}

void displayCategoryFilter(ostringstream &oss, struct in_addr ip, int port) {

	oss << "<FORM ACTION=" << CLASSIFIED_CGI << " METHOD=POST>" << endl;
	oss << "<INPUT NAME=PORT TYPE=hidden VALUE=" << port << ">" << endl;
	oss << "<INPUT NAME=IP TYPE=hidden VALUE=" << inet_ntoa(ip) << ">" << endl;
	oss << "Category: " << endl;
	oss << "<SELECT NAME=category>" << endl;
  
	for (Categories::iterator it = categories.begin();
       it != categories.end();
       it++) {
		oss << "<OPTION value=\"" << (*it)->getNumber() << "\">" 
			<< (*it)->getName() << "</OPTION>" << endl;
	}
	oss << "</SELECT>" << endl;

	oss << "<INPUT NAME=COMMAND VALUE=\"Top Only\" TYPE=submit>" << endl;
	oss << "<INPUT NAME=COMMAND VALUE=\"Recursive\" TYPE=submit>" << endl;
	oss << "</FORM>" << endl;
}

void displayRegister (ostringstream &oss, struct in_addr ip, int port) {

    oss << "<B><CENTER>Create Account</CENTER></B><BR>" << endl;
    if (!create_verified) {
      oss << "<FONT COLOR=red>Passwords didn't match.</FONT>" << endl;
      create_verified = true;
    }
	oss << "<table width=100%>" << endl;
    oss << "<FORM ACTION=" << CLASSIFIED_CGI << " METHOD=POST>" << endl;
    oss << "<INPUT NAME=PORT TYPE=hidden VALUE=" << port << ">" << endl;
    oss << "<INPUT NAME=IP TYPE=hidden VALUE=" << inet_ntoa(ip) << ">" << endl;
    oss << "<tr><td align=right>Email:<td><INPUT NAME=email TYPE=text SIZE=20 MAXLENGTH=30></tr>" 
        << endl;
    oss << "<tr><td align=right>Last name:<td><INPUT NAME=lname TYPE=text SIZE=20 MAXLENGTH=20></tr>" 
        << endl;
    oss << "<tr><td align=right>First name:<td><INPUT NAME=fname TYPE=text SIZE=20 MAXLENGTH=20></tr>" 
        << endl;
    oss << "<tr><td align=right>Password:<td><INPUT NAME=passwd TYPE=password SIZE=20 MAXLENGTH=60></tr>" << endl;
    oss << "<tr><td align=right>Password (again):<td><INPUT NAME=passwd2 TYPE=password SIZE=20 MAXLENGTH=60></tr>" << endl;
    oss << "<tr><td align=center colspan=2><INPUT NAME=COMMAND VALUE=\"Create\" TYPE=submit></tr>" << endl;
    oss << "</FORM>" << endl;
}

void displayControlPanel (ostringstream &oss, struct in_addr ip, int port) {

	// If someone is logged in
	if ("" != active_user) {

		displayLogout(oss, ip, port);
		oss << "<hr>" << endl;

		displayPostItem(oss, ip, port);
		oss << "<hr>" << endl;

		displayCategoryAdd(oss, ip, port);
	}
	else {

		displayLogin(oss, ip, port);
		oss << "<hr>" << endl;

		displayRegister(oss, ip, port);
	}
}

void displayLogout (ostringstream &oss, struct in_addr ip, int port) {

	oss << "<center>" << endl;
    oss << "Your userid: " << active_user << "&nbsp;&nbsp;&nbsp;" << endl;
    oss << "<FORM ACTION=" << CLASSIFIED_CGI << " METHOD=POST>" << endl;
    oss << "<INPUT NAME=PORT TYPE=hidden VALUE=" << port << ">" << endl;
    oss << "<INPUT NAME=IP TYPE=hidden VALUE=" << inet_ntoa(ip) << ">" << endl;
    oss << "<INPUT NAME=COMMAND VALUE=Logout TYPE=submit>" << endl;
    oss << "</FORM></center>" << endl;
}

void displayLogin (ostringstream &oss, struct in_addr ip, int port) {

	oss << "<center>" << endl;
    if (login_failed) {
      oss << "<b><FONT COLOR=red>Login failed.</FONT></b></br>" << endl;
      login_failed = false;
    }
	else {
      oss << "<b>Login</b></br>" << endl;
	}
	oss << "</center>" << endl;

    oss << "<table border=0 width=100%>" << endl;
    oss << "<FORM ACTION=" << CLASSIFIED_CGI << " METHOD=POST>" << endl;
    oss << "<INPUT NAME=PORT TYPE=hidden VALUE=" << port << ">" << endl;
    oss << "<INPUT NAME=IP TYPE=hidden VALUE=" << inet_ntoa(ip) << ">" << endl;
    oss << "<tr><td align=right>Email:" << endl;
	oss << "<td><INPUT NAME=email TYPE=text SIZE=12 MAXLENGTH=30></tr>" << endl; 
    oss << "<tr><td align=right>Password:" << endl;
	oss << "<td><INPUT NAME=passwd TYPE=password SIZE=12 MAXWLENGTH=10></tr>" << endl;
    oss << "<tr><td colspan=2 align=center>" << endl;
	oss << "<INPUT NAME=COMMAND VALUE=\"Login\" TYPE=submit>" << endl;
    oss << "</FORM></tr></table>" << endl;

}

void displayAdvertisement (ostringstream &oss, Advertisement* ad, struct in_addr ip, 
             int port) {

	Client* seller = NULL;
	seller = users[ad->getEmail()];

	oss << "<table border=0 width=100%><tr><td align=center width=15%>" << endl; 	
    if ("" != active_user) {
		displayBidButton(oss, ad, ip, port);
	}
	else {
		oss << "&nbsp;" << endl;
	}
	oss << "<td>" << endl;
	oss << "<B>" << ad->getTitle() << "</B><br>" << endl;
	oss << "Posted by: <A HREF=mailto:" << ad->getEmail() << ">";  
	oss << seller->getLname() << ", " << seller->getFname() << "</a><br>" << endl;
	oss << "Posted: " << ad->getStart() << "<br>" << endl;
	oss << "Closes: " << ad->getClose() << "<br>" << endl;
	oss << "Quantity: "	<< ad->getQuantity() << "<br>" << endl;
	oss << "Number of bids: " << ad->getBids().size() << "<br>" << endl;
	
	if (ad->getBids().size() > 0) {
		oss << "High bid: $" << ad->getBids().top().getAmount() << "<br>" << endl;
	}
	
	oss << ad->getBody() << endl;
    oss << "</tr></table>" << endl;
} 

void displayBidButton(ostringstream &oss, Advertisement* ad, struct in_addr ip, 
					  int port) {

	oss << "<FORM ACTION=" << CLASSIFIED_CGI << " METHOD=POST>" << endl;
	oss << "<INPUT NAME=PORT TYPE=hidden VALUE=" << port << ">" << endl;
	oss << "<INPUT NAME=IP TYPE=hidden VALUE=" << inet_ntoa(ip) << ">" << endl;
	oss << "<INPUT NAME=email TYPE=hidden VALUE=" << active_user << ">" << endl;
	oss << "<INPUT NAME=number VALUE=" << ad->getNumber() << " TYPE=hidden>" << endl;
	oss << "<INPUT NAME=COMMAND VALUE=Bid TYPE=submit></FORM>" << endl;
}

in_addr getIP(void) {

	// Find self for form parm
	char hostname_str[256];
	gethostname (hostname_str, 256);
	hostent *he = gethostbyname (hostname_str);
	in_addr ip;
	memcpy (&ip.s_addr, he->h_addr_list[0], sizeof(ip.s_addr));

	return ip;
}
