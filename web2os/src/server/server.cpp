// Project headers
#include "server/server.hpp"

// Standard C++ includes
#include <iostream>

Server::Server(const Config& config) 
    :   m_database(config.getConfigData()), 
        m_router(m_http_server, m_database), 
        m_config_data(config.getConfigData()) 
{
    /* Nothing to do for now */
}

void Server::start() {
    // Start the HTTP server
    std::cout << "Server is running: http://localhost:" << m_config_data.serverPort << std::endl;
    m_http_server.listen("0.0.0.0", m_config_data.serverPort);
}