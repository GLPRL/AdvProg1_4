//
// Created by Dekel on 13/11/2022.
//

#ifndef ADVPROG1_2_ALGORITHMS_H
#define ADVPROG1_2_ALGORITHMS_H
using namespace std;
#include <vector>
#include "cmath"
#include "iostream"
#include "stdlib.h"
#include <string.h>
#include <ios>
#include <fstream>
#include <sstream>
#include "TypeVector.h"
#include <algorithm>
#include <map>
string knnAlgo(vector<TypeVector> vectorArray, int k, map<string, int> names);
double minkowski(vector<double> v1, vector<double> v2);
double canberra(vector<double> v1, vector<double> v2);
double euclidean(vector<double> v1, vector<double> v2);
double chebyshev(vector<double> v1, vector<double> v2);
double manhattan(vector<double> v1, vector<double> v2);
#endif //ADVPROG1_2_ALGORITHMS_H
