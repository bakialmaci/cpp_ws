#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

struct ConfigData {
    std::string databasePath;
    int serverPort;
};

class Config {
public:
    // Constructor that loads the configuration from a file
    Config(const std::string& configFilePath);

    // Getter method to access the configuration data
    ConfigData getConfigData() const;

private:
    // Method to load configuration from a file
    void loadConfig(const std::string& configFilePath);

    // Member variable to store the configuration data
    ConfigData configData_;
};

#endif // CONFIG_HPP
