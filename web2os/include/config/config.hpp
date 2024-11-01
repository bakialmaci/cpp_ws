#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

class Config {
public:
    // Constructor to load settings
    Config(const std::string& configFilePath);

    // Method to get the database path
    std::string getDatabasePath() const;

private:
    std::string databasePath_;
    void loadConfig(const std::string& configFilePath);
};

#endif // CONFIG_HPP
