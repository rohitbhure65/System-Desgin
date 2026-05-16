/*
 * ABSTRACT FACTORY DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Abstract Factory pattern provides an interface for creating families of related or dependent objects without specifying their concrete classes.
 * It's like a factory of factories.
 * 
 * WHY DOES IT EXIST?
 * - When you need to create families of related objects (e.g., UI components for different operating systems)
 * - When you want to ensure that created objects are compatible with each other
 * - When you want to provide a library of products without exposing their implementation details
 * - When you need to support multiple themes or platforms
 * 
 * WHEN TO USE IT?
 * - When a system should be independent of how its products are created, composed, and represented
 * - When a system should be configured with one of multiple families of products
 * - When the family of related product objects is designed to be used together, and you need to enforce this constraint
 * - When you want to provide a class library of products, and you want to reveal just their interfaces, not their implementations
 * - Common use cases: cross-platform UI components, database connectors for different DBMS, game development (different themes)
 * 
 * PROS:
 * - Ensures that products from the same family are compatible
 * - Hides the concrete classes from the client code
 * - Easy to introduce new product families without modifying existing code (Open/Closed Principle)
 * - Promotes consistency among products
 * 
 * CONS:
 * - Can be complex to implement due to many interfaces and classes
 * - Adding new products to existing families requires modifying all factory interfaces
 * - Can lead to excessive abstraction and indirection
 * - May be overkill for simple scenarios
 * 
 * REAL-WORLD ANALOGY:
 * Think of a furniture factory that produces different styles of furniture (Modern, Victorian, Rustic). Each style has its own family of products (chairs, tables, sofas). If you order a Modern chair, you want it to match with a Modern table. The abstract factory ensures that all furniture pieces you order belong to the same style family.
 */

#include <iostream>
#include <memory>
#include <string>

// Abstract Product A: Button interface
class Button {
public:
    virtual ~Button() = default;
    virtual void click() = 0;
    virtual void render() = 0;
    virtual std::string getName() const = 0;
};

// Abstract Product B: Checkbox interface
class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void check() = 0;
    virtual void render() = 0;
    virtual std::string getName() const = 0;
};

// Concrete Product A1: Windows Button
class WindowsButton : public Button {
public:
    void click() override {
        std::cout << "Windows button clicked!" << std::endl;
    }
    
    void render() override {
        std::cout << "Rendering Windows-style button..." << std::endl;
    }
    
    std::string getName() const override {
        return "Windows Button";
    }
};

// Concrete Product B1: Windows Checkbox
class WindowsCheckbox : public Checkbox {
public:
    void check() override {
        std::cout << "Windows checkbox checked!" << std::endl;
    }
    
    void render() override {
        std::cout << "Rendering Windows-style checkbox..." << std::endl;
    }
    
    std::string getName() const override {
        return "Windows Checkbox";
    }
};

// Concrete Product A2: Mac Button
class MacButton : public Button {
public:
    void click() override {
        std::cout << "Mac button clicked!" << std::endl;
    }
    
    void render() override {
        std::cout << "Rendering Mac-style button..." << std::endl;
    }
    
    std::string getName() const override {
        return "Mac Button";
    }
};

// Concrete Product B2: Mac Checkbox
class MacCheckbox : public Checkbox {
public:
    void check() override {
        std::cout << "Mac checkbox checked!" << std::endl;
    }
    
    void render() override {
        std::cout << "Rendering Mac-style checkbox..." << std::endl;
    }
    
    std::string getName() const override {
        return "Mac Checkbox";
    }
};

// Abstract Factory interface - declares methods for creating each abstract product
class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
};

// Concrete Factory 1: Windows Factory
// Creates Windows-specific UI components
class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<WindowsCheckbox>();
    }
};

// Concrete Factory 2: Mac Factory
// Creates Mac-specific UI components
class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<MacCheckbox>();
    }
};

// Client class that uses the abstract factory
// The client doesn't know which concrete factory is being used
class Application {
private:
    std::unique_ptr<Button> button;
    std::unique_ptr<Checkbox> checkbox;
    
public:
    // Constructor takes a factory and creates UI components
    Application(std::unique_ptr<GUIFactory> factory) {
        button = factory->createButton();
        checkbox = factory->createCheckbox();
    }
    
    // Business logic that uses the products
    void renderUI() {
        std::cout << "Rendering UI components..." << std::endl;
        std::cout << "Button: " << button->getName() << std::endl;
        std::cout << "Checkbox: " << checkbox->getName() << std::endl;
        
        button->render();
        checkbox->render();
    }
    
