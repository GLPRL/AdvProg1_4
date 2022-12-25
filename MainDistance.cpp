/**
 Receives two vectors from the user and calculates various types of distances between them.
**/

#include "Algorithms.h"
#include <algorithm>
#include "MainDistance.h"

/**
 * Getting all the names, disregarding duplicates.
 * @param tv TypeVector array to fetch names from.
 * @return a names vector.
**/
map<string, int> getAllNames(vector <TypeVector> tv) {
    map<string, int> names;
    for (int i = 0; i < tv.size(); i++) {
        names.insert(pair<string, int>(tv[i].getType(), 0));
    }
    return names;
}

/**
 * Checks if the alg of choosing is valid.
 * return 0 if not, otherwise 1.
 * @param alg algorithm of choosing
 * @return T/F if the input of algorithm of choosing is correct
**/
int validateAlg(string alg) {
    if (alg.compare("AUC") == 0) {
        return 1;
    }
    if (alg.compare("MAN") == 0) {
        return 1;
    }
    if (alg.compare("CHB") == 0) {
        return 1;
    }
    if (alg.compare("CAN") == 0) {
        return 1;
    }
    if (alg.compare("MIN") == 0) {
        return 1;
    }
    return 0;
}
/**
 * Data aggregation. Fetches the data of the vector according to placements. Everything ex. the last item in the vector
 * will be converted to double; the last parameter will be of type string, as it's the name of the item.
 * @param vectorsString Raw data, as fetched from CSV file
 * @param v User-inputted vector.
 * @param alg Our algorithm of calculation
 * @return a new TypeVector item, inserted into an array of this type.
**/
TypeVector aggregate(vector <string> vectorsString) {
    vector<double> vectors;
    for (int i = 0; i < vectorsString.size() - 1; i++) {                     //Inserts all the numbers into a new vector
        try {
            double p=stod(vectorsString[i]);
            vectors.push_back(p);
        }
        catch (...){
                perror("This excel file's vectors are not in accordance to instructions\n");
                exit(-1);
        }
    }                                                         //Item in last position in vectorsString will be the name
    string name = vectorsString[vectorsString.size() - 1];
    TypeVector tv = TypeVector(vectors, name);                             //Create the new TypeVector and calc.
    return tv;
}

/**
 * Open a CSV file here. We will build an instance of a named vector, contains: name, the actual vector and diff
 * We check for compliance in sizes and if the file was successfully opened.
 * @param alg Distance algorithms to use
 * @param k Amount of items to compare.
 * @param v Vector to compare with the CSV file.
**/
vector <TypeVector> readData(int &vsize, string filename) {
    fstream fin;
    string line, word;
                                                                  //we need to select the algorithm according to string.
    vector <TypeVector> typeVectors;
    vector <string> row;                                                //Name of type
    vector<double> vectors;                                            //Vector of type
    int excelVectorSize;
    int firstLine = 1;
    fin.open(filename, ios::in);
    if (fin.is_open()) {
        while (getline(fin, line)) {                             //Read from file and process.
            row.clear();                                                //Cleaning the row data before data is inserted
            stringstream str(line);
            while (getline(str, word, ',')) {              //Read single line from CSV file into string arr
                row.push_back(word);
            }
            if (firstLine) {                                            //if reading the first line of the file
                excelVectorSize = row.size() - 1;
                firstLine = 0;
            }
            TypeVector tVector = aggregate(row);        // Inserts the new TypeVector into an array.
            typeVectors.push_back(tVector);
        }
    } else {
        perror("No such file or directory\n");
        exit(-1);
    }
    fin.close();
    vsize=excelVectorSize;
    return typeVectors;
}

/**
 * Main function. We receive several command line arguments: 4 in total
 * First: some int K: number of neighbors. K is positive integer
 * Second: some file with suffix .csv , with data of the vectors.
 * We will read the data from each line, which will be a single flower.
 * Third: Our method of calculation. AUC, MAN, CHB, CAN, MIN for each of the algorithms.
 * @param alg algorithm to use
 * @param v vector of double values
 * @param k k - neighbors
 * @param filename filename to use for algorithm
 * @return code 0 if works as expected.
**/
string runMain(string alg, vector<TypeVector> tv, vector<double> v, int k, map<string, int> names) {
    int fileVectorSize = -1;
    //if(v.size()!=fileVectorSize){
    //    cout << "Your vector size does not match the excel file, try another vector"<<endl;
    //    return "";
    //} else
    int vectorSize = v.size();
    int size = tv.size();
    for (int i = 0; i < size; i++) {
        if (vectorSize != tv[i].getVector().size()) {
            return "invalid input";
        }
        tv[i].calculateDistance(v, alg);               //Calc. distance according to user
    }
    string result = knnAlgo(tv, k, names);       //Checking which vectors from csv are closest to user's vector.
    return result;
}