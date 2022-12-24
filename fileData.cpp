//
// Created by gp on 12/24/22.
//

#include "fileData.h"
#include "Algorithms.h"
#include "MainDistance.h"

vector<TypeVector> fileData::readData(int &vsize, string filename) {
    fstream fin;
    string line, word;
    //we need to select the algorithm according to string.
    vector<TypeVector> typeVectors;
    vector<string> row;                                                //Name of type
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
        perror("No such file or directory");
        exit(-1);
    }
    fin.close();
    vsize = excelVectorSize;
    return typeVectors;
}
/**
 * Getter for the TypeVector
 * @return  TypeVector vector
 */
vector<TypeVector> fileData::getTypeVector() {
    return vector<TypeVector>();
}
