//
//  clientMain.cpp
//  ChatApp
//
//  Created by Ryan Shim on 2021-09-20.
//

#include "clients.hpp"

int main() {
    std::string name;
    std::cout << "What is your name? ";
    getline(std::cin, name);
    Client mainClient(name, 8888);
    mainClient.start_client();
}
