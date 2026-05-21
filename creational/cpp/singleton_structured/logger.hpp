#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <mutex>

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::once_flag initFlag;
    
    Logger() { std::cout << "Logger: Initializing logger..." << std::endl; }
    ~Logger() { std::cout << "Logger: Destroying logger..." << std::endl; }
    
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    int logCount = 0;

public:
    static Logger& getInstance() {
        std::call_once(initFlag, []() {
            instance.reset(new Logger());
        });
        return *instance;
    }
    
    void log(const std::string& message) {
        logCount++;
        std::cout << "[LOG #" << logCount << "] " << message << std::endl;
    }
    
    int getLogCount() const { return logCount; }
};

std::unique_ptr<Logger> Logger::instance = nullptr;
std::once_flag Logger::initFlag;
