#include "HttpServer.h"
#include <direct.h>

int main() {
    _chdir(""); // TODO: Fix default pathing issue

    HttpServer server;
    server.initialize();
    server.start();
}
