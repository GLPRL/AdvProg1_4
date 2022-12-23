/**
 Receives two vectors from the user and calculates various types of distances between them.
**/

#include "Algorithms.h"
#include <algorithm>

/**
 * Checks for name duplications.
 * @param name string to compare duplication with
 * @param tv comparing with TypeVector's types attribute
 * @return status if duplicate. 0 if is duplicate, 1 otherwise.
**/
using namespace std;

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
 * Reads a vector from the user in accordance to the ex1 instructions.
 * Prints an error if the input is not as expected.
**/
vector<double> readVector() {
    string lin;
    getline(cin, lin);
    lin = ' ' + lin + " ";
                                                     // If there is more than one space in a row, then return
                                                     //and allow re-entry
    if (lin.find("  ") != string::npos) {
        vector<double> ve;
        return ve;
    }
    vector<double> v;
    int pos = 0;
    double x;
    char *e;
                                                    // Loop until the end of the string each time separating the spaces.
    while ((pos = lin.find(" ")) != string::npos) {
        string sub = lin.substr(0, pos);
        x = std::strtod(sub.c_str(), &e);
        if (*e != '\0') {
            cout << "Error:" << sub.c_str() << " is not a number" << endl;; //if cannot be converted,
            vector <double> verr;                                           // then allow re-entry
            return verr;
        }
        v.push_back(x);
        lin.erase(0, pos + 1);
    }
    v.erase(v.begin());
    return v;
}

/**
 * Data aggregation. Fetches the data of the vector according to placements. Everything ex. the last item in the vector
 * will be converted to double; the last parameter will be of type string, as it's the name of the item.
 * @param vectorsString Raw data, as fetched from CSV file
 * @param v User-inputted vector.
 * @param alg Our algorithm of calculation
 * @return a new TypeVector item, inserted into an array of this type.
**/
TypeVector aggregate(vector <string> vectorsString, string alg) {
    vector<double> vectors;
    for (int i = 0;
         i < vectorsString.size() - 1; i++) {                 //Inserts all the numbers into a new vector of type double
        try {
            double p=stod(vectorsString[i]);
            vectors.push_back(p);
        }
        catch (...){
                cout << "This excel file's vectors are not in accordance to instructions" << endl;
                exit(-1);
        }
    }                                                         //Item in last position in vectorsString will be the name!
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
vector <TypeVector> readData(string alg, int &vsize, string filename) {
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
            TypeVector tVector = aggregate(row, alg);        // Inserts the new TypeVector into an array.
            typeVectors.push_back(tVector);
        }
    } else {
        perror("No such file or directory");
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
 * @return code 0 if works as expected.
**/
int main(int argc, char *argv[]) {
    if (argc != 4) {                                                //If we don't have enough cmd line args
        perror("Not enough command line arguments.");
        return -1;
    }
    if (validateAlg(argv[3]) != 1) {                            //Validation of correct user input for algorithm
        perror("Invalid algorithm name input.");
        return -1;
    }
    for (int i = 0; i < strlen(argv[1]); i++) {                     //Validation that K is an int
        if (isdigit(argv[1][i]) == false) {
            perror("Second parameter must be an integer.");
            return -1;
        }
    }
    int k = stoi(argv[1]);
    int fileVectorSize=-1;
    vector <TypeVector> tv = readData(argv[3], fileVectorSize, argv[2]);
    map<string, int> names = getAllNames(tv);
    while (true) {
        vector<double> v = readVector();                          //Reading input vector data
        if(v.size()!=fileVectorSize){
            cout<<"Your vector size does not match the excel file, try another vector"<<endl;
            continue;
        } else
        if(v.size() == 0) {
            cout << "Too many whitespaces, try another vector" << endl;
            continue;
        }
        for(int i=0;i<tv.size();i++){
            tv[i].calculateDistance(v,argv[3]);      //calculate distance for each vector in the file
        }
        cout << knnAlgo(tv, k, names) << endl; //Checking which vectors from csv are closest to user's vector.
    }
}