#include "knnServer.h"

/**
 * Function receives the in-buffer, returns vector of the data in buffer in orderly manner
 * @param buffer in-buffer
 * @return data of buffer in order
 */
vector<vector<char>> getVector(char buffer[]) {
    int size = 0;
    while (buffer[size] != '\n') {                             //get the actual size of buffer
        size++;
    }
    vector<vector<char>> stringVector;
    vector<char> tempv;
    for (int i = 0; i < size; i++) {                        //Create a vector of strings from buffer
        if (buffer[i] != ' ') {
            tempv.push_back(buffer[i]);
        } else {
            stringVector.push_back(tempv);                   //If whitespace, then ended a string & begin new one
            tempv.clear();                                  //purge old string
        }
    }
    return stringVector;
}
/**
 * Translates each string into double
 * @param size size of vector
 * @param vector string vector
 * @return double-precision vector
 */
vector<double> getNumberVector(int size, vector<vector<char>> vector) {
    ::vector<double> v;
    ::vector<double> vErr;
    for (int i = 0; i < size; i++) {
        try {
            string s(vector[i].begin(), vector[i].end());
            double num = stod(s);
            v.push_back(num);
        } catch (...) {
            cout << "Vector is of incorrect parameters, please enter a new one" << endl;
            return vErr;
        }
    }
    return v;
}
/**
 * Check if port is valid: If can be converted to int, and is in range 0-65535
 * @param port port to listen on
 * @return port number if exists, -1 otherwise.
 */
int getPort(string port) {
    int size = port.size();
    for (int i = 0; i < size; i++) {                                  //Iterate through the port characters and validate
        if (isdigit(port[i]) == false) {
            perror("Port must be an integer");
            return -1;
        }
    }
    int serverPort = stoi(port);
    if (serverPort > 65535) {
        return -1;
    }
    if (serverPort < 0) {
        return -1;
    }
    return serverPort;
}
/**
 * KNN Server.
 * @param argc count of command line args
 * @param argv command line args:
 * ARG[0] = server.out
 * ARG[1] = file to classify with
 * ARG[2] = port
 * Server receives data from client as STRING, and then divides according to whitespace the items
 * @return nothing
 */
int main(int argc, char *argv[]) {
    if (argc < 4) {
        cout << "Not enough arguments" << endl;
        return 1;
    }
    const int server_port = getPort(argv[2]);                                                     //Port validation
    if (server_port == -1) {
        cout << "No valid port entered. Exiting..." << endl;
        return 1;
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);                                    //Declaring socket
    if (sock < 0) {
        perror("Error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {                            //Bind socket
        perror("Error binding socket");
    }
    while (true) {                                                                       //Listen loop: for client input
        if (listen(sock, 5) < 0) {
            perror("Error listening to a socket");
        }
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);              //Accept new connection
        if (client_sock < 0) {
            perror("Error accepting client");
        }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);                   //Receive data
        if (buffer[0] == '-' && buffer[1] == '1') {                                 //buffer == "-1" -> close connection
            cout << "Closed" << endl;
            close(sock);
            return 0;
        }
        if (read_bytes == 0) {
            cout << "Closed" << endl;
        } else if (read_bytes < 0) {
            perror("Error reading from client");
        } else {
            cout << buffer;
        }
        vector<vector<char>> vector = getVector(buffer);
        int s = vector.size();
        ::vector<double> numVector = getNumberVector(s, vector);
        if (numVector.begin() == numVector.end()) {
            char outBufferErr[] = "invalid input";
            int sent_bytes = send(client_sock, outBufferErr, read_bytes, 0);
            continue;
        }
        string alg(vector[vector.size()-2].begin(), vector[vector.size()-2].end());
        string kString(vector[vector.size()-1].begin(), vector[vector.size()-1].end());
        int k = stod(kString);
        vector.pop_back();
        vector.pop_back();
        string fileName = argv[1];                                    //Get filename
        string result = runMain(alg, numVector, k, argv[1]);                             //Run KNN algorithm
        if (result.empty()) {
            continue;
        }
        int resSize = result.length();
        char outBuffer[4096];
        for (int i = 0; i < resSize; i++)
            outBuffer[i] = result[i];                           //Copy data into outBuffer
        int sent_bytes = send(client_sock, outBuffer, read_bytes, 0);
        if (sent_bytes < 0) {
            perror("error sending to client");
        }
    }
}