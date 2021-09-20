//
//  client.cpp
//  ChatApp
//
//  Created by Ryan Shim on 2021-09-16.
//

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
using namespace std;
//Client side
void listen_for_server(int clientSd) {
    while (1) {
        //std::cout << "listened called" << std::endl;
        string msg;
        char buffer[1025];
        memset(&buffer, 0, sizeof(buffer));
        recv(clientSd, (char*)&buffer, sizeof(buffer), 0);
        
        std::cout << buffer << " threaded." << std::endl;
    }
}

void send_to_server(int clientSd) {
    while(1) {
        //std::cout << "sent called first" << std::endl;
        char buffer[1025];
        memset(&buffer, 0, sizeof(buffer));
        string data;
        getline(cin, data);
        strcpy(buffer, data.c_str());
        send(clientSd, (char*)&buffer, sizeof(buffer), 0);
        //std::cout << "sent called second" << std::endl;
    }
    
}
int main(int argc, char *argv[])
{
    //we need 2 things: ip address and port number, in that order
    if(argc != 3)
    {
        cerr << "Usage: ip_address port" << endl; exit(0);
    } //grab the IP address and port number
    char *serverIp = argv[1]; int port = atoi(argv[2]);
    //create a message buffer
    char msg[1500];
    //setup a socket and connection tools
    struct hostent* host = gethostbyname(serverIp);
    sockaddr_in sendSockAddr;
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr =
        inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    //try to connect...
    
    string clientDisplayName;
    getline(cin, clientDisplayName);
    int status = connect(clientSd,
                         (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
    if(status < 0)
    {
        cout<<"Error connecting to socket!"<<endl;
    }
    cout << "Connected to the server!" << endl;
    int bytesRead = 0;
    int bytesWritten = 0;
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    while(1)
    {
        std::thread t1(listen_for_server, clientSd);
        std::thread t2(send_to_server, clientSd);
        cout << ">";
        string data;
        //getline(cin, data);
        //memset(&msg, 0, sizeof(msg));//clear the buffer
        //strcpy(msg, data.c_str());
        if(data == "exit")
        {
            send(clientSd, (char*)&msg, strlen(msg), 0);
            break;
        }
        
        cout << "Awaiting server response..." << endl;
        //string fullMsg = clientDisplayName + ": " + data;
        //memset(&msg, 0, sizeof(msg));//clear the buffer
        //strcpy(msg, fullMsg.c_str());
        //bytesWritten += send(clientSd, (char*)&data, data.length(), 0);
       // memset(&msg, 0, sizeof(msg));
        //bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
        //cout << bytesRead << endl;
        
        if(!strcmp(msg, "exit"))
        {
            cout << "Server has quit the session" << endl;
            break;
        }
        //cout << "Server: " << msg << endl;
        t1.join();
        t2.join();
        
    }
    gettimeofday(&end1, NULL);
    close(clientSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten <<
    " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec- start1.tv_sec)
      << " secs" << endl;
    cout << "Connection closed" << endl;
    return 0;
}
