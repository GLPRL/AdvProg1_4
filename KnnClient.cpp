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
 * Check if port is valid: If can be converted to int, and is in range 0-65535
 * @param port port to listen on
 * @return port number if exists, -1 otherwise.
 */
int getPort(string port) {
    int size = port.size();
    for (int i = 0; i < size; i++) {                  //Iterate through the port characters and validate they are digits
        if (isdigit(port[i]) == false) {
            perror("Port must be an integer");
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
        perror("Wrong amount of command line arguments\n");
        return 1;
    }
    //TODO: Force the 127.0.0.1 loopback/localhost IP?
    const char *ip_address = argv[1];                                                               //Options for socket
    const int port_no = getPort(argv[2]);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket\n");
    }
    struct sockaddr_in sin;                                                                               //setup socket
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {                   //Connected to server
        perror("Error connecting to server");
    }
    //TODO: data_addr[] = input with cin
    char data_addr[] = "3.1 0 20 30 MAN 3\n";                                                         //Data to send
    int data_len = strlen(data_addr);
    int sent_bytes = send(sock, data_addr, data_len, 0);                             //Sending data
    if (sent_bytes < 0) {
        perror("Error sending data to server\n");
        return 1;
    }
    while(true) {                                                                                       //Data send loop
        char buffer[2048];                                                       //Clearing space for answer from server
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);                 //Receive from server
        if (read_bytes == 0) {                                                                               //If closed
            cout << "Connection closed" << endl;
            close(sock);                                                             //close only when server closed
            return 0;
        } else if (read_bytes < 0) {                                                                          //If error
            perror("Error reading data from server");
        } else {
            cout << buffer << endl;                                                                       //Print result
        }
        memset(&buffer, 0, sizeof(buffer));                                       //Purge past data from buffer
        //TODO: data_addr1[] = input with cin
        char data_addr1[] = "-1";
        int data_len1 = strlen(data_addr1);
        int sent_bytes = send(sock, data_addr1, data_len1, 0);                           //Sending data
        if (sent_bytes < 0) {
            perror("Error sending data to server");
            return 1;
        }
        continue;
    }
}
