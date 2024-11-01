#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <vector>
#include <sqlite3.h>

class Database {
public:
    Database(const std::string& db_path);
    ~Database();

    bool addUser(const std::string& username, const std::string& password);
    bool authenticateUser(const std::string& username, const std::string& password);
    std::vector<std::string> getAllUsers(); // New method to get all users

private:
    sqlite3* db_;
    bool executeQuery(const std::string& query);
};

#endif // DATABASE_HPP
