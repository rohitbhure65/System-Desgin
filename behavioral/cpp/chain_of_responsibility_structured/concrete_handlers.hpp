#pragma once
#include "interfaces.hpp"

// Concrete Handler 1: Support Agent
class SupportAgent : public Handler {
public:
    void handleRequest(const std::string& request) override {
        if (request == "technical_issue" || request == "basic_question") {
            std::cout << "SupportAgent: Handling request - " << request << std::endl;
        } else if (nextHandler) {
            std::cout << "SupportAgent: Passing to next handler..." << std::endl;
            nextHandler->handleRequest(request);
        } else {
            std::cout << "SupportAgent: Cannot handle this request" << std::endl;
        }
    }
};

// Concrete Handler 2: Technical Specialist
class TechnicalSpecialist : public Handler {
public:
    void handleRequest(const std::string& request) override {
        if (request == "complex_technical" || request == "bug_report") {
            std::cout << "TechnicalSpecialist: Handling request - " << request << std::endl;
        } else if (nextHandler) {
            std::cout << "TechnicalSpecialist: Passing to next handler..." << std::endl;
            nextHandler->handleRequest(request);
        } else {
            std::cout << "TechnicalSpecialist: Cannot handle this request" << std::endl;
        }
    }
};

// Concrete Handler 3: Manager
class Manager : public Handler {
public:
    void handleRequest(const std::string& request) override {
        if (request == "refund" || request == "complaint" || request == "escalation") {
            std::cout << "Manager: Handling request - " << request << std::endl;
        } else if (nextHandler) {
            std::cout << "Manager: Passing to next handler..." << std::endl;
            nextHandler->handleRequest(request);
        } else {
            std::cout << "Manager: Cannot handle this request" << std::endl;
        }
    }
};
