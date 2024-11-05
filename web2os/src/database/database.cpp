// Description: Implementation of the Database class.

// Project includes
#include "database/database.hpp"

// Standard C++ includes
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <filesystem>

Database::Database(const ConfigData& config_data) {
    // Check if the SQLite database file exists
    if (!std::filesystem::exists(config_data.databasePath)) {
        throw std::runtime_error("Database file not found at: " + config_data.databasePath);
    }else{
        std::cout << "Database file found at: " << config_data.databasePath << std::endl;
    }

    // Open the SQLite database
    if (sqlite3_open(config_data.databasePath.c_str(), &m_database) != SQLITE_OK) {
        throw std::runtime_error("Failed to open database: " + std::string(sqlite3_errmsg(m_database)));
    }else{
        std::cout << "Database opened successfully." << std::endl;
    }
}

Database::~Database() {
    // Close the SQLite database if it's open
    if (m_database) {
        sqlite3_close(m_database);
    }
}

bool Database::addUser(const std::string& username, const std::string& password) {
    // Prepare an SQL query to insert a new user
    std::ostringstream query;
    query << "INSERT INTO users (username, password) VALUES ('" << username << "', '" << password << "');";
    return executeQuery(query.str());
}

bool Database::authenticateUser(const std::string& username, const std::string& password) {
    // Prepare an SQL query to authenticate the user
    std::ostringstream query;
    query << "SELECT COUNT(*) FROM users WHERE username = '" << username << "' AND password = '" << password << "';";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(m_database, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(m_database) << std::endl;
        return false;
    }

    bool authenticated = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        authenticated = (count > 0);
    }

    sqlite3_finalize(stmt);
    return authenticated;
}

int Database::getUserIdByUsername(const std::string& username) {
    // Prepare an SQL query to get the user ID by username
    std::ostringstream query;
    query << "SELECT id FROM users WHERE username = '" << username << "';";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(m_database, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(m_database) << std::endl;
        return -1; // Return -1 on failure
    }

    int userId = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        userId = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return userId;
}

std::vector<std::string> Database::getAllUsers() {
    std::vector<std::string> users;
    const char* query = "SELECT username FROM users;";
    sqlite3_stmt* stmt;

    if (!m_database) {
        std::cerr << "Database connection is not initialized." << std::endl;
        return users;
    }

    if (sqlite3_prepare_v2(m_database, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(m_database) << std::endl;
        return users;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* username = sqlite3_column_text(stmt, 0);
        if (username) {
            users.push_back(std::string(reinterpret_cast<const char*>(username)));
        }
    }

    sqlite3_finalize(stmt);
    return users;
}

std::unordered_map<std::string, std::string> Database::getUserSettings(int userId) {
    // Prepare an SQL query to get all settings for a given user ID
    std::unordered_map<std::string, std::string> settings;
    std::ostringstream query;
    query << "SELECT setting_key, setting_value FROM user_settings WHERE user_id = " << userId << ";";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(m_database, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(m_database) << std::endl;
        return settings;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* key = sqlite3_column_text(stmt, 0);
        const unsigned char* value = sqlite3_column_text(stmt, 1);
        if (key && value) {
            settings[std::string(reinterpret_cast<const char*>(key))] = std::string(reinterpret_cast<const char*>(value));
        }
    }

    sqlite3_finalize(stmt);
    return settings;
}

bool Database::updateUserSetting(int userId, const std::string& key, const std::string& value) {
    // Prepare an SQL query to update or insert a setting for a given user ID
    std::ostringstream query;
    query << "REPLACE INTO user_settings (user_id, setting_key, setting_value) VALUES ("
          << userId << ", '" << key << "', '" << value << "');";
    return executeQuery(query.str());
}

bool Database::executeQuery(const std::string& query) {
    // Execute an SQL query and handle any errors
    char* errorMessage = nullptr;
    if (sqlite3_exec(m_database, query.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}
