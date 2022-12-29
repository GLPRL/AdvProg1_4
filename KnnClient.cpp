#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
using namespace std;
/**
 * reads input from the user in accordance to exrecise instructions.
 * returns 1 if success
 * returns 0 if input was -1
 * returns -1 if input was not good
 */
int readVector(string &distanceType, int &k,vector<double> &v,char c[] ) {
    string lin;
    getline(cin, lin);
    for(int i=0;i<lin.length();i++){
        c[i]=lin[i];
    }
    //c[lin.length()+1] = '\0';
    c[lin.length()] = '\0';
    if(lin.compare("-1")==0){
        return 0;
    }
    lin = ' ' + lin + " ";
    // If there is more than one space in a row, then return
    //and allow re-entry
    if (lin.find("  ") != string::npos) {
        // vector<double> ve;
        //return ve;
        return -1;
    }
    //vector<double> v;
    int pos = 0,y;
    double x;
    char *e;
    int wasDistance = 0;
    int wasVector = 0;
    int wasK = 0;

    lin.erase(0,1);

    // Loop until the end of the string each time separating the spaces.
    while ((pos = lin.find(" ")) != string::npos) {
        string sub = lin.substr(0, pos);
        if ((sub.compare("AUC") == 0)
            || (sub.compare("MAN") == 0)
            || (sub.compare("CHB") == 0)
            || (sub.compare("CAN") == 0)
            || (sub.compare("MIN") == 0)
                ) {
            if ( (wasVector == 1) && (wasK == 0) ) {
                wasDistance = 1;
                distanceType = sub;
            } else {
                return -1;
            }

        } else if (wasDistance==1)  {
            if (wasK == 1) {
                return -1;
            }
            y = stoi(sub);
            x = std::strtod(sub.c_str(), &e);
            k=y;
            if(k!=x){
                return -1;
            }
            wasK = 1;

        } else {
            x = std::strtod(sub.c_str(), &e);
            if (*e != '\0') {
                return -1;
            }
            wasVector = 1;
            v.push_back(x);
        }
        lin.erase(0, pos + 1);
    }
    //v.erase(v.begin());
    //if(wasDistance && readK) {
    if(wasDistance && wasK) {
        return 1;
    }
    return-1;
}
/**
 * Check if port is valid: If can be converted to int, and is in range 0-65535
 * @param port port to listen on
 * @return port number if exists, -1 otherwise.
 */
int getPort(string port) {
    int size = port.size();
    for (int i = 0; i < size; i++) {                  //Iterate through the port characters and validate they are digits
        if (isdigit(port[i]) == false) {
            return -1;
        }
    }
    int serverPort = stoi(port);                                                             //Convert string to int
    if (serverPort > 65535) {                                                             //Port in range of 65535 and 0
        return -1;
    }
    if (serverPort < 0) {
        return -1;
    }
    return serverPort;
}
/**
 * KNN client
 * @param argc command line args
 * @param argv arguments:
 * argv[0] = client.out
 * argv[1] = dest ip
 * argv[2] = dest port
 * @return
 */
int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("invalid input");
        return 1;
    }
    const char *ip_address = argv[1];                                                               //Options for socket
    const int port_no = getPort(argv[2]);
    if (port_no == -1) {                                                                                    //Error port
        perror("invalid input");
        return 1;
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        return 1;
    }
    struct sockaddr_in sin;                                                                               //setup socket
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {                   //Connected to server
        perror("Error connecting to server");
    }
    while (true) {                                                                                      //Send data loop
        char data_addr[2048];
        memset(&data_addr, 0, sizeof(data_addr));                                           //Purge send buffer
        string s;
        int p;
        vector<double> v;
        int result = readVector( s, p, v,data_addr);
        if (result == -1) {                                                                           //Is invalid input
            cout << "invalid input" << endl;
           continue;
        }
        int data_len = strlen(data_addr);
        int sent_bytes = send(sock, data_addr, data_len, 0);                             //Sending data
        if (sent_bytes < 0) {
            perror("Error sending data to server\n");
            return 1;
        }
        char buffer[2048];                                                       //Clearing space for answer from server
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);                 //Receive from server
        if (read_bytes < 0) {                                                                                 //If error
            perror("Error reading data from server");
        } else if(read_bytes!=0) {
            cout << buffer << endl;                                                                       //Print result
        }

        if(result==0){                                                                               // if -1 then close
            close(sock);
            exit(0);
        }
        memset(&buffer, 0, sizeof(buffer));                                       //Purge past data from buffer
        continue;
    }
}