#pragma once
#include <iostream>
#include <string>

class House {
private:
    std::string foundation;
    std::string structure;
    std::string roof;
    std::string interior;
    bool hasGarage;
    bool hasGarden;
    bool hasSwimmingPool;
    
public:
    House() : hasGarage(false), hasGarden(false), hasSwimmingPool(false) {}
    
    void setFoundation(const std::string& f) { foundation = f; }
    void setStructure(const std::string& s) { structure = s; }
    void setRoof(const std::string& r) { roof = r; }
    void setInterior(const std::string& i) { interior = i; }
    void setGarage(bool g) { hasGarage = g; }
    void setGarden(bool g) { hasGarden = g; }
    void setSwimmingPool(bool s) { hasSwimmingPool = s; }
    
    void display() const {
        std::cout << "=== House Details ===" << std::endl;
        std::cout << "Foundation: " << foundation << std::endl;
        std::cout << "Structure: " << structure << std::endl;
        std::cout << "Roof: " << roof << std::endl;
        std::cout << "Interior: " << interior << std::endl;
        std::cout << "Garage: " << (hasGarage ? "Yes" : "No") << std::endl;
        std::cout << "Garden: " << (hasGarden ? "Yes" : "No") << std::endl;
        std::cout << "Swimming Pool: " << (hasSwimmingPool ? "Yes" : "No") << std::endl;
        std::cout << "====================" << std::endl;
    }
};

class Computer {
private:
    std::string cpu;
    std::string gpu;
    int ram;
    int storage;
    bool hasWifi;
    bool hasBluetooth;
    
public:
    Computer() : ram(8), storage(256), hasWifi(false), hasBluetooth(false) {}
    
    void setCpu(const std::string& c) { cpu = c; }
    void setGpu(const std::string& g) { gpu = g; }
    void setRam(int r) { ram = r; }
    void setStorage(int s) { storage = s; }
    void setWifi(bool w) { hasWifi = w; }
    void setBluetooth(bool b) { hasBluetooth = b; }
    
    void display() const {
        std::cout << "=== Computer Specs ===" << std::endl;
        std::cout << "CPU: " << cpu << std::endl;
        std::cout << "GPU: " << gpu << std::endl;
        std::cout << "RAM: " << ram << " GB" << std::endl;
        std::cout << "Storage: " << storage << " GB" << std::endl;
        std::cout << "WiFi: " << (hasWifi ? "Yes" : "No") << std::endl;
        std::cout << "Bluetooth: " << (hasBluetooth ? "Yes" : "No") << std::endl;
        std::cout << "=====================" << std::endl;
    }
};
