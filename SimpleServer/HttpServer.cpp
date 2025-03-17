/*
Code snippets and standard implementation can be found at https://learn.microsoft.com/en-us/windows/win32/winsock/getting-started-with-winsock
 */

#include "HttpServer.h"

#include <fstream>
#pragma comment(lib, "ws2_32.lib")
#define PORT 8080
WSADATA wsaData;

HttpServer::HttpServer() : addressLength(sizeof(serverAddress)) {
    memset(requestBuffer, 0, sizeof(requestBuffer));

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed" << endl;
        exit(EXIT_FAILURE);
    }
}

void HttpServer::initialize() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    listen(serverSocket, 3);
}

void HttpServer::start() {
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &serverAddress.sin_addr, ip, sizeof(ip));
    cout << "Server is listening on " << ip << ":" << PORT << endl;

    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&serverAddress, (socklen_t*)&addressLength);
        processRequest();
    }
}

void HttpServer::processRequest() {
    recv(clientSocket, requestBuffer, sizeof(requestBuffer), 0);

    cout << "Received request:\n" << requestBuffer << endl;

    string path = extractPath(requestBuffer);

    string fileName;

    if (path.find("/css/") == 0) {
        fileName = "Pages" + path;
    } else {
        fileName = getFileForPath(path);
    }

    ifstream htmlFile(fileName, ios::in | ios::binary);
    if (!htmlFile.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        string notFoundResponse = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n"
                                 "<html><body><h1>404 Not Found</h1></body></html>";
        send(clientSocket, notFoundResponse.c_str(), notFoundResponse.length(), 0);
        closesocket(clientSocket);
        return;
    }

    string contentType = "text/html";
    if (path.find(".css") != string::npos) {
        contentType = "text/css";
    }

    string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: " + contentType + "\r\nConnection: close\r\n\r\n";

    string fileContent((istreambuf_iterator<char>(htmlFile)), istreambuf_iterator<char>());
    httpResponse += fileContent;

    send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);

    closesocket(clientSocket);
}


string HttpServer::extractPath(const char *request) {
    std::string requestStr(request);
    size_t pos1 = requestStr.find(" ");
    size_t pos2 = requestStr.find(" ", pos1 + 1);

    if (pos1 == std::string::npos || pos2 == std::string::npos) {
        return "/";
    }

    std::string path = requestStr.substr(pos1 + 1, pos2 - pos1 - 1);
    return path.empty() ? "/" : path;
}

string HttpServer::getFileForPath(const std::string &path) {

    if (path == "/") {
        return "Pages/index.html";
    }
    else if (path == "/about") {
        return "Pages/about.html";
    }
    else if (path == "/contact") {
        return "Pages/contact.html";
    }
    else if (path == "/register") {
        return "Pages/register.html";
    }
    return "Pages/index.html";
}

HttpServer::~HttpServer() {
    // Cleanup Winsock
    WSACleanup();
}
