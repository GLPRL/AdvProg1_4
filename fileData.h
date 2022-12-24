
#ifndef ADVPROG1_4_FILEDATA_H
#define ADVPROG1_4_FILEDATA_H
using namespace std;
#include "TypeVector.h"
#include "TypeVector.h"
class fileData {
    vector<TypeVector> v;
    int size;
public:
    vector<TypeVector> readData(int& vsize, string filename);
    void calculateDistance(vector<TypeVector> v, string alg);
    vector<TypeVector> getTypeVector();
};
#endif //ADVPROG1_4_FILEDATA_H
