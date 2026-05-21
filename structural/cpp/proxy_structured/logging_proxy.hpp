#pragma once
#include <memory>

class Service {
public:
    virtual ~Service() = default;
    virtual void doWork() = 0;
};

class RealService : public Service {
public:
    void doWork() override {
        std::cout << "Service: Performing work..." << std::endl;
    }
};

class LoggingProxy : public Service {
private:
    std::unique_ptr<RealService> realService;
    
    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }
    
public:
    LoggingProxy() : realService(std::make_unique<RealService>()) {}
    
    void doWork() override {
        log("Before doWork");
        realService->doWork();
        log("After doWork");
    }
};
