#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "httplib.h"
#include "database/database.hpp"
#include <string>
#include <unordered_map>

class Router {
public:
    Router(httplib::Server& server, Database* db);
    void setupRoutes();

private:
    httplib::Server& server_;
    Database* db_;
    std::unordered_map<std::string, std::string> sessionData_; // Map for session data

    void handleIndex(const httplib::Request&, httplib::Response& res);
    void handleProfile(const httplib::Request&, httplib::Response& res);
    void handleLoginPage(const httplib::Request&, httplib::Response& res);
    void handleSignupPage(const httplib::Request&, httplib::Response& res);
    void handleLogin(const httplib::Request& req, httplib::Response& res);
    void handleSignup(const httplib::Request& req, httplib::Response& res);
    void handleProfileApi(const httplib::Request& req, httplib::Response& res);
    void handleGetAllUsers(const httplib::Request&, httplib::Response& res);

    // Helper methods
    std::string getSessionData(const std::string& key);
    void setSessionData(const std::string& key, const std::string& value);
};

#endif // ROUTER_HPP
