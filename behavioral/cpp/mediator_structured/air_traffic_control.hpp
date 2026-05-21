#pragma once
#include "interfaces.hpp"
#include <map>

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
    }
    
    void requestLanding() {
        std::cout << flightNumber << " requesting landing clearance..." << std::endl;
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
