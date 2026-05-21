#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

class Subject {
protected:
    std::vector<std::shared_ptr<Observer>> observers;
    
public:
    virtual ~Subject() = default;
    
    void attach(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
        std::cout << "Attached an observer" << std::endl;
    }
    
    void detach(std::shared_ptr<Observer> observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
            std::cout << "Detached an observer" << std::endl;
        }
    }
    
    void notify(const std::string& message) {
        std::cout << "Notifying observers..." << std::endl;
        for (const auto& observer : observers) {
            observer->update(message);
        }
    }
};
