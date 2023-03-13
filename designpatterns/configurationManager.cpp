#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

class ConfigurationManager {
private:
    std::unordered_map<std::string, std::string> configMap;
    std::string configFileName;
    static ConfigurationManager* instance;
    ConfigurationManager() {
        configFileName = "config.txt";
        readConfigFromFile();
    }
public:
    static ConfigurationManager* getInstance() {
        if (instance == nullptr) {
            instance = new ConfigurationManager();
        }
        return instance;
    }
    std::string getConfigValue(std::string key) {
        return configMap[key];
    }
    void setConfigValue(std::string key, std::string value) {
        configMap[key] = value;
    }
    void saveConfigToFile() {
        std::ofstream outfile(configFileName);
        if (outfile.is_open()) {
            for (auto& [key, value] : configMap) {
                outfile << key << "=" << value << std::endl;
            }
            std::cout << "Configuration saved to file: " << configFileName << std::endl;
        }
        else {
            std::cerr << "Error opening file for writing: " << configFileName << std::endl;
        }
        outfile.close();
    }
    void reloadConfigFromFile() {
        readConfigFromFile();
        std::cout << "Configuration reloaded from file: " << configFileName << std::endl;
    }
    void printConfigValues() {
        for (auto& [key, value] : configMap) {
            std::cout << key << ": " << value << std::endl;
        }
    }
private:
    void readConfigFromFile() {
        std::ifstream infile(configFileName);
        if (infile.is_open()) {
            std::string line;
            while (std::getline(infile, line)) {
                std::stringstream ss(line);
                std::string key, value;
                if (std::getline(ss, key, '=') && std::getline(ss, value)) {
                    configMap[key] = value;
                }
            }
            std::cout << "Configuration loaded from file: " << configFileName << std::endl;
        }
        else {
            std::cerr << "Error opening file for reading: " << configFileName << std::endl;
        }
        infile.close();
    }
};

ConfigurationManager* ConfigurationManager::instance = nullptr;

int main() {
    ConfigurationManager* configManager = ConfigurationManager::getInstance();

    // Print all config values
    std::cout << "Current configuration:" << std::endl;
    configManager->printConfigValues();

    // Get config value
    std::cout << "DB_HOST: " << configManager->getConfigValue("DB_HOST") << std::endl;

    // Set config value
    configManager->setConfigValue("DB_HOST", "newhost");

    // Print all config values again
    std::cout << "New configuration:" << std::endl;
    configManager->printConfigValues();

    // Save config to file
    configManager->saveConfigToFile();

    // Reload config from file
    configManager->reloadConfigFromFile();

    // Print all config values again
    std::cout << "Reloaded configuration:" << std::endl;
    configManager->printConfigValues();

    return 0;
}
