#ifndef PROCESS_REQUEST_H
#define PROCESS_REQUEST_H

#include <sstream>
#include "buildpage.h"
#include "buildbidpage.h"

using namespace std;

void processrequest(istringstream &iss, int connfd, int port);

#endif
