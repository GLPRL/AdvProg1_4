//
// Created by gp on 12/24/22.
//

#ifndef ADVPROG1_4_MAINDISTANCE_H
#define ADVPROG1_4_MAINDISTANCE_H
using namespace std;
map<string, int> getAllNames(vector <TypeVector> tv);
int validateAlg(string alg);
TypeVector aggregate(vector <string> vectorsString);
vector <TypeVector> readData(int &vsize, string filename);
string runMain(string alg, vector<TypeVector> tv, vector<double> v, int k, map<string, int> names, int vSize);
#endif //ADVPROG1_4_MAINDISTANCE_H
