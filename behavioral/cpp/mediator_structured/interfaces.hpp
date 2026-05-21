#pragma once
#include <string>
#include <memory>

class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void sendMessage(const std::string& message, const std::string& sender) = 0;
};

class Colleague {
protected:
    std::shared_ptr<Mediator> mediator;
    std::string name;
    
public:
    Colleague(std::shared_ptr<Mediator> mediator, const std::string& name)
        : mediator(mediator), name(name) {}
    
    virtual ~Colleague() = default;
    
    virtual void send(const std::string& message) {
        mediator->sendMessage(message, name);
    }
    
    virtual void receive(const std::string& message) = 0;
    
    std::string getName() const {
        return name;
    }
};
