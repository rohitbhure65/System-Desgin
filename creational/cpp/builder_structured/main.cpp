#include "director.hpp"
#include "builders.hpp"

int main() {
    std::cout << "=== Builder Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Classic Builder with Director
    std::cout << "--- Classic Builder with Director ---" << std::endl;
    
    ConstructionDirector director;
    
    // Build a simple house
    std::cout << "\nBuilding Simple House:" << std::endl;
    SimpleHouseBuilder simpleBuilder;
    director.setBuilder(&simpleBuilder);
    director.buildBasicHouse();
    House simpleHouse = simpleBuilder.getResult();
    simpleHouse.display();
    
    // Build a luxury house
    std::cout << "\nBuilding Luxury House:" << std::endl;
    LuxuryHouseBuilder luxuryBuilder;
    director.setBuilder(&luxuryBuilder);
    director.buildFullHouse();
    House luxuryHouse = luxuryBuilder.getResult();
    luxuryHouse.display();
    
    // Build a custom house
    std::cout << "\nBuilding Custom House (with garage and garden, no pool):" << std::endl;
    SimpleHouseBuilder customBuilder;
    director.setBuilder(&customBuilder);
    director.buildCustomHouse(true, true, false);
    House customHouse = customBuilder.getResult();
    customHouse.display();
    
    // Example 2: Fluent Builder (method chaining)
    std::cout << "\n--- Fluent Builder (Method Chaining) ---" << std::endl;
    
    std::cout << "\nBuilding Gaming Computer:" << std::endl;
    Computer gamingComputer = ComputerBuilder()
        .setCpu("Intel Core i9-13900K")
        .setGpu("NVIDIA RTX 4090")
        .setRam(32)
        .setStorage(1000)
        .addWifi()
        .addBluetooth()
        .build();
    gamingComputer.display();
    
    std::cout << "\nBuilding Office Computer:" << std::endl;
    Computer officeComputer = ComputerBuilder()
        .setCpu("Intel Core i5-13400")
        .setGpu("Integrated Graphics")
        .setRam(16)
        .setStorage(512)
        .addWifi()
        .build();
    officeComputer.display();
    
    return 0;
}
