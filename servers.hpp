//
//  servers.hpp
//  ChatApp
//
//  Created by Ryan Shim on 2021-09-19.
//

#ifndef servers_hpp
#define servers_hpp

#include <stdio.h>
#include <iostream>
#include <thread>
#include <string>
#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
     
#define TRUE   1
#define FALSE  0
#define PORT 8888

class Server {
public:
    int start_server();
};

#endif /* servers_hpp */
