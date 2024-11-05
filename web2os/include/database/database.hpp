#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <sqlite3.h>
#include "config/config.hpp"

class Database {
public:
    Database(const ConfigData& config_data);
    ~Database();

    bool addUser(const std::string& username, const std::string& password);
    bool authenticateUser(const std::string& username, const std::string& password);
    int getUserIdByUsername(const std::string& username); // New method
    std::vector<std::string> getAllUsers();
    std::unordered_map<std::string, std::string> getUserSettings(int userId);
    bool updateUserSetting(int userId, const std::string& key, const std::string& value);

private:
    sqlite3* m_database;
    bool executeQuery(const std::string& query);
};

#endif // DATABASE_HPP
