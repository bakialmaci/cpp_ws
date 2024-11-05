#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "httplib.h"
#include "database/database.hpp"
#include "middleware/auth_middleware.hpp"
#include <string>
#include <unordered_map>
#include "server/session_manager.hpp"

class Router {
public:
    Router(httplib::Server& server, Database& db);
    void setupRoutes();

private:
    httplib::Server&    m_http_server;
    Database&           m_database;
    SessionManager&     m_session_manager;

    // AuthMiddleware is now an instance member
    AuthMiddleware authMiddleware_;

    void handleIndex(const httplib::Request&, httplib::Response& res);
    void handleProfile(const httplib::Request&, httplib::Response& res);
    void handleLoginPage(const httplib::Request&, httplib::Response& res);
    void handleSignupPage(const httplib::Request&, httplib::Response& res);
    void handleLogin(const httplib::Request& req, httplib::Response& res);
    void handleSignup(const httplib::Request& req, httplib::Response& res);
    void handleProfileApi(const httplib::Request&, httplib::Response& res);
    void handleGetAllUsers(const httplib::Request&, httplib::Response& res);
    void handleGetSettings(const httplib::Request&, httplib::Response& res);
    void handleUpdateSettings(const httplib::Request& req, httplib::Response& res);
    void handleLogout(const httplib::Request&, httplib::Response& res);

    // Helper methods for session data management
    std::string getSessionData(const std::string& key);
    void setSessionData(const std::string& key, const std::string& value);
};

#endif // ROUTER_HPP