    void interact() {
        std::cout << "\nUser interaction..." << std::endl;
        button->click();
        checkbox->check();
    }
};

// Another example: Database Abstract Factory
// Shows how Abstract Factory can be used for database connections

// Abstract Product: Database Connection
class DatabaseConnection {
public:
    virtual ~DatabaseConnection() = default;
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void executeQuery(const std::string& query) = 0;
};

// Abstract Product: Database Command
class DatabaseCommand {
public:
    virtual ~DatabaseCommand() = default;
    virtual void execute() = 0;
};

// Concrete Products: MySQL
class MySQLConnection : public DatabaseConnection {
public:
    void connect() override {
        std::cout << "Connecting to MySQL database..." << std::endl;
    }
    
    void disconnect() override {
        std::cout << "Disconnecting from MySQL database..." << std::endl;
    }
    
    void executeQuery(const std::string& query) override {
        std::cout << "Executing MySQL query: " << query << std::endl;
    }
};

class MySQLCommand : public DatabaseCommand {
private:
    std::string command;
    
public:
    MySQLCommand(const std::string& cmd) : command(cmd) {}
    
    void execute() override {
        std::cout << "Executing MySQL command: " << command << std::endl;
    }
};

// Concrete Products: PostgreSQL
class PostgreSQLConnection : public DatabaseConnection {
public:
    void connect() override {
        std::cout << "Connecting to PostgreSQL database..." << std::endl;
    }
    
    void disconnect() override {
        std::cout << "Disconnecting from PostgreSQL database..." << std::endl;
    }
    
    void executeQuery(const std::string& query) override {
        std::cout << "Executing PostgreSQL query: " << query << std::endl;
    }
};

class PostgreSQLCommand : public DatabaseCommand {
private:
    std::string command;
    
public:
    PostgreSQLCommand(const std::string& cmd) : command(cmd) {}
    
    void execute() override {
        std::cout << "Executing PostgreSQL command: " << command << std::endl;
    }
};

// Abstract Factory for Database
class DatabaseFactory {
public:
    virtual ~DatabaseFactory() = default;
    virtual std::unique_ptr<DatabaseConnection> createConnection() = 0;
    virtual std::unique_ptr<DatabaseCommand> createCommand(const std::string& cmd) = 0;
};

// Concrete Factory: MySQL
class MySQLFactory : public DatabaseFactory {
public:
    std::unique_ptr<DatabaseConnection> createConnection() override {
        return std::make_unique<MySQLConnection>();
    }
    
    std::unique_ptr<DatabaseCommand> createCommand(const std::string& cmd) override {
        return std::make_unique<MySQLCommand>(cmd);
    }
};

// Concrete Factory: PostgreSQL
class PostgreSQLFactory : public DatabaseFactory {
public:
    std::unique_ptr<DatabaseConnection> createConnection() override {
        return std::make_unique<PostgreSQLConnection>();
    }
    
    std::unique_ptr<DatabaseCommand> createCommand(const std::string& cmd) override {
        return std::make_unique<PostgreSQLCommand>(cmd);
    }
};

int main() {
    std::cout << "=== Abstract Factory Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: GUI Components
    std::cout << "--- GUI Components Example ---" << std::endl;
    
    // Create Windows UI
    std::cout << "\nCreating Windows UI:" << std::endl;
    auto windowsFactory = std::make_unique<WindowsFactory>();
    Application windowsApp(std::move(windowsFactory));
    windowsApp.renderUI();
    windowsApp.interact();
    
    // Create Mac UI
    std::cout << "\nCreating Mac UI:" << std::endl;
    auto macFactory = std::make_unique<MacFactory>();
    Application macApp(std::move(macFactory));
    macApp.renderUI();
    macApp.interact();
    
    // Example 2: Database Connections
    std::cout << "\n\n--- Database Connections Example ---" << std::endl;
    
    // MySQL
    std::cout << "\nUsing MySQL:" << std::endl;
    auto mysqlFactory = std::make_unique<MySQLFactory>();
    auto mysqlConnection = mysqlFactory->createConnection();
    auto mysqlCommand = mysqlFactory->createCommand("CREATE TABLE users (id INT)");
    
    mysqlConnection->connect();
    mysqlConnection->executeQuery("SELECT * FROM users");
    mysqlCommand->execute();
    mysqlConnection->disconnect();
    
    // PostgreSQL
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
