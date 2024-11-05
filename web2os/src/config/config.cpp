// Project includes
#include "config/config.hpp"

// Standard C++ includes
#include <fstream>
#include <iostream>
#include <stdexcept>

// External libraries
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Config::Config(const std::string& configFilePath) {
    loadConfig(configFilePath);
}

void Config::loadConfig(const std::string& configFilePath) {
    std::ifstream configFile(configFilePath);
    if (!configFile.is_open()) {
        throw std::runtime_error("Failed to open configuration file: " + configFilePath);
    }

    json configJson;
    configFile >> configJson;

    // Load the database path
    if (configJson.contains("databasePath")) {
        configData_.databasePath = configJson["databasePath"].get<std::string>();
    } else {
        throw std::runtime_error("Missing 'databasePath' in configuration file.");
    }

    // Load the server port
    if (configJson.contains("serverPort")) {
        configData_.serverPort = configJson["serverPort"].get<int>();
    } else {
        throw std::runtime_error("Missing 'serverPort' in configuration file.");
    }
}

ConfigData Config::getConfigData() const {
    return configData_;
}
