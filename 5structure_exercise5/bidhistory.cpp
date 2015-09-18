#include "bidhistory.h"
#include "main.h"

void showBid(ostringstream &oss, Bid bid)
{
	oss << "Bid: $" << bid.getAmount() << "  Posted By: " << bid.getEmail() << "<br>" << endl;
}

void displayBidHistory(ostringstream &oss, Advertisement* ad)
{
	Client* seller = NULL;
	seller = users[ad->getEmail()];
	vector<Bid> bids = ad->getTopDutchBids();

	//show advertisment
	oss << "<table border=0 width=100%><tr><td align=center width=15%>" << endl; 	
	oss << "<td>" << endl;
	oss << "<B>" << ad->getTitle() << "</B><br>" << endl;
	oss << "Posted by: <A HREF=mailto:" << ad->getEmail() << ">";
	oss << seller->getLname() << ", " << seller->getFname() << "</a><br>" << endl;
	oss << "Posted: " << ad->getStart() << "<br>" << endl;
	oss << "Closes: " << ad->getClose() << "<br>" << endl;
	oss << "Quantity: "	<< ad->getQuantity() << "<br>" << endl;
	oss << "Number of bids: " << ad->getBids().size() << "<br>" << endl;
	
	//show bids
	int sumQuantity = ad->getQuantity();
	for (vector<Bid>::iterator it = bids.begin(); it != bids.end(); it++){
		showBid(oss, *it);
		sumQuantity -= (*it).getQuantity();
	}
	oss << "The quantity left: " << sumQuantity << "<br>" <<endl;

	oss << "</tr></table>" << endl;
} 