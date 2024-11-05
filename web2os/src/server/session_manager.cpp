#include "server/session_manager.hpp"

// Singleton instance method
SessionManager& SessionManager::getInstance() {
    static SessionManager instance;
    return instance;
}

// Create 

// Get session data by key
std::string SessionManager::getSessionData(const std::string& key) const {
    // session_data is a unique_ptr, so we need to dereference it to access the map
    if (session_data_) {
        auto it = session_data_->find(key);
        return it != session_data_->end() ? it->second : "";
    }else{
        return "";
    }
}

// Set session data by key
void SessionManager::setSessionData(const std::string& key, const std::string& value) {
    // If session_data is null, create a new map
    if (!session_data_) {
        session_data_ = std::make_unique<std::unordered_map<std::string, std::string>>();
    }
    // Set the value in the map
    (*session_data_)[key] = value;
}

// Clear all session data
void SessionManager::clearSessionData() {
    // If session_data is not null, clear the map
    if (session_data_) {
        session_data_->clear();
    }
}
