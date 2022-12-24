/**
 * knnServer header file
 */
#ifndef ADVPROG1_4_KNNSERVER_H
#define ADVPROG1_4_KNNSERVER_H
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include "Algorithms.h"
string runMain(string alg, vector<double> v, int k, string filename);
using namespace std;
#endif //ADVPROG1_4_KNNSERVER_H
