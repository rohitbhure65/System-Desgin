/*
 * TEMPLATE METHOD DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Template Method pattern defines the skeleton of an algorithm in the base class but lets subclasses override specific steps without changing the algorithm's structure.
 * It's a behavioral pattern that uses inheritance to define parts of an algorithm.
 * 
 * WHY DOES IT EXIST?
 * - When you have an algorithm with invariant parts and variable parts
 * - When you want to avoid code duplication by extracting common behavior
 * - When you want to control the extension points of an algorithm
 * 
 * WHEN TO USE IT?
 * - When you have several classes that contain almost identical algorithms with minor differences
 * - When you want to let subclasses extend only certain parts of a large algorithm
 * - When you want to enforce the overall structure of an algorithm while allowing customization
 * - Common use cases: data processing pipelines, frameworks, build systems, report generation
 * 
 * PROS:
 * - Reuses common code in the base class
 * - Follows Open/Closed Principle (extend behavior without modifying existing code)
 * - Provides control over the extension points
 * - Reduces code duplication
 * 
 * CONS:
 * - Can be difficult to maintain if the template method is complex
 * - May limit flexibility due to rigid structure
 * - Can lead to class explosion if many variations are needed
 * - Subclasses may need to implement methods they don't use
 * 
 * REAL-WORLD ANALOGY:
 * Think of cooking a recipe. The recipe (template method) defines the steps: prepare ingredients, cook, serve. The specific ingredients and cooking methods can vary (subclass implementations), but the overall structure remains the same. You can make pasta, curry, or stir-fry using the same recipe structure with different implementations.
 */

#include <iostream>
#include <string>
#include <vector>

// Abstract Class - defines the template method and abstract primitive operations
class DataProcessor {
public:
    virtual ~DataProcessor() = default;
    
    // Template method - defines the algorithm structure
    void processData() {
        std::cout << "\n=== Starting Data Processing ===" << std::endl;
        readData();
        validateData();
        transformData();
        saveData();
        std::cout << "=== Data Processing Complete ===" << std::endl;
    }
    
protected:
    // Primitive operations - to be implemented by subclasses
    virtual void readData() = 0;
    virtual void validateData() = 0;
    virtual void transformData() = 0;
    virtual void saveData() = 0;
    
    // Hook method - optional override point
    virtual void logProcessing() {
        std::cout << "Processing logged" << std::endl;
    }
};

// Concrete Class 1: CSV Data Processor
class CSVDataProcessor : public DataProcessor {
private:
    std::string data;
    
protected:
    void readData() override {
        std::cout << "Reading CSV file..." << std::endl;
        data = "name,age,city\nJohn,30,NYC\nJane,25,LA";
    }
    
    void validateData() override {
        std::cout << "Validating CSV format..." << std::endl;
        std::cout << "CSV format is valid" << std::endl;
    }
    
    void transformData() override {
        std::cout << "Transforming CSV to JSON..." << std::endl;
        // Simulate transformation
        data = "[{\"name\":\"John\",\"age\":30,\"city\":\"NYC\"},{\"name\":\"Jane\",\"age\":25,\"city\":\"LA\"}]";
    }
    
    void saveData() override {
        std::cout << "Saving JSON file..." << std::endl;
        std::cout << "Data saved: " << data << std::endl;
    }
};

// Concrete Class 2: XML Data Processor
class XMLDataProcessor : public DataProcessor {
private:
    std::string data;
    
protected:
    void readData() override {
        std::cout << "Reading XML file..." << std::endl;
        data = "<users><user><name>John</name><age>30</age></user></users>";
    }
    
    void validateData() override {
        std::cout << "Validating XML structure..." << std::endl;
        std::cout << "XML structure is valid" << std::endl;
    }
    
    void transformData() override {
        std::cout << "Transforming XML to CSV..." << std::endl;
        // Simulate transformation
        data = "name,age\nJohn,30";
    }
    
    void saveData() override {
        std::cout << "Saving CSV file..." << std::endl;
        std::cout << "Data saved: " << data << std::endl;
    }
};

// Example 2: Report Generation
// Shows how Template Method can be used for report generation

class ReportGenerator {
public:
    virtual ~ReportGenerator() = default;
    
    // Template method
    void generateReport() {
        std::cout << "\n=== Generating Report ===" << std::endl;
        collectData();
        analyzeData();
        formatReport();
        exportReport();
        std::cout << "=== Report Generated ===" << std::endl;
    }
    
protected:
    virtual void collectData() = 0;
    virtual void analyzeData() = 0;
    virtual void formatReport() = 0;
    virtual void exportReport() = 0;
};

class SalesReport : public ReportGenerator {
protected:
    void collectData() override {
        std::cout << "Collecting sales data from database..." << std::endl;
    }
    
