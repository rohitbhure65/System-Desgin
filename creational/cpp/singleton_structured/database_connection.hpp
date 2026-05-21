#pragma once
#include <iostream>
#include <string>

class DatabaseConnection {
private:
    DatabaseConnection() {
        std::cout << "DatabaseConnection: Initializing connection..." << std::endl;
        isConnected = true;
    }
    ~DatabaseConnection() {
        std::cout << "DatabaseConnection: Closing connection..." << std::endl;
        isConnected = false;
    }
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
    
    bool isConnected;
    int queryCount = 0;

public:
    static DatabaseConnection& getInstance() {
        static DatabaseConnection instance;
        return instance;
    }
    
    void executeQuery(const std::string& query) {
        if (isConnected) {
            queryCount++;
            std::cout << "Executing query #" << queryCount << ": " << query << std::endl;
        } else {
            std::cout << "Error: Not connected to database" << std::endl;
        }
    }
    
    int getQueryCount() const { return queryCount; }
    bool getConnectionStatus() const { return isConnected; }
};
