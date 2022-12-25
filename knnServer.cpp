#include "knnServer.h"
#include "MainDistance.h"
void extract(char c[],int &k,string &distanceType,vector<double> &v){
    string s (c);
    char *e;
    int pos=0;
    int wasDistance = 0;
    double x;
    s = ' ' + s + " ";
    while ((pos = s.find(" ")) != string::npos) {
        string sub = s.substr(0, pos);
        if ((sub.compare("AUC") == 0)
            || (sub.compare("MAN") == 0)
            || (sub.compare("CHB") == 0)
            || (sub.compare("CAN") == 0)
            || (sub.compare("MIN") == 0)
                ) {
            wasDistance = 1;
            distanceType = sub;

        } else if(wasDistance) {
            k = stoi(sub);

        } else {
            x = std::strtod(sub.c_str(), &e);
            v.push_back(x);
        }
        s.erase(0, pos + 1);
    }
    v.erase(v.begin());
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
            perror("Port must be an integer\n");
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
    if (argc < 3) {
        perror("Not enough arguments\n");
        return 1;
    }
    const int server_port = getPort(argv[2]);                                                     //Port validation
    if (server_port == -1) {
        perror("No valid port entered. Exiting\n");
        return 1;
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);                                    //Declaring socket
    if (sock < 0) {
        perror("Error creating socket\n");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {                            //Bind socket
        perror("Error binding socket");
    }
    int vSize = -1;
    string fileName = argv[1];
    vector<TypeVector> v = readData(vSize, fileName);
    map<string, int> names = getAllNames(v);
    if (listen(sock, 5) < 0) {
        perror("Error listening to a socket");
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);     //Accept new connection
    if (client_sock < 0) {
        perror("Error accepting client");
    }
    while (true) {                                                                       //Listen loop: for client input
        char buffer[2048];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);                //Receive data
        vector<double> numVector;
        int k;
        string distanceType;
        extract(buffer,k,distanceType,numVector);
        cout<<"------"<<endl;
        cout<<k<<endl;
        cout<<distanceType<<endl;
        for(int i=0;i<numVector.size();i++){
            cout<<numVector[i]<<endl;
        }
        //vector<vector<char>> vector = getVector(buffer);           //TODO: get data from vector
        //int s = vector.size();
        //while(numVector[0] != -1 && numVector.size() == 1)
        while(numVector[0] != -1 || numVector.size() != 1){          //Read continuous data from client and send back
            if (numVector.size() == 0) {
                char outBufferErr[] = "invalid input";
                int sent_bytes = send(client_sock, outBufferErr, read_bytes, 0);
                if (sent_bytes < 0) {
                    perror("error sending to client\n");
                }
                continue;
            }
            int k = 3;          //TODO: how to get k
            //string alg(vector[vector.size() - 1].begin(), vector[vector.size() - 1].end());
            string alg = "MIN";
            string result = runMain(alg, v, numVector, k, names);
            if (result.empty()) {
                continue;
            }
            int resSize = result.length();
            read_bytes = resSize;
            char outBuffer[2048];
            for (int i = 0; i < resSize; i++)
                outBuffer[i] = result[i];
            expected_data_len = sizeof(buffer);
            int sent_bytes = send(client_sock, outBuffer, read_bytes, 0);
            if (sent_bytes < 0) {
                perror("error sending to client\n");
            }
            memset(&result, 0, sizeof(result));
            memset(&buffer, 0, 2048);                                                             //Purge buffer
            expected_data_len = sizeof(buffer);
            read_bytes = recv(client_sock, buffer, expected_data_len, 0);                //Receive data
            //vector = getVector(buffer);
            //s = vector.size();
            numVector = {-1, 2};
            numVector.shrink_to_fit();
            //::vector<double> numVector = getNumberVector(s, vector); TODO: getNumVector function
        }
        if (read_bytes == 0) {
            cout << "Closed" << endl;                                       //TODO: close connection
        } else if (read_bytes < 0) {
            perror("Error reading from client\n");
        }
        close(client_sock);
        if (listen(sock, 5) < 0) {
            perror("Error listening to a socket");
        }
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);     //Accept new connection
        if (client_sock < 0) {
            perror("Error accepting client");
        }

        //return 0;
    }
}