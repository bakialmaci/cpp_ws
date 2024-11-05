#include "middleware/auth_middleware.hpp"
#include <iostream>

// Constructor that initializes session data using createSessionData()
AuthMiddleware::AuthMiddleware()
    : sessionData_(createSessionData()) {}

// Method to check if a user is authenticated
bool AuthMiddleware::isAuthenticated(const httplib::Request& req) {
    (void)req; // Unused parameter
    // Check if the session contains a "username" entry
    auto it = sessionData_.find("username");
    return it != sessionData_.end() && !it->second.empty();
}

// Method to require authentication
void AuthMiddleware::requireAuth(const httplib::Request& req, httplib::Response& res) {
    if (!isAuthenticated(req)) {
        // If not authenticated, redirect to the login page
        res.set_redirect("/login");
        std::cerr << "Unauthorized access attempt. Redirecting to /login." << std::endl;
    }
}

// Static method to create session data
std::unordered_map<std::string, std::string> AuthMiddleware::createSessionData() {
    return std::unordered_map<std::string, std::string>();
}
