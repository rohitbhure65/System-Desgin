#pragma once
#include "interfaces.hpp"
#include "products.hpp"

class SimpleHouseBuilder : public HouseBuilder {
private:
    House house;
    
public:
    void buildFoundation() override { house.setFoundation("Concrete foundation"); }
    void buildStructure() override { house.setStructure("Wood frame structure"); }
    void buildRoof() override { house.setRoof("Asphalt shingle roof"); }
    void buildInterior() override { house.setInterior("Basic interior with drywall"); }
    void buildGarage() override { house.setGarage(false); }
    void buildGarden() override { house.setGarden(false); }
    void buildSwimmingPool() override { house.setSwimmingPool(false); }
    House getResult() override { return house; }
};

class LuxuryHouseBuilder : public HouseBuilder {
private:
    House house;
    
public:
    void buildFoundation() override { house.setFoundation("Reinforced concrete foundation with basement"); }
    void buildStructure() override { house.setStructure("Steel frame structure with brick exterior"); }
    void buildRoof() override { house.setRoof("Spanish tile roof with solar panels"); }
    void buildInterior() override { house.setInterior("Luxury interior with marble floors and custom cabinetry"); }
    void buildGarage() override { house.setGarage(true); }
    void buildGarden() override { house.setGarden(true); }
    void buildSwimmingPool() override { house.setSwimmingPool(true); }
    House getResult() override { return house; }
};

class ComputerBuilder {
private:
    Computer computer;
    
public:
    ComputerBuilder& setCpu(const std::string& cpu) { computer.setCpu(cpu); return *this; }
    ComputerBuilder& setGpu(const std::string& gpu) { computer.setGpu(gpu); return *this; }
    ComputerBuilder& setRam(int ram) { computer.setRam(ram); return *this; }
    ComputerBuilder& setStorage(int storage) { computer.setStorage(storage); return *this; }
    ComputerBuilder& addWifi() { computer.setWifi(true); return *this; }
    ComputerBuilder& addBluetooth() { computer.setBluetooth(true); return *this; }
    Computer build() { return computer; }
};
