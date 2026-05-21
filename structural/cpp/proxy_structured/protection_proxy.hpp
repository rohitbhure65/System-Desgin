#pragma once
#include <string>
#include <memory>
#include <unordered_map>

class Database {
public:
    virtual ~Database() = default;
    virtual void query(const std::string& sql) = 0;
};

class RealDatabase : public Database {
public:
    void query(const std::string& sql) override {
        std::cout << "Executing query: " << sql << std::endl;
    }
};

class DatabaseProxy : public Database {
private:
    std::unique_ptr<RealDatabase> realDatabase;
    std::string currentUser;
    std::unordered_map<std::string, bool> permissions;
    
    bool hasPermission() {
        return permissions[currentUser];
    }
    
public:
    DatabaseProxy(const std::string& user) : currentUser(user) {
        permissions["admin"] = true;
        permissions["user"] = false;
        permissions["guest"] = false;
    }
    
    void query(const std::string& sql) override {
        if (hasPermission()) {
            if (!realDatabase) {
                realDatabase = std::make_unique<RealDatabase>();
            }
            realDatabase->query(sql);
        } else {
            std::cout << "Access denied: User '" << currentUser 
                      << "' does not have permission to execute queries" << std::endl;
        }
    }
    
    void setUser(const std::string& user) {
        currentUser = user;
    }
};
