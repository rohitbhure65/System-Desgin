#pragma once
#include "interfaces.hpp"

class ConsoleLogger : public Logger {
public:
    void log(const std::string& message, int severity) override {
        if (severity >= 1) {
            std::cout << "[CONSOLE] " << message << std::endl;
        }
        if (nextLogger) {
            nextLogger->log(message, severity);
        }
    }
};

class FileLogger : public Logger {
public:
    void log(const std::string& message, int severity) override {
        if (severity >= 2) {
            std::cout << "[FILE] " << message << std::endl;
        }
        if (nextLogger) {
            nextLogger->log(message, severity);
        }
    }
};

class ErrorLogger : public Logger {
public:
    void log(const std::string& message, int severity) override {
        if (severity >= 3) {
            std::cout << "[ERROR] " << message << std::endl;
        }
        if (nextLogger) {
            nextLogger->log(message, severity);
        }
    }
};
