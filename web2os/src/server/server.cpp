#include "server/server.hpp"
#include "server/router.hpp"
#include <iostream>

Server::Server(Database* db) : db_(db) {
    std::cout << "Server initialized with Database." << std::endl;
}

void Server::start(int port) {
    // Create a Router instance and set up routes
    Router router(httpServer, db_);
    router.setupRoutes();

    // Start the HTTP server
    std::cout << "Server is running: http://localhost:" << port << "..." << std::endl;
    httpServer.listen("localhost", port);
}
