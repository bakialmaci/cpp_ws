#ifndef AUTH_MIDDLEWARE_HPP
#define AUTH_MIDDLEWARE_HPP

#include <httplib.h>
#include <unordered_map>
#include <string>

class AuthMiddleware {
public:
    AuthMiddleware();

    // Method to check if a user is authenticated
    bool isAuthenticated(const httplib::Request& req);

    // Method to require authentication
    void requireAuth(const httplib::Request& req, httplib::Response& res);

private:
    std::unordered_map<std::string, std::string> sessionData_;

    // Static method to create session data
    static std::unordered_map<std::string, std::string> createSessionData();
};

#endif // AUTH_MIDDLEWARE_HPP
