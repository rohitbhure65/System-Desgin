#pragma once
#include "interfaces.hpp"
#include <string>

class YouTubeChannel : public Subject {
private:
    std::string channelName;
    
public:
    YouTubeChannel(const std::string& name) : channelName(name) {}
    
    void uploadVideo(const std::string& videoTitle) {
        std::cout << "\n" << channelName << " uploaded: " << videoTitle << std::endl;
        notify("New video: " + videoTitle);
    }
    
    void goLive(const std::string& streamTitle) {
        std::cout << "\n" << channelName << " is live: " << streamTitle << std::endl;
        notify("Live stream started: " + streamTitle);
    }
};

class Subscriber : public Observer {
private:
    std::string name;
    
public:
    Subscriber(const std::string& name) : name(name) {}
    
    void update(const std::string& message) override {
        std::cout << "  " << name << " received notification: " << message << std::endl;
    }
};

class NotificationService : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "  [NotificationService] Push notification sent: " << message << std::endl;
    }
};
