#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: chat <port>" << endl;
        return 1;
    }

    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        cout << "Error creating socket" << endl;
        return 1;
    }

    // Bind the socket to a port
    int port = atoi(argv[1]);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        cout << "Error binding socket" << endl;
        return 1;
    }

    // Listen for incoming connections
    listen(sockfd, 5);

    // Accept an incoming connection
    cout << "Waiting for incoming connection..." << endl;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_fd < 0)
    {
        cout << "Error accepting connection" << endl;
        return 1;
    }
    cout << "Incoming connection from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << endl;

    // Chat loop
    while (true)
    {
        // Read a message from the client
        char buffer[256];
        int bytes_received = read(client_fd, buffer, 255);
        if (bytes_received < 0)
        {
            cout << "Error reading from socket" << endl;
            return 1;
        }
        buffer[bytes_received] = '\0';
        cout << "Received: " << buffer << endl;

        // Send a message to the client
        cout << "Send: ";
        string message;
        getline(cin, message);
        int bytes_sent = write(client_fd, message.c_str(), message.length());
        if (bytes_sent < 0)
        {
            cout << "Error writing to socket" << endl;
            return 1;
        }
    }

    // Close the socket
    close(sockfd);

    return 0;
}
