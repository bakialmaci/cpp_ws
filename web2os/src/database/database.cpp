#include "database/database.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

Database::Database(const std::string& db_path) {
    if (sqlite3_open(db_path.c_str(), &db_) != SQLITE_OK) {
        throw std::runtime_error("Failed to open database: " + std::string(sqlite3_errmsg(db_)));
    }
}

Database::~Database() {
    if (db_) {
        sqlite3_close(db_);
    }
}

bool Database::addUser(const std::string& username, const std::string& password) {
    std::ostringstream query;
    query << "INSERT INTO users (username, password) VALUES ('" << username << "', '" << password << "');";
    return executeQuery(query.str());
}

bool Database::authenticateUser(const std::string& username, const std::string& password) {
    std::ostringstream query;
    query << "SELECT COUNT(*) FROM users WHERE username = '" << username << "' AND password = '" << password << "';";
    
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db_, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(db_) << std::endl;
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

std::vector<std::string> Database::getAllUsers() {
    std::vector<std::string> users;
    const char* query = "SELECT username FROM users;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db_, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(db_) << std::endl;
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

bool Database::executeQuery(const std::string& query) {
    char* errorMessage = nullptr;
    if (sqlite3_exec(db_, query.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}
