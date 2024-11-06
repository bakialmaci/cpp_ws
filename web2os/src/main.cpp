// Author: Baki ALMACI

// Project includes
#include "config/config.hpp"
#include "server/server.hpp"

// Standard C++ includes
#include <iostream>

// Global definitions
const std::string CONFIG_FILE_PATH = "/app/config/config.json";

int main() {
    try {
        // Configuration setup
        Config config(CONFIG_FILE_PATH);

        // Server setup
        Server server(config);
        
        // Start the server
        server.start();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE; // Return non-zero exit code on failure
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return EXIT_FAILURE; // Return non-zero exit code on failure
    }

    return EXIT_SUCCESS; // Return zero exit code on success
}
