//
//  clients.cpp
//  ChatApp
//
//  Created by Ryan Shim on 2021-09-20.
//


#include "clients.hpp"

using namespace std;
//Client side
void listen_for_server(int clientSd) {
    while (1) {
        //std::cout << "listened called" << std::endl;
        string msg;
        char buffer[1025];
        memset(&buffer, 0, sizeof(buffer));
        recv(clientSd, (char*)&buffer, sizeof(buffer), 0);
        
        std::cout << buffer << std::endl;
    }
}

void send_to_server(int clientSd, std::string clientName) {
    while(1) {
        //std::cout << "sent called first" << std::endl;
        char buffer[1025];
        memset(&buffer, 0, sizeof(buffer));
        string data;
        cout << ">";
        getline(cin, data);
        data = clientName + ": " + data;
        strcpy(buffer, data.c_str());
        send(clientSd, (char*)&buffer, sizeof(buffer), 0);
        //std::cout << "sent called second" << std::endl;
    }
    
}

Client::Client(std::string name, int port) {
    this->clientName = name;
    this->port = port;
}
int Client::start_client()
{
    char const *serverIp = "127.0.0.1";
    char msg[1500];
    //setup a socket and connection tools
    struct hostent* host = gethostbyname(serverIp);
    sockaddr_in sendSockAddr;
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr =
        inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(this->port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    //try to connect...
    
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
        std::thread t2(send_to_server, clientSd, this->clientName);
                //cout << "Awaiting server response..." << endl;
        
        if(!strcmp(msg, "exit"))
        {
            cout << "Server has quit the session" << endl;
            break;
        }
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
