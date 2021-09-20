#!/bin/bash
g++ -std=c++11 servers.cpp -pthread -o servers
g++ -std=c++11 client.cpp -o client
