#pragma once
#include <string>
#include <memory>

class ConfigurationMemento {
private:
    std::string theme;
    int fontSize;
    bool notificationsEnabled;
    
public:
    ConfigurationMemento(const std::string& theme, int fontSize, bool notifications)
        : theme(theme), fontSize(fontSize), notificationsEnabled(notifications) {}
    
    std::string getTheme() const { return theme; }
    int getFontSize() const { return fontSize; }
    bool getNotificationsEnabled() const { return notificationsEnabled; }
};

class ApplicationSettings {
private:
    std::string theme;
    int fontSize;
    bool notificationsEnabled;
    
public:
    ApplicationSettings() : theme("light"), fontSize(12), notificationsEnabled(true) {}
    
    void setTheme(const std::string& newTheme) {
        theme = newTheme;
        std::cout << "Theme changed to " << theme << std::endl;
    }
    
    void setFontSize(int size) {
        fontSize = size;
        std::cout << "Font size set to " << fontSize << std::endl;
    }
    
    void setNotificationsEnabled(bool enabled) {
        notificationsEnabled = enabled;
        std::cout << "Notifications " << (enabled ? "enabled" : "disabled") << std::endl;
    }
    
    void displaySettings() const {
        std::cout << "=== Current Settings ===" << std::endl;
        std::cout << "Theme: " << theme << std::endl;
        std::cout << "Font Size: " << fontSize << std::endl;
        std::cout << "Notifications: " << (notificationsEnabled ? "Enabled" : "Disabled") << std::endl;
        std::cout << "=====================" << std::endl;
    }
    
    std::unique_ptr<ConfigurationMemento> saveConfiguration() {
        return std::make_unique<ConfigurationMemento>(theme, fontSize, notificationsEnabled);
    }
    
    void restoreConfiguration(const ConfigurationMemento& memento) {
        theme = memento.getTheme();
        fontSize = memento.getFontSize();
        notificationsEnabled = memento.getNotificationsEnabled();
        std::cout << "Configuration restored!" << std::endl;
        displaySettings();
    }
};
