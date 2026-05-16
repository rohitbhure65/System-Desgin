/*
 * BUILDER DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Builder pattern separates the construction of a complex object from its representation, allowing the same construction process to create different representations.
 * It constructs complex objects step by step.
 * 
 * WHY DOES IT EXIST?
 * - When you need to create complex objects with many optional parameters
 * - When you want to separate the construction logic from the object's representation
 * - When you need to create objects in a step-by-step fashion
 * - When you want to provide different representations for the same construction process
 * 
 * WHEN TO USE IT?
 * - When the algorithm for creating a complex object should be independent of the parts that make up the object and how they're assembled
 * - When the construction process must allow different representations for the object that's constructed
 * - When you want to construct objects with many optional parameters without using a telescoping constructor
 * - Common use cases: building complex documents, SQL query builders, HTML/XML generators, configuration objects
 * 
 * PROS:
 * - Allows you to construct complex objects step by step
 * - Provides fine-grained control over the construction process
 * - Can reuse the same construction process to create different representations
 * - Single Responsibility Principle (complex construction code is isolated from business logic)
 * - More readable than telescoping constructors
 * 
 * CONS:
 * - Increases overall code complexity
 * - Requires creating a separate Builder class for each product
 * - May not be necessary for simple objects
 * - Can lead to code duplication if not carefully designed
 * 
 * REAL-WORLD ANALOGY:
 * Think of ordering a custom pizza. You don't just say "give me a pizza" - you specify the crust, sauce, cheese, and toppings step by step. The pizza builder (chef) takes your specifications and constructs the pizza. You can use the same process to create different types of pizzas (vegetarian, meat lover's, etc.) by choosing different options at each step.
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Product class - the complex object being built
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
    
    // Setter methods for builder to use
    void setFoundation(const std::string& f) { foundation = f; }
    void setStructure(const std::string& s) { structure = s; }
    void setRoof(const std::string& r) { roof = r; }
    void setInterior(const std::string& i) { interior = i; }
    void setGarage(bool g) { hasGarage = g; }
    void setGarden(bool g) { hasGarden = g; }
    void setSwimmingPool(bool s) { hasSwimmingPool = s; }
    
    // Display the house details
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

// Builder interface - defines the steps to build the product
class HouseBuilder {
public:
    virtual ~HouseBuilder() = default;
    
    virtual void buildFoundation() = 0;
    virtual void buildStructure() = 0;
    virtual void buildRoof() = 0;
    virtual void buildInterior() = 0;
    virtual void buildGarage() = 0;
    virtual void buildGarden() = 0;
    virtual void buildSwimmingPool() = 0;
    
    virtual House getResult() = 0;
};

// Concrete Builder 1: Simple House Builder
class SimpleHouseBuilder : public HouseBuilder {
private:
    House house;
    
public:
    void buildFoundation() override {
        house.setFoundation("Concrete foundation");
    }
    
    void buildStructure() override {
        house.setStructure("Wood frame structure");
    }
    
    void buildRoof() override {
        house.setRoof("Asphalt shingle roof");
    }
    
    void buildInterior() override {
        house.setInterior("Basic interior with drywall");
    }
    
    void buildGarage() override {
        house.setGarage(false);
    }
    
    void buildGarden() override {
        house.setGarden(false);
    }
    
    void buildSwimmingPool() override {
        house.setSwimmingPool(false);
    }
    
    House getResult() override {
        return house;
    }
};

// Concrete Builder 2: Luxury House Builder
class LuxuryHouseBuilder : public HouseBuilder {
private:
    House house;
    
public:
    void buildFoundation() override {
        house.setFoundation("Reinforced concrete foundation with basement");
    }
    
    void buildStructure() override {
        house.setStructure("Steel frame structure with brick exterior");
    }
    
    void buildRoof() override {
        house.setRoof("Spanish tile roof with solar panels");
    }
    
    void buildInterior() override {
        house.setInterior("Luxury interior with marble floors and custom cabinetry");
    }
    
    void buildGarage() override {
        house.setGarage(true);
    }
    
    void buildGarden() override {
        house.setGarden(true);
    }
    
    void buildSwimmingPool() override {
        house.setSwimmingPool(true);
    }
    
    House getResult() override {
        return house;
    }
};

// Director class - orchestrates the construction process
// The director knows the construction algorithm but doesn't know the details
class ConstructionDirector {
private:
    HouseBuilder* builder;
    
public:
    void setBuilder(HouseBuilder* b) {
        builder = b;
    }
    
    // Construct a basic house
    void buildBasicHouse() {
        builder->buildFoundation();
        builder->buildStructure();
        builder->buildRoof();
        builder->buildInterior();
    }
    
    // Construct a full-featured house
    void buildFullHouse() {
        builder->buildFoundation();
        builder->buildStructure();
        builder->buildRoof();
        builder->buildInterior();
        builder->buildGarage();
        builder->buildGarden();
        builder->buildSwimmingPool();
    }
    
    // Construct a custom house
    void buildCustomHouse(bool withGarage, bool withGarden, bool withPool) {
        builder->buildFoundation();
        builder->buildStructure();
        builder->buildRoof();
        builder->buildInterior();
        if (withGarage) builder->buildGarage();
        if (withGarden) builder->buildGarden();
        if (withPool) builder->buildSwimmingPool();
    }
};

// Alternative: Fluent Builder pattern (method chaining)
// This is a common variation where the builder returns itself for chaining
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

class ComputerBuilder {
private:
    Computer computer;
    
public:
    ComputerBuilder& setCpu(const std::string& cpu) {
        computer.setCpu(cpu);
        return *this;
    }
    
    ComputerBuilder& setGpu(const std::string& gpu) {
        computer.setGpu(gpu);
        return *this;
    }
    
    ComputerBuilder& setRam(int ram) {
        computer.setRam(ram);
        return *this;
    }
    
    ComputerBuilder& setStorage(int storage) {
        computer.setStorage(storage);
        return *this;
    }
    
    ComputerBuilder& addWifi() {
        computer.setWifi(true);
        return *this;
    }
    
    ComputerBuilder& addBluetooth() {
        computer.setBluetooth(true);
        return *this;
    }
    
    Computer build() {
        return computer;
    }
};

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
