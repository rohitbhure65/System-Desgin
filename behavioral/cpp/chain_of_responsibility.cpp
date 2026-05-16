/*
 * CHAIN OF RESPONSIBILITY DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Chain of Responsibility pattern lets you pass requests along a chain of handlers.
 * Each handler decides either to process the request or to pass it to the next handler in the chain.
 * 
 * WHY DOES IT EXIST?
 * - When you want to decouple senders of a request from its receivers
 * - When multiple objects can handle a request without the sender knowing which one will
 * - When you want to dynamically add or remove handlers at runtime
 * 
 * WHEN TO USE IT?
 * - When more than one object can handle a request, and the handler isn't known a priori
 * - When you want to issue a request to one of several objects without specifying the receiver explicitly
 * - When the set of objects that can handle a request should be specified dynamically
 * - Common use cases: event handling systems, logging frameworks, approval workflows, help systems
 * 
 * PROS:
 * - Decouples sender from receiver (sender doesn't know which handler will process)
 * - Open/Closed Principle (can add new handlers without changing existing code)
 * - Can control the order of handling
 * - Simplifies object interactions
 * 
 * CONS:
 * - No guarantee that a request will be handled
 * - Can lead to deep chains that are hard to debug
 * - May affect performance if the chain is long
 * - Can be difficult to observe runtime characteristics
 * 
 * REAL-WORLD ANALOGY:
 * Think of a customer service call center. When you call, your request goes through a chain of representatives. If the first representative can't help, they transfer you to a specialist. If that specialist can't help, they transfer you to a manager. The call moves up the chain until someone can help or you reach the end.
 */

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

// Example 2: Document Approval Chain
// Shows how Chain of Responsibility can be used for approval workflows

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

class TeamLead : public Approver {
public:
    void approveRequest(double amount) override {
        if (amount <= 1000) {
            std::cout << "TeamLead: Approved request of $" << amount << std::endl;
        } else if (nextApprover) {
            std::cout << "TeamLead: Amount exceeds limit, passing to manager..." << std::endl;
            nextApprover->approveRequest(amount);
        } else {
            std::cout << "TeamLead: Cannot approve this amount" << std::endl;
        }
    }
};

class Manager : public Approver {
public:
    void approveRequest(double amount) override {
        if (amount <= 5000) {
            std::cout << "Manager: Approved request of $" << amount << std::endl;
        } else if (nextApprover) {
            std::cout << "Manager: Amount exceeds limit, passing to director..." << std::endl;
            nextApprover->approveRequest(amount);
        } else {
            std::cout << "Manager: Cannot approve this amount" << std::endl;
        }
    }
};

class Director : public Approver {
public:
    void approveRequest(double amount) override {
        if (amount <= 20000) {
            std::cout << "Director: Approved request of $" << amount << std::endl;
        } else if (nextApprover) {
            std::cout << "Director: Amount exceeds limit, passing to CEO..." << std::endl;
            nextApprover->approveRequest(amount);
        } else {
            std::cout << "Director: Cannot approve this amount" << std::endl;
        }
    }
};

class CEO : public Approver {
public:
    void approveRequest(double amount) override {
        std::cout << "CEO: Approved request of $" << amount << " (final approver)" << std::endl;
    }
};

// Example 3: Logging Chain
// Shows how Chain of Responsibility can be used for logging

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

int main() {
    std::cout << "=== Chain of Responsibility Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Customer Service Chain
    std::cout << "--- Customer Service Chain ---" << std::endl;
    
    auto agent = std::make_shared<SupportAgent>();
    auto specialist = std::make_shared<TechnicalSpecialist>();
    auto manager = std::make_shared<Manager>();
    
    agent->setNext(specialist);
    specialist->setNext(manager);
    
    std::cout << "\nRequest: basic_question" << std::endl;
    agent->handleRequest("basic_question");
    
    std::cout << "\nRequest: complex_technical" << std::endl;
    agent->handleRequest("complex_technical");
    
    std::cout << "\nRequest: refund" << std::endl;
    agent->handleRequest("refund");
    
    std::cout << "\nRequest: unknown" << std::endl;
    agent->handleRequest("unknown");
    
    std::cout << std::endl;
    
    // Example 2: Document Approval Chain
    std::cout << "--- Document Approval Chain ---" << std::endl;
    
    auto teamLead = std::make_shared<TeamLead>();
    auto manager2 = std::make_shared<Manager>();
    auto director = std::make_shared<Director>();
    auto ceo = std::make_shared<CEO>();
    
    teamLead->setNext(manager2);
    manager2->setNext(director);
    director->setNext(ceo);
    
    std::cout << "\nRequest: $500" << std::endl;
    teamLead->approveRequest(500);
    
    std::cout << "\nRequest: $3000" << std::endl;
    teamLead->approveRequest(3000);
    
    std::cout << "\nRequest: $15000" << std::endl;
    teamLead->approveRequest(15000);
    
    std::cout << "\nRequest: $50000" << std::endl;
    teamLead->approveRequest(50000);
    
    std::cout << std::endl;
    
    // Example 3: Logging Chain
    std::cout << "--- Logging Chain ---" << std::endl;
    
    auto consoleLogger = std::make_shared<ConsoleLogger>();
    auto fileLogger = std::make_shared<FileLogger>();
    auto errorLogger = std::make_shared<ErrorLogger>();
    
    consoleLogger->setNext(fileLogger);
    fileLogger->setNext(errorLogger);
    
    std::cout << "\nLog: Info message (severity 1)" << std::endl;
    consoleLogger->log("Info message", 1);
    
    std::cout << "\nLog: Warning message (severity 2)" << std::endl;
    consoleLogger->log("Warning message", 2);
    
    std::cout << "\nLog: Error message (severity 3)" << std::endl;
    consoleLogger->log("Error message", 3);
    
    return 0;
}
