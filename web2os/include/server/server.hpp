#ifndef SERVER_HPP
#define SERVER_HPP

// Project headers
#include "config/config.hpp"
#include "database/database.hpp"
#include "server/router.hpp"

// External libraries
#include <httplib.h>

// Standard C++ includes
#include <unordered_map>
#include <string>

class Server {
public:
    Server(const Config& config);
    void start();
private:
    // Member variables
    Database        m_database;
    httplib::Server m_http_server;
    Router          m_router;
    ConfigData      m_config_data;
    // Member functions   
    void setupRoutes();
    std::string getHtmlFileContent(const std::string& filePath); // Helper method
};

#endif // SERVER_HPP
