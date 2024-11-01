#ifndef SERVER_HPP
#define SERVER_HPP

#include "database/database.hpp"
#include "httplib.h"
#include <string>

class Server {
public:
    Server(Database* db);
    void start(int port);

private:
    Database* db_;
    httplib::Server httpServer;

    void setupRoutes();
    std::string getHtmlFileContent(const std::string& filePath); // Helper method
};

#endif // SERVER_HPP
