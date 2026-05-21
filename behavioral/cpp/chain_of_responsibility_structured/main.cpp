#include "interfaces.hpp"
#include "concrete_handlers.hpp"
#include "concrete_approvers.hpp"
#include "concrete_loggers.hpp"

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
    auto manager2 = std::make_shared<ManagerApprover>();
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
