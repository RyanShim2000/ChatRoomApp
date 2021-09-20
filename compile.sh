#!/bin/bash
g++ -std=c++11 -pthread servers.cpp serverMain.cpp -o servers
g++ -std=c++11 -pthread clients.cpp clientMain.cpp -o clients
