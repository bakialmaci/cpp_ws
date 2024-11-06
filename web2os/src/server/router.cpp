// Project headers
#include "server/router.hpp"

// Standard C++ includes
#include <fstream>
#include <sstream>
#include <iostream>

// External library includes
#include <nlohmann/json.hpp>

Router::Router(httplib::Server& http_server, Database& database) 
    : 
    m_http_server(http_server), 
    m_database(database),
    m_session_manager(SessionManager::getInstance())
{
    setupRoutes(); // Set up all the routes
}

void Router::setupRoutes() {
    // Gets
    m_http_server.Get("/", [this](const httplib::Request& req, httplib::Response& res) {
        handleIndex(req, res);
    });
    m_http_server.Get("/profile", [this](const httplib::Request& req, httplib::Response& res) {
        handleProfile(req, res);
    });
    m_http_server.Get("/login", [this](const httplib::Request& req, httplib::Response& res) {
        handleLoginPage(req, res);
    });
    m_http_server.Get("/signup", [this](const httplib::Request& req, httplib::Response& res) {
        handleSignupPage(req, res);
    });
    // Gets API
    m_http_server.Get("/api/profile", [this](const httplib::Request& req, httplib::Response& res) {
        handleProfileApi(req, res);
    });
    m_http_server.Get("/api/users", [this](const httplib::Request& req, httplib::Response& res) {
        handleGetAllUsers(req, res);
    });
    m_http_server.Get("/api/settings", [this](const httplib::Request& req, httplib::Response& res) {
        handleGetSettings(req, res);
    });
    m_http_server.Get("/logout", [this](const httplib::Request& req, httplib::Response& res) {
        handleLogout(req, res);
    });
    // Posts
    m_http_server.Post("/login", [this](const httplib::Request& req, httplib::Response& res) {
        handleLogin(req, res);
    });
    m_http_server.Post("/signup", [this](const httplib::Request& req, httplib::Response& res) {
        handleSignup(req, res);
    });
    // Posts API
    m_http_server.Post("/api/settings", [this](const httplib::Request& req, httplib::Response& res) {
        handleUpdateSettings(req, res);
    });
    std::cout << "Routes setup successfully!." << std::endl;
}

void Router::handleIndex(const httplib::Request&, httplib::Response& res) {
    std::ifstream file("/app/web/index.html");
    if (!file.is_open()) {
        res.set_content("{\"error\": \"404 Not Found\"}", "application/json");
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    res.set_content(buffer.str(), "text/html");
}

void Router::handleProfile(const httplib::Request&, httplib::Response& res) {
    // Check if the profile page exists
    std::ifstream file("/app/web/pages/profile.html");
    if (!file.is_open()) {
        res.set_content("{\"error\": \"404 Not Found\"}", "application/json");
        return;
    }

    // Check if the user is authenticated
    std::string username = m_session_manager.getSessionData("username");
    if (username.empty()) {
        res.set_redirect("/login");
        return;
    }else{
        std::cout << "User is authenticated: " << username << std::endl;
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        std::string placeholder = "{{username}}";
        size_t pos = content.find(placeholder);
        if (pos != std::string::npos) {
            content.replace(pos, placeholder.length(), username);
        }
        res.set_content(content, "text/html");
        return;
    }
}

void Router::handleLoginPage(const httplib::Request&, httplib::Response& res) {
    std::ifstream file("/app/web/pages/login.html");
    if (!file.is_open()) {
        res.set_content("{\"error\": \"404 Not Found\"}", "application/json");
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    res.set_content(buffer.str(), "text/html");
}

void Router::handleSignupPage(const httplib::Request&, httplib::Response& res) {
    std::ifstream file("/app/web/pages/signup.html");
    if (!file.is_open()) {
        res.set_content("{\"error\": \"404 Not Found\"}", "application/json");
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    res.set_content(buffer.str(), "text/html");
}

void Router::handleLogin(const httplib::Request& req, httplib::Response& res) {
    std::string username = req.get_param_value("username");
    std::string password = req.get_param_value("password");

    if (m_database.authenticateUser(username, password)) {
        m_session_manager.setSessionData("username", username);
        res.set_redirect("/profile"); // Redirect to the profile page on success
    } else {
        res.set_content("{\"error\": \"Invalid username or password.\"}", "application/json");
    }
}

void Router::handleSignup(const httplib::Request& req, httplib::Response& res) {
    std::string username = req.get_param_value("username");
    std::string password = req.get_param_value("password");

    if (m_database.addUser(username, password)) {
        res.set_redirect("/login"); // Redirect to the login page on success
    } else {
        res.set_content("{\"error\": \"User already exists or could not be added.\"}", "application/json");
    }
}

void Router::handleProfileApi(const httplib::Request&, httplib::Response& res) {
    std::string username = m_session_manager.getSessionData("username");
    if (username.empty()) {
        res.set_content("{\"error\": \"User not logged in.\"}", "application/json");
        return;
    }

    nlohmann::json response = {{"username", username}};
    res.set_content(response.dump(), "application/json");
}

void Router::handleGetAllUsers(const httplib::Request&, httplib::Response& res) {
    std::vector<std::string> users = m_database.getAllUsers();
    nlohmann::json response = {{"users", users}};
    res.set_content(response.dump(), "application/json");
}

void Router::handleGetSettings(const httplib::Request&, httplib::Response& res) {
    std::string username = m_session_manager.getSessionData("username");
    if (username.empty()) {
        res.set_content("{\"error\": \"User not logged in.\"}", "application/json");
        return;
    }

    int userId = m_database.getUserIdByUsername(username); 
    auto settings = m_database.getUserSettings(userId);
    nlohmann::json response = settings;
    res.set_content(response.dump(), "application/json");
}

void Router::handleUpdateSettings(const httplib::Request& req, httplib::Response& res) {
    std::string username = m_session_manager.getSessionData("username");
    if (username.empty()) {
        res.set_content("{\"error\": \"User not logged in.\"}", "application/json");
        return;
    }

    int userId = m_database.getUserIdByUsername(username);
    auto json = nlohmann::json::parse(req.body);
    for (auto& [key, value] : json.items()) {
        // Update system volume
        if(key == "volume"){
            std::cout << "Setting system volume to: " << value << std::endl;
            // Update the system volume
            std::string command = "amixer -D pulse sset Master " + value.get<std::string>() + "%";
            system(command.c_str());
        }
        // Update each setting in the database
        m_database.updateUserSetting(userId, key, value);
    }

    res.set_content("{\"message\": \"Settings updated successfully.\"}", "application/json");
}

// Implementation of the handleLogout method
void Router::handleLogout(const httplib::Request&, httplib::Response& res) {
    // Clear the "username" from the session data
    m_session_manager.clearSessionData();

    // Redirect the user to the login page after logging out
    res.set_redirect("/login");

    std::cout << "User logged out successfully." << std::endl;
}