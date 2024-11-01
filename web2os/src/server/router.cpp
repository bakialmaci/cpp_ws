#include "server/router.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp>

Router::Router(httplib::Server& server, Database* db) : server_(server), db_(db) {}

void Router::setupRoutes() {
    server_.Get("/", [this](const httplib::Request& req, httplib::Response& res) {
        handleIndex(req, res);
    });
    server_.Get("/profile", [this](const httplib::Request& req, httplib::Response& res) {
        handleProfile(req, res);
    });
    server_.Get("/login", [this](const httplib::Request& req, httplib::Response& res) {
        handleLoginPage(req, res);
    });
    server_.Get("/signup", [this](const httplib::Request& req, httplib::Response& res) {
        handleSignupPage(req, res);
    });
    server_.Post("/login", [this](const httplib::Request& req, httplib::Response& res) {
        handleLogin(req, res);
    });
    server_.Post("/signup", [this](const httplib::Request& req, httplib::Response& res) {
        handleSignup(req, res);
    });
    server_.Get("/api/profile", [this](const httplib::Request& req, httplib::Response& res) {
        handleProfileApi(req, res);
    });
    server_.Get("/api/users", [this](const httplib::Request& req, httplib::Response& res) {
        handleGetAllUsers(req, res);
    });
}

// Helper method to get session data
std::string Router::getSessionData(const std::string& key) {
    auto it = sessionData_.find(key);
    if (it != sessionData_.end()) {
        return it->second;
    }
    return "";
}

// Helper method to set session data
void Router::setSessionData(const std::string& key, const std::string& value) {
    sessionData_[key] = value;
}

void Router::handleIndex(const httplib::Request&, httplib::Response& res) {
    std::ifstream file("../web/index.html");
    if (!file.is_open()) {
        res.set_content("<h1>404 Not Found</h1>", "text/html");
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    res.set_content(buffer.str(), "text/html");
}

void Router::handleProfile(const httplib::Request&, httplib::Response& res) {
    std::ifstream file("../web/pages/profile.html");
    if (!file.is_open()) {
        res.set_content("<h1>404 Not Found</h1>", "text/html");
        return;
    }

    // Load the profile.html content and replace a placeholder with the username
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    // Replace the placeholder with the username from the session data
    std::string username = getSessionData("username");
    std::string placeholder = "{{username}}";
    size_t pos = content.find(placeholder);
    
    if (pos != std::string::npos) {
        content.replace(pos, placeholder.length(), username);
    }

    res.set_content(content, "text/html");
}

void Router::handleLoginPage(const httplib::Request&, httplib::Response& res) {
    std::ifstream file("../web/pages/login.html");
    if (!file.is_open()) {
        res.set_content("<h1>404 Not Found</h1>", "text/html");
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    res.set_content(buffer.str(), "text/html");
}

void Router::handleSignupPage(const httplib::Request&, httplib::Response& res) {
    std::ifstream file("../web/pages/signup.html");
    if (!file.is_open()) {
        res.set_content("<h1>404 Not Found</h1>", "text/html");
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    res.set_content(buffer.str(), "text/html");
}

void Router::handleLogin(const httplib::Request& req, httplib::Response& res) {
    std::string username = req.get_param_value("username");
    std::string password = req.get_param_value("password");

    if (db_->authenticateUser(username, password)) {
        // Store the username in the session data
        setSessionData("username", username);

        // Redirect to the profile page on successful login
        res.set_redirect("/profile");
    } else {
        // Respond with an error message if the credentials are incorrect
        res.set_content("{\"error\": \"Invalid username or password.\"}", "application/json");
    }
}

void Router::handleSignup(const httplib::Request& req, httplib::Response& res) {
    std::string username = req.get_param_value("username");
    std::string password = req.get_param_value("password");

    if (db_->addUser(username, password)) {
        // Redirect to the login page on success
        res.set_redirect("/login");
    } else {
        // Respond with an error message if the user already exists or any other error
        res.set_content("{\"error\": \"User already exists or could not be added.\"}", "application/json");
    }
}

void Router::handleProfileApi(const httplib::Request&, httplib::Response& res) {
    // Check if the username is stored in the session data
    std::string username = getSessionData("username");
    if (username.empty()) {
        res.set_content("{\"error\": \"User not logged in.\"}", "application/json");
        return;
    }

    // Respond with the username in JSON format
    nlohmann::json response = {{"username", username}};
    res.set_content(response.dump(), "application/json");
}

void Router::handleGetAllUsers(const httplib::Request&, httplib::Response& res) {
    std::vector<std::string> users = db_->getAllUsers();
    nlohmann::json response = {{"users", users}};
    res.set_content(response.dump(), "application/json");
}
