#include "interfaces.hpp"
#include "concrete_factories.hpp"
#include "client.hpp"

int main() {
    std::cout << "=== Abstract Factory Pattern Demo ===" << std::endl << std::endl;
    
    std::cout << "--- GUI Components Example ---" << std::endl;
    
    std::cout << "\nCreating Windows UI:" << std::endl;
    auto windowsFactory = std::make_unique<WindowsFactory>();
    Application windowsApp(std::move(windowsFactory));
    windowsApp.renderUI();
    windowsApp.interact();
    
    std::cout << "\nCreating Mac UI:" << std::endl;
    auto macFactory = std::make_unique<MacFactory>();
    Application macApp(std::move(macFactory));
    macApp.renderUI();
    macApp.interact();
    
    std::cout << "\n\n--- Database Connections Example ---" << std::endl;
    
    std::cout << "\nUsing MySQL:" << std::endl;
    auto mysqlFactory = std::make_unique<MySQLFactory>();
    auto mysqlConnection = mysqlFactory->createConnection();
    auto mysqlCommand = mysqlFactory->createCommand("CREATE TABLE users (id INT)");
    
    mysqlConnection->connect();
    mysqlConnection->executeQuery("SELECT * FROM users");
    mysqlCommand->execute();
    mysqlConnection->disconnect();
    
    std::cout << "\nUsing PostgreSQL:" << std::endl;
    auto postgresFactory = std::make_unique<PostgreSQLFactory>();
    auto postgresConnection = postgresFactory->createConnection();
    auto postgresCommand = postgresFactory->createCommand("CREATE TABLE products (id INT)");
    
    postgresConnection->connect();
    postgresConnection->executeQuery("SELECT * FROM products");
    postgresCommand->execute();
    postgresConnection->disconnect();
    
    return 0;
}
