#pragma once
#include <iostream>
#include <string>
#include <memory>

// Handler interface - declares the handling method and sets a reference to the next handler
class Handler {
protected:
    std::shared_ptr<Handler> nextHandler;
    
public:
    virtual ~Handler() = default;
    
    void setNext(std::shared_ptr<Handler> handler) {
        nextHandler = handler;
    }
    
    virtual void handleRequest(const std::string& request) = 0;
};

// Approver interface for document approval chain
class Approver {
protected:
    std::shared_ptr<Approver> nextApprover;
    
public:
    virtual ~Approver() = default;
    
    void setNext(std::shared_ptr<Approver> approver) {
        nextApprover = approver;
    }
    
    virtual void approveRequest(double amount) = 0;
};

// Logger interface for logging chain
class Logger {
protected:
    std::shared_ptr<Logger> nextLogger;
    
public:
    virtual ~Logger() = default;
    
    void setNext(std::shared_ptr<Logger> logger) {
        nextLogger = logger;
    }
    
    virtual void log(const std::string& message, int severity) = 0;
};
