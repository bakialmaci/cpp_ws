#include "config/config.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
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

    if (configJson.contains("databasePath")) {
        databasePath_ = configJson["databasePath"].get<std::string>();
    } else {
        throw std::runtime_error("Missing 'databasePath' in configuration file.");
    }
}

std::string Config::getDatabasePath() const {
    return databasePath_;
}
