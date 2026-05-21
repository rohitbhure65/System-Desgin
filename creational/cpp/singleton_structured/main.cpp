#include "database_connection.hpp"
#include "logger.hpp"
#include "serialized_singleton.hpp"
#include "bypasable_singleton.hpp"

int main() {
    std::cout << "=== Singleton Pattern Demo ===" << std::endl << std::endl;
    
    std::cout << "--- DatabaseConnection Example ---" << std::endl;
    DatabaseConnection& db1 = DatabaseConnection::getInstance();
    db1.executeQuery("SELECT * FROM users");
    
    DatabaseConnection& db2 = DatabaseConnection::getInstance();
    db2.executeQuery("SELECT * FROM products");
    
    std::cout << "Same instance? " << (&db1 == &db2 ? "Yes" : "No") << std::endl;
    std::cout << "Total queries: " << db1.getQueryCount() << std::endl << std::endl;
    
    std::cout << "--- Logger Example ---" << std::endl;
    Logger& logger1 = Logger::getInstance();
    logger1.log("Application started");
    
    Logger& logger2 = Logger::getInstance();
    logger2.log("User logged in");
    logger2.log("Processing request");
    
    std::cout << "Same instance? " << (&logger1 == &logger2 ? "Yes" : "No") << std::endl;
    std::cout << "Total logs: " << logger1.getLogCount() << std::endl << std::endl;
    
    std::cout << "--- SerializedSingleton Example ---" << std::endl;
    SerializedSingleton* s1 = SerializedSingleton::getInstance();
    s1->doWork();
    SerializedSingleton* s2 = SerializedSingleton::getInstance();
    std::cout << "Same instance? " << (s1 == s2 ? "Yes" : "No") << std::endl << std::endl;

    std::cout << "--- Bypassing Singleton Example ---" << std::endl;
    BypasableSingleton* b1 = BypasableSingleton::getInstance();
    BypasableSingleton* b2 = SingletonHacker::createNewInstance();
    
    std::cout << "Same instance? " << (b1 == b2 ? "Yes" : "No (Bypass Successful!)") << std::endl;
    
    return 0;
}
