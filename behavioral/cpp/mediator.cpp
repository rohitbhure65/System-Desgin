/*
 * MEDIATOR DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Mediator pattern defines an object that encapsulates how a set of objects interact.
 * It promotes loose coupling by preventing objects from referring to each other explicitly.
 * 
 * WHY DOES IT EXIST?
 * - When you want to reduce the chaotic dependencies between objects
 * - When you want to centralize complex communications and control logic between related objects
 * - When you want to reuse the interaction logic without duplicating it across multiple objects
 * 
 * WHEN TO USE IT?
 * - When a set of objects communicate in well-defined but complex ways
 * - When you want to customize a behavior that's distributed between several objects without subclassing
 * - When you have many objects that need to interact with each other
 * - Common use cases: chat rooms, air traffic control, GUI frameworks, auction systems
 * 
 * PROS:
 * - Single Responsibility Principle (extracts communication logic to a separate class)
 * - Open/Closed Principle (can add new colleagues without changing the mediator)
 * - Reduces coupling between colleagues
 * - Simplifies object interactions
 * 
 * CONS:
 * - The mediator can become a monolith (god object) if not carefully designed
 * - Can make the system harder to understand due to indirect communication
 * - May reduce performance due to indirection
 * - Can be overkill for simple interactions
 * 
 * REAL-WORLD ANALOGY:
 * Think of an air traffic control tower. Planes (colleagues) don't communicate directly with each other - they all communicate through the tower (mediator). The tower coordinates takeoffs, landings, and routes, ensuring planes don't collide. This centralizes the coordination logic and prevents planes from needing to know about each other.
 */

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>

// Mediator interface - declares the communication interface
class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void sendMessage(const std::string& message, const std::string& sender) = 0;
};

// Colleague interface - declares the interface for communicating with the mediator
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

// Concrete Colleague 1
class User : public Colleague {
public:
    User(std::shared_ptr<Mediator> mediator, const std::string& name)
        : Colleague(mediator, name) {}
    
    void receive(const std::string& message) override {
        std::cout << name << " received: " << message << std::endl;
    }
};

// Concrete Colleague 2
class Bot : public Colleague {
public:
    Bot(std::shared_ptr<Mediator> mediator, const std::string& name)
        : Colleague(mediator, name) {}
    
    void receive(const std::string& message) override {
        std::cout << name << " received: " << message << std::endl;
        // Bot can auto-reply
        send("Auto-reply: Thanks for your message!");
    }
};

// Concrete Mediator
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

// Example 2: Air Traffic Control
// Shows how Mediator can coordinate complex interactions

class Aircraft {
protected:
    std::shared_ptr<Mediator> controlTower;
    std::string flightNumber;
    int altitude;
    int speed;
    
public:
    Aircraft(std::shared_ptr<Mediator> tower, const std::string& flightNumber)
        : controlTower(tower), flightNumber(flightNumber), altitude(0), speed(0) {}
    
    virtual ~Aircraft() = default;
    
    void requestTakeoff() {
        std::cout << flightNumber << " requesting takeoff clearance..." << std::endl;
        // In real implementation, would send to mediator
    }
    
    void requestLanding() {
        std::cout << flightNumber << " requesting landing clearance..." << std::endl;
        // In real implementation, would send to mediator
    }
    
    void setAltitude(int alt) {
        altitude = alt;
        std::cout << flightNumber << " at altitude " << altitude << " feet" << std::endl;
    }
    
    std::string getFlightNumber() const {
        return flightNumber;
    }
};

class ControlTower : public Mediator {
private:
    std::map<std::string, std::shared_ptr<Aircraft>> aircrafts;
    
public:
    void registerAircraft(std::shared_ptr<Aircraft> aircraft) {
        aircrafts[aircraft->getFlightNumber()] = aircraft;
    }
    
    void sendMessage(const std::string& message, const std::string& sender) override {
        // Simplified for demo
        std::cout << "Control Tower: " << message << " from " << sender << std::endl;
    }
    
    void grantTakeoff(const std::string& flightNumber) {
        std::cout << "Control Tower: Takeoff granted to " << flightNumber << std::endl;
        if (aircrafts.find(flightNumber) != aircrafts.end()) {
            aircrafts[flightNumber]->setAltitude(10000);
        }
    }
    
    void grantLanding(const std::string& flightNumber) {
        std::cout << "Control Tower: Landing granted to " << flightNumber << std::endl;
        if (aircrafts.find(flightNumber) != aircrafts.end()) {
            aircrafts[flightNumber]->setAltitude(0);
        }
    }
};

// Example 3: Smart Home System
// Shows how Mediator can coordinate home automation

class SmartDevice {
protected:
    std::shared_ptr<Mediator> homeHub;
    std::string deviceName;
    bool isOn;
    
public:
    SmartDevice(std::shared_ptr<Mediator> hub, const std::string& name)
        : homeHub(hub), deviceName(name), isOn(false) {}
    
    virtual ~SmartDevice() = default;
    
    void turnOn() {
        isOn = true;
        std::cout << deviceName << " turned ON" << std::endl;
        homeHub->sendMessage(deviceName + " turned ON", deviceName);
    }
    
    void turnOff() {
        isOn = false;
        std::cout << deviceName << " turned OFF" << std::endl;
        homeHub->sendMessage(deviceName + " turned OFF", deviceName);
    }
    
    std::string getName() const {
        return deviceName;
    }
    
    bool getStatus() const {
        return isOn;
    }
};

class SmartLight : public SmartDevice {
public:
    SmartLight(std::shared_ptr<Mediator> hub, const std::string& name)
        : SmartDevice(hub, name) {}
};

class SmartThermostat : public SmartDevice {
private:
    int temperature;
    
public:
    SmartThermostat(std::shared_ptr<Mediator> hub, const std::string& name)
        : SmartDevice(hub, name), temperature(70) {}
    
    void setTemperature(int temp) {
        temperature = temp;
        std::cout << getName() << " set to " << temperature << "°F" << std::endl;
    }
    
    int getTemperature() const {
        return temperature;
    }
};

class HomeHub : public Mediator {
private:
    std::map<std::string, std::shared_ptr<SmartDevice>> devices;
    
public:
    void addDevice(std::shared_ptr<SmartDevice> device) {
        devices[device->getName()] = device;
    }
    
    void sendMessage(const std::string& message, const std::string& sender) override {
        std::cout << "Home Hub: " << message << std::endl;
        
        // Example logic: if thermostat turns on, turn on lights
        if (sender.find("Thermostat") != std::string::npos && message.find("turned ON") != std::string::npos) {
            for (const auto& [name, device] : devices) {
                if (name.find("Light") != std::string::npos && !device->getStatus()) {
                    device->turnOn();
                }
            }
        }
    }
    
    void activateAwayMode() {
        std::cout << "Home Hub: Activating away mode..." << std::endl;
        for (const auto& [name, device] : devices) {
            if (device->getStatus()) {
                device->turnOff();
            }
        }
    }
    
    void activateHomeMode() {
        std::cout << "Home Hub: Activating home mode..." << std::endl;
        for (const auto& [name, device] : devices) {
            if (name.find("Light") != std::string::npos) {
                device->turnOn();
            }
        }
    }
};

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