    void analyzeData() override {
        std::cout << "Analyzing sales trends..." << std::endl;
        std::cout << "Sales increased by 15% this quarter" << std::endl;
    }
    
    void formatReport() override {
        std::cout << "Formatting sales report with charts..." << std::endl;
    }
    
    void exportReport() override {
        std::cout << "Exporting to PDF..." << std::endl;
    }
};

class InventoryReport : public ReportGenerator {
protected:
    void collectData() override {
        std::cout << "Collecting inventory data..." << std::endl;
    }
    
    void analyzeData() override {
        std::cout << "Analyzing stock levels..." << std::endl;
        std::cout << "3 items need restocking" << std::endl;
    }
    
    void formatReport() override {
        std::cout << "Formatting inventory report with tables..." << std::endl;
    }
    
    void exportReport() override {
        std::cout << "Exporting to Excel..." << std::endl;
    }
};

// Example 3: Game Character Creation
// Shows how Template Method can be used for character creation

class GameCharacter {
public:
    virtual ~GameCharacter() = default;
    
    // Template method
    void createCharacter() {
        std::cout << "\n=== Creating Character ===" << std::endl;
        chooseName();
        selectRace();
        selectClass();
        assignStats();
        equipStartingItems();
        std::cout << "=== Character Created ===" << std::endl;
    }
    
protected:
    virtual void chooseName() = 0;
    virtual void selectRace() = 0;
    virtual void selectClass() = 0;
    virtual void assignStats() = 0;
    virtual void equipStartingItems() = 0;
    
    // Hook method
    virtual void displayCharacter() {
        std::cout << "Character ready for adventure!" << std::endl;
    }
};

class Warrior : public GameCharacter {
protected:
    void chooseName() override {
        std::cout << "Name chosen: Thorin" << std::endl;
    }
    
    void selectRace() override {
        std::cout << "Race selected: Dwarf" << std::endl;
    }
    
    void selectClass() override {
        std::cout << "Class selected: Warrior" << std::endl;
    }
    
    void assignStats() override {
        std::cout << "Stats assigned: STR: 18, DEX: 12, CON: 16, INT: 8, WIS: 10" << std::endl;
    }
    
    void equipStartingItems() override {
        std::cout << "Equipped: Iron Sword, Steel Shield, Chain Mail" << std::endl;
    }
    
    void displayCharacter() override {
        GameCharacter::displayCharacter();
        std::cout << "Special ability: Battle Rage" << std::endl;
    }
};

class Mage : public GameCharacter {
protected:
    void chooseName() override {
        std::cout << "Name chosen: Gandalf" << std::endl;
    }
    
    void selectRace() override {
        std::cout << "Race selected: Human" << std::endl;
    }
    
    void selectClass() override {
        std::cout << "Class selected: Mage" << std::endl;
    }
    
    void assignStats() override {
        std::cout << "Stats assigned: STR: 8, DEX: 14, CON: 10, INT: 18, WIS: 16" << std::endl;
    }
    
    void equipStartingItems() override {
        std::cout << "Equipped: Wooden Staff, Robe, Spellbook" << std::endl;
    }
    
    void displayCharacter() override {
        GameCharacter::displayCharacter();
        std::cout << "Special ability: Fireball" << std::endl;
    }
};

class Rogue : public GameCharacter {
protected:
    void chooseName() override {
        std::cout << "Name chosen: Legolas" << std::endl;
    }
    
    void selectRace() override {
        std::cout << "Race selected: Elf" << std::endl;
    }
    
    void selectClass() override {
        std::cout << "Class selected: Rogue" << std::endl;
    }
    
    void assignStats() override {
        std::cout << "Stats assigned: STR: 12, DEX: 18, CON: 12, INT: 14, WIS: 12" << std::endl;
    }
    
    void equipStartingItems() override {
        std::cout << "Equipped: Dagger, Leather Armor, Lockpicks" << std::endl;
    }
    
    void displayCharacter() override {
        GameCharacter::displayCharacter();
        std::cout << "Special ability: Stealth" << std::endl;
    }
};

int main() {
    std::cout << "=== Template Method Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Data Processing
    std::cout << "--- Data Processing Example ---" << std::endl;
    
    CSVDataProcessor csvProcessor;
    csvProcessor.processData();
    
    XMLDataProcessor xmlProcessor;
    xmlProcessor.processData();
    
    // Example 2: Report Generation
    std::cout << "\n--- Report Generation Example ---" << std::endl;
    
    SalesReport salesReport;
    salesReport.generateReport();
    
    InventoryReport inventoryReport;
    inventoryReport.generateReport();
    
    // Example 3: Game Character Creation
    std::cout << "\n--- Game Character Creation Example ---" << std::endl;
    
    Warrior warrior;
    warrior.createCharacter();
    
    Mage mage;
    mage.createCharacter();
    
    Rogue rogue;
    rogue.createCharacter();
    
    return 0;
}
