//
//  clients.hpp
//  ChatApp
//
//  Created by Ryan Shim on 2021-09-20.
//

#ifndef clients_hpp
#define clients_hpp

#include <stdio.h>
#include <iostream>
#include <thread>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>



class Client {
    std::string clientName;
    int port;
    //void listen_for_server(int clientSd);
    //void send_to_server(int clientSd);
    
    public:
    Client(std::string name, int port);
    int start_client();
    
};

#endif /* clients_hpp */
