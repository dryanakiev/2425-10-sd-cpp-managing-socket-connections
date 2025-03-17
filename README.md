# Simple Socket Client-Server in C++

This repository contains a basic example of a socket-based client-server application in C++. The application demonstrates communication between a server and a client using TCP sockets. 

**Note:** This repository is for educational purposes only. It provides a simple implementation of socket programming in C++ and is not intended for production use.

## Features

- Basic HTTP server using Winsock (Windows).
- Handles requests for static files (HTML, CSS).
- Handles multiple routes (`/`, `/about`, `/contact` and `/register`).
- Easy to modify and extend.

### Prerequisites

- **Windows OS** (MinGW, or other Windows-based C++ compiler).
- **C++17** or higher (recommended for modern C++ features).
- **CLion** or another C++ IDE (optional, but helpful for development).

## Important: Fix path issue later
The root directory of the project determines where the Pages folder and other assets are located. Currently, the server uses relative paths that assume the working directory is set to the root of your project. This can cause issues with paths depending on how the executable is run.

### Temporary Fix: 
The server uses _chdir() to change the working directory to the project root, but this may expose the absolute file path of your user directory, which is not ideal.
### Permanent Fix: 
Modify the code to ensure that the root directory and path handling are secure and flexible without exposing your user folder. You can adjust this later by either dynamically setting the working directory or configuring the paths more securely.
