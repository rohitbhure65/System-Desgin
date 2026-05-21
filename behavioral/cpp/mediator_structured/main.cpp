#include "interfaces.hpp"
#include "chat_room.hpp"
#include "air_traffic_control.hpp"
#include "smart_home.hpp"
#include <iostream>
#include <memory>

int main() {
    std::cout << "=== Mediator Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Chat Room
    std::cout << "--- Chat Room Example ---" << std::endl;
    
    auto chatRoom = std::make_shared<ChatRoom>();
    
    auto user1 = std::make_shared<User>(chatRoom, "Alice");
    auto user2 = std::make_shared<User>(chatRoom, "Bob");
    auto bot = std::make_shared<Bot>(chatRoom, "HelperBot");
    
    chatRoom->addUser(user1);
    chatRoom->addUser(user2);
    chatRoom->addUser(bot);
    
    std::cout << "\nAlice sends a message:" << std::endl;
    user1->send("Hello everyone!");
    
    std::cout << "\nBob sends a message:" << std::endl;
    user2->send("Hi Alice!");
    
    std::cout << std::endl;
    
    // Example 2: Air Traffic Control
    std::cout << "--- Air Traffic Control Example ---" << std::endl;
    
    auto controlTower = std::make_shared<ControlTower>();
    
    auto flight1 = std::make_shared<Aircraft>(controlTower, "AA123");
    auto flight2 = std::make_shared<Aircraft>(controlTower, "UA456");
    
    controlTower->registerAircraft(flight1);
    controlTower->registerAircraft(flight2);
    
    std::cout << "\nFlight AA123 requests takeoff:" << std::endl;
    controlTower->grantTakeoff("AA123");
    
    std::cout << "\nFlight UA456 requests landing:" << std::endl;
    controlTower->grantLanding("UA456");
    
    std::cout << std::endl;
    
    // Example 3: Smart Home System
    std::cout << "--- Smart Home System Example ---" << std::endl;
    
    auto homeHub = std::make_shared<HomeHub>();
    
    auto livingRoomLight = std::make_shared<SmartLight>(homeHub, "Living Room Light");
    auto bedroomLight = std::make_shared<SmartLight>(homeHub, "Bedroom Light");
    auto thermostat = std::make_shared<SmartThermostat>(homeHub, "Main Thermostat");
    
    homeHub->addDevice(livingRoomLight);
    homeHub->addDevice(bedroomLight);
    homeHub->addDevice(thermostat);
    
    std::cout << "\nTurning on thermostat (should trigger lights):" << std::endl;
    thermostat->turnOn();
    
    std::cout << "\nActivating away mode:" << std::endl;
    homeHub->activateAwayMode();
    
    std::cout << "\nActivating home mode:" << std::endl;
    homeHub->activateHomeMode();
    
    return 0;
}
