/**
* Knn server.
 * Port = 50000
 * IP = localhost
*/
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
using namespace std;
int main() {
    const int server_port = 50000;                                                                   //create new socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror ("Error binding socket");
    }
    if (listen(sock, 5) < 0) {                                                                                  //listen
        perror ("Error listening on socket");
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);                  //accept new connection
    if (client_sock < 0) {
        perror ("Error accepting client");
    }
    char buffer[2048];
    int expected_data_len = sizeof(buffer);
    while (true) {                                                              //infinite read data from the connection
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        if (read_bytes < 0) {
            perror("Error reading data");
        } else {                                                 //if no error reading data, then initiate knn algorithm
            cout << buffer << endl;
            //TODO: CALCULATIONS
            //string data = ???
        }
        int sent_bytes = send(client_sock, "2", read_bytes, 0);
        if (sent_bytes < 0) {
            perror("Error sending to client");
        }
    }
    return 0;
}