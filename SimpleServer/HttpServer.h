/*
 Code snippets and standard implementation can be found at https://learn.microsoft.com/en-us/windows/win32/winsock/getting-started-with-winsock
 */
using namespace std;
#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 8080

class HttpServer {
private:
    int serverSocket;
    int clientSocket;
    struct sockaddr_in serverAddress;
    int addressLength;
    char requestBuffer[1024];

public:
    HttpServer();
    void initialize();
    void start();
    void processRequest();
    string extractPath(const char* request);
    string getFileForPath(const string& path);

    ~HttpServer();
};

// TODO: Add http method processing for GET and POST

#endif // HTTP_SERVER_H
