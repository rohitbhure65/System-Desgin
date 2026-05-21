#pragma once
#include "interfaces.hpp"
#include <map>

class User : public Colleague {
public:
    User(std::shared_ptr<Mediator> mediator, const std::string& name)
        : Colleague(mediator, name) {}
    
    void receive(const std::string& message) override {
        std::cout << name << " received: " << message << std::endl;
    }
};

class Bot : public Colleague {
public:
    Bot(std::shared_ptr<Mediator> mediator, const std::string& name)
        : Colleague(mediator, name) {}
    
    void receive(const std::string& message) override {
        std::cout << name << " received: " << message << std::endl;
        send("Auto-reply: Thanks for your message!");
    }
};

class ChatRoom : public Mediator {
private:
    std::map<std::string, std::shared_ptr<Colleague>> colleagues;
    
public:
    void addUser(std::shared_ptr<Colleague> colleague) {
        colleagues[colleague->getName()] = colleague;
    }
    
    void sendMessage(const std::string& message, const std::string& sender) override {
        std::cout << sender << " sends: " << message << std::endl;
        for (const auto& [name, colleague] : colleagues) {
            if (name != sender) {
                colleague->receive(message);
            }
        }
    }
};
