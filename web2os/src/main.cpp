#include "server/server.hpp"
#include "database/database.hpp"
#include <iostream>
#include <filesystem>

// Function to check if the database file exists
bool databaseFileExists(const std::string& db_path) {
    return std::filesystem::exists(db_path);
}

int main() {
    try {
        // Define the relative path to the database file
        std::string dbPath = "../db/users.db";

        // Check if the database file exists
        if (!databaseFileExists(dbPath)) {
            throw std::runtime_error("Database file not found at: " + dbPath);
        }

        // Initialize the database connection
        Database db(dbPath);

        // Create and start the server
        Server server(&db);
        std::cout << "Starting the web2os server on port 8080..." << std::endl;
        server.start(8080);

        // Successful start message
        std::cout << "Server started successfully." << std::endl;
    } catch (const std::exception& e) {
        // Catch and display any exceptions
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE; // Return non-zero exit code on failure
    } catch (...) {
        // Catch any unknown exceptions
        std::cerr << "An unknown error occurred." << std::endl;
        return EXIT_FAILURE; // Return non-zero exit code on failure
    }

    return EXIT_SUCCESS; // Return zero exit code on success
}
