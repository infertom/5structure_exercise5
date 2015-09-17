#include <winsock2.h>
#include <ws2tcpip.h>
#include <signal.h>
#include <cstdio>

#include <string>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <sstream>

#include "Listing.h"
#include "Group.h"
#include "Categories.h"
#include "processrequest.h"
#include "main.h"

using namespace std;

Categories categories;
Listing advertisements;
Group users;

int category_counter = 0;
int advertisement_counter = 0;

string active_user = "";
bool create_verified = true;
bool login_failed = false;


/*
 * Not this is explicitly not concurrent -- the auction data structures
 * are not necessarily concurrency safe
 */

int main (int argc, char *argv[]) {

	

  /*
   * argv[1] should be the port number
   */
  if (2 != argc) {
    cout << "Usage: " << argv[0] << " [port]" << endl << endl;
    return -1;
  }

  int port = atoi(argv[1]);


    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
 
    wVersionRequested = MAKEWORD( 2, 2 );
 
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        return 0;
    }



  /*
   * Create and configure the socket
   */
  int connfd = -1;
  int listenfd = -1; 
  
  struct sockaddr_in cliaddr;
  struct sockaddr_in servaddr;
  int clilen = sizeof (cliaddr);

  listenfd = socket (AF_INET, SOCK_STREAM, 0); 

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
  servaddr.sin_port = htons(port);


  /*
   * Bind to the socket
   */
  ::bind (listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));


  /*
   * Configure the listen queue
   */
  listen (listenfd, BACKLOG);
  
  /*
   * Main work loop:
   * Listen for connection, accept it, process request, print html page
   */

  Category top_level(Categories::NO_PARENT, "Top Level");
  top_level.setNumber(category_counter);
  category_counter++;
  
  categories.add(new Category(top_level));

  
  while (true) {

    // Wait for the knock at the door
    if (0 > (connfd = accept (listenfd, 
                              (struct sockaddr *) &cliaddr, &clilen)) ) {

     if (errno == EINTR)
        continue;
     else {
        cerr << "unknown error: " << errno << " " << connfd << endl;
        exit(-1); // Who knows? Bad foo. Maybe continue for roubustness?
        
        }

    }

    // Process the request
    char req_buffer[REQ_MAX];
    int count;


 
    for (count=0; count<REQ_MAX; count++) {
      int retval = recv (connfd, req_buffer+count, 1, 0);

	  if (4 == req_buffer[count]) { // 4 is EOT, a.ka. CTRL-D 
        req_buffer[count] = '\0';
        break;
      }
    }

  
    // Move request to stream for C++ style processing
    ostringstream oss;
    oss.str("");
    oss << req_buffer;
    memset (req_buffer, 0, REQ_MAX);

    cerr << oss.str() << endl;

    istringstream iss (oss.str());

    processrequest (iss, connfd, port);
    
    // Done with this request
    closesocket (connfd);
    connfd = -1;
  }

}
