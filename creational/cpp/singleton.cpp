/*
 * SINGLETON DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Singleton pattern ensures a class has only one instance and provides a global point of access to that instance.
 * 
 * WHY DOES IT EXIST?
 * - Some resources should only exist once (database connections, logging services, configuration managers)
 * - Prevents multiple instances from causing conflicts or inconsistent state
 * - Provides controlled access to the sole instance
 * 
 * WHEN TO USE IT?
 * - When exactly one instance of a class is needed to coordinate actions across the system
 * - When the sole instance should be extensible by subclassing, and clients should be able to use an extended instance without modifying their code
 * - Common use cases: database connection pools, logging services, configuration managers, thread pools, caches
 * 
 * PROS:
 * - Controlled access to the sole instance
 * - Reduced namespace pollution (compared to global variables)
 * - Can be subclassed
 * - Can be lazy-loaded (created only when first needed)
 * 
 * CONS:
 * - Violates Single Responsibility Principle (handles both its business logic and instance creation)
 * - Can hide dependencies (making code harder to test)
 * - Global state can lead to unexpected behavior in multi-threaded environments
 * - Difficult to unit test due to global state
 * 
 * REAL-WORLD ANALOGY:
 * Think of a government - there's only one president or prime minister at a time. Everyone who needs to interact with the head of state goes through the same single instance. You can't have two presidents simultaneously making conflicting decisions.
 */

#include <iostream>
#include <memory>
#include <mutex>

// Thread-safe Singleton class using Meyer's Singleton pattern
class DatabaseConnection {
private:
    // Private constructor to prevent instantiation from outside
    DatabaseConnection() {
        std::cout << "DatabaseConnection: Initializing connection..." << std::endl;
        // Simulate connection setup
        isConnected = true;
    }
    
    // Private destructor to prevent deletion from outside
    ~DatabaseConnection() {
        std::cout << "DatabaseConnection: Closing connection..." << std::endl;
        isConnected = false;
    }
    
    // Delete copy constructor and assignment operator
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
    
    bool isConnected;
    int queryCount = 0;

public:
    // Static method to get the single instance
    // This is thread-safe in C++11 and later (Meyer's Singleton)
    static DatabaseConnection& getInstance() {
        // Static local variable is created only once, on first call
        // This is thread-safe in C++11 and later
        static DatabaseConnection instance;
        return instance;
    }
    
    // Business logic methods
    void executeQuery(const std::string& query) {
        if (isConnected) {
            queryCount++;
            std::cout << "Executing query #" << queryCount << ": " << query << std::endl;
        } else {
            std::cout << "Error: Not connected to database" << std::endl;
        }
    }
    
    int getQueryCount() const {
        return queryCount;
    }
    
    bool getConnectionStatus() const {
        return isConnected;
    }
};

// Alternative implementation using std::call_once for explicit thread safety
// This is useful when you need more control over initialization
class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::once_flag initFlag;
    
    Logger() {
        std::cout << "Logger: Initializing logger..." << std::endl;
    }
    
    ~Logger() {
        std::cout << "Logger: Destroying logger..." << std::endl;
    }
    
    // Delete copy constructor and assignment operator
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
    
    int getLogCount() const {
        return logCount;
    }
};

std::unique_ptr<Logger> Logger::instance = nullptr;
std::once_flag Logger::initFlag;

// Example 3: Double-Checked Locking (Explicit Serialized Access)
// This pattern was common before C++11. It uses a mutex to ensure
// that only one thread creates the instance.
class SerializedSingleton {
private:
    static SerializedSingleton* instance;
    static std::mutex mutex;

    SerializedSingleton() {
        std::cout << "SerializedSingleton: Instance created." << std::endl;
    }

public:
    static SerializedSingleton* getInstance() {
        // First check (no locking for performance)
        if (instance == nullptr) {
            // Locking for thread safety
            std::lock_guard<std::mutex> lock(mutex);
            // Second check (to prevent race condition)
            if (instance == nullptr) {
                instance = new SerializedSingleton();
            }
        }
        return instance;
    }
    
    void doWork() {
        std::cout << "SerializedSingleton is working..." << std::endl;
    }
};

SerializedSingleton* SerializedSingleton::instance = nullptr;
std::mutex SerializedSingleton::mutex;

// Example 4: Bypassing Singleton
// Demonstrates how a singleton can be "broken" using pointer hacking
// or other techniques.
class BypasableSingleton {
private:
    static BypasableSingleton* instance;
    BypasableSingleton() {
        std::cout << "BypasableSingleton: Instance created." << std::endl;
    }

public:
    static BypasableSingleton* getInstance() {
        if (!instance) instance = new BypasableSingleton();
        return instance;
    }
};
BypasableSingleton* BypasableSingleton::instance = nullptr;

int main() {
    std::cout << "=== Singleton Pattern Demo ===" << std::endl << std::endl;
    
    // Using Meyer's Singleton (DatabaseConnection)
    std::cout << "--- DatabaseConnection Example ---" << std::endl;
    
    // Get the singleton instance
    DatabaseConnection& db1 = DatabaseConnection::getInstance();
    db1.executeQuery("SELECT * FROM users");
    
    // Get the same instance again
    DatabaseConnection& db2 = DatabaseConnection::getInstance();
    db2.executeQuery("SELECT * FROM products");
    
    // Verify they are the same instance
    std::cout << "Same instance? " << (&db1 == &db2 ? "Yes" : "No") << std::endl;
    std::cout << "Total queries: " << db1.getQueryCount() << std::endl << std::endl;
    
    // Using std::call_once Singleton (Logger)
    std::cout << "--- Logger Example ---" << std::endl;
    
    Logger& logger1 = Logger::getInstance();
    logger1.log("Application started");
    
    Logger& logger2 = Logger::getInstance();
    logger2.log("User logged in");
    logger2.log("Processing request");
    
    std::cout << "Same instance? " << (&logger1 == &logger2 ? "Yes" : "No") << std::endl;
    std::cout << "Total logs: " << logger1.getLogCount() << std::endl << std::endl;
    
    // Using Double-Checked Locking
    std::cout << "--- SerializedSingleton Example ---" << std::endl;
    SerializedSingleton* s1 = SerializedSingleton::getInstance();
    s1->doWork();
    SerializedSingleton* s2 = SerializedSingleton::getInstance();
    std::cout << "Same instance? " << (s1 == s2 ? "Yes" : "No") << std::endl << std::endl;

    // Bypassing Singleton
    std::cout << "--- Bypassing Singleton Example ---" << std::endl;
    BypasableSingleton* b1 = BypasableSingleton::getInstance();
    
    // Bypass using 'new' is impossible because constructor is private.
    // But we can bypass using "Placement New" or Hacking with Pointers if we know the memory layout.
    // Or simpler: Using reflection (if available) or Friend classes.
    
    std::cout << "Ways to bypass in C++:" << std::endl;
    std::cout << "1. Friend classes/functions can access private constructor." << std::endl;
    std::cout << "2. Pointer hacking (casting to access private members)." << std::endl;
    std::cout << "3. Serialization/Deserialization (manually rebuilding the object)." << std::endl;

    return 0;
}
