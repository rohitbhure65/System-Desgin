#pragma once
#include "interfaces.hpp"
#include <map>

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
