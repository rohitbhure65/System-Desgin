#include "data_processor.hpp"
#include "report_generator.hpp"
#include "game_character.hpp"
#include <iostream>

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
