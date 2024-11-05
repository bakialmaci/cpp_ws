#ifndef SESSION_MANAGER_HPP
#define SESSION_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <memory>

class SessionManager {
public:
    // Singleton pattern for global access
    static SessionManager& getInstance();

    // Method to get a session value by key
    std::string getSessionData(const std::string& key) const;

    // Method to set a session value by key
    void setSessionData(const std::string& key, const std::string& value);

    // Method to clear session data (e.g., on logout)
    void clearSessionData();

private:
    // Private constructor for Singleton
    SessionManager() = default;

    // Delete copy constructor and assignment operator for Singleton
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;

    // The actual session data storage
    std::unique_ptr<std::unordered_map<std::string, std::string>> session_data_;
};

#endif // SESSION_MANAGER_HPP
