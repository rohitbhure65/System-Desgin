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

// Abstract Class - defines the template method and abstract primitive operations
abstract class DataProcessor {
  // Template method - defines the algorithm structure
  void processData() {
    print('\n=== Starting Data Processing ===');
    readData();
    validateData();
    transformData();
    saveData();
    print('=== Data Processing Complete ===');
  }
  
  // Primitive operations - to be implemented by subclasses
  void readData();
  void validateData();
  void transformData();
  void saveData();
  
  // Hook method - optional override point
  void logProcessing() {
    print('Processing logged');
  }
}

// Concrete Class 1: CSV Data Processor
class CSVDataProcessor extends DataProcessor {
  String _data = '';
  
  @override
  void readData() {
    print('Reading CSV file...');
    _data = 'name,age,city\nJohn,30,NYC\nJane,25,LA';
  }
  
  @override
  void validateData() {
    print('Validating CSV format...');
    print('CSV format is valid');
  }
  
  @override
  void transformData() {
    print('Transforming CSV to JSON...');
    // Simulate transformation
    _data = '[{"name":"John","age":30,"city":"NYC"},{"name":"Jane","age":25,"city":"LA"}]';
  }
  
  @override
  void saveData() {
    print('Saving JSON file...');
    print('Data saved: $_data');
  }
}

// Concrete Class 2: XML Data Processor
class XMLDataProcessor extends DataProcessor {
  String _data = '';
  
  @override
  void readData() {
    print('Reading XML file...');
    _data = '<users><user><name>John</name><age>30</age></user></users>';
  }
  
  @override
  void validateData() {
    print('Validating XML structure...');
    print('XML structure is valid');
  }
  
  @override
  void transformData() {
    print('Transforming XML to CSV...');
    // Simulate transformation
    _data = 'name,age\nJohn,30';
  }
  
  @override
  void saveData() {
    print('Saving CSV file...');
    print('Data saved: $_data');
  }
}

// Example 2: Report Generation
// Shows how Template Method can be used for report generation

abstract class ReportGenerator {
  // Template method
  void generateReport() {
    print('\n=== Generating Report ===');
    collectData();
    analyzeData();
    formatReport();
    exportReport();
    print('=== Report Generated ===');
  }
  
  void collectData();
  void analyzeData();
  void formatReport();
  void exportReport();
}

class SalesReport extends ReportGenerator {
  @override
  void collectData() {
    print('Collecting sales data from database...');
  }
  
  @override
  void analyzeData() {
    print('Analyzing sales trends...');
    print('Sales increased by 15% this quarter');
  }
  
  @override
  void formatReport() {
    print('Formatting sales report with charts...');
  }
  
  @override
  void exportReport() {
    print('Exporting to PDF...');
  }
}

class InventoryReport extends ReportGenerator {
  @override
  void collectData() {
    print('Collecting inventory data...');
  }
  
  @override
  void analyzeData() {
    print('Analyzing stock levels...');
    print('3 items need restocking');
  }
  
  @override
  void formatReport() {
    print('Formatting inventory report with tables...');
  }
  
  @override
  void exportReport() {
    print('Exporting to Excel...');
  }
}

// Example 3: Game Character Creation
// Shows how Template Method can be used for character creation

abstract class GameCharacter {
  // Template method
  void createCharacter() {
    print('\n=== Creating Character ===');
    chooseName();
    selectRace();
    selectClass();
    assignStats();
    equipStartingItems();
    print('=== Character Created ===');
  }
  
  void chooseName();
  void selectRace();
  void selectClass();
  void assignStats();
  void equipStartingItems();
  
  // Hook method
  void displayCharacter() {
    print('Character ready for adventure!');
  }
}

class Warrior extends GameCharacter {
  @override
  void chooseName() {
    print('Name chosen: Thorin');
  }
  
  @override
  void selectRace() {
    print('Race selected: Dwarf');
  }
  
  @override
  void selectClass() {
    print('Class selected: Warrior');
  }
  
  @override
  void assignStats() {
    print('Stats assigned: STR: 18, DEX: 12, CON: 16, INT: 8, WIS: 10');
  }
  
  @override
  void equipStartingItems() {
    print('Equipped: Iron Sword, Steel Shield, Chain Mail');
  }
  
  @override
  void displayCharacter() {
    super.displayCharacter();
    print('Special ability: Battle Rage');
  }
}

class Mage extends GameCharacter {
  @override
  void chooseName() {
    print('Name chosen: Gandalf');
  }
  
  @override
  void selectRace() {
    print('Race selected: Human');
  }
  
  @override
  void selectClass() {
    print('Class selected: Mage');
  }
  
  @override
  void assignStats() {
    print('Stats assigned: STR: 8, DEX: 14, CON: 10, INT: 18, WIS: 16');
  }
  
  @override
  void equipStartingItems() {
    print('Equipped: Wooden Staff, Robe, Spellbook');
  }
  
  @override
  void displayCharacter() {
    super.displayCharacter();
    print('Special ability: Fireball');
  }
}

class Rogue extends GameCharacter {
  @override
  void chooseName() {
    print('Name chosen: Legolas');
  }
  
  @override
  void selectRace() {
    print('Race selected: Elf');
  }
  
  @override
  void selectClass() {
    print('Class selected: Rogue');
  }
  
  @override
  void assignStats() {
    print('Stats assigned: STR: 12, DEX: 18, CON: 12, INT: 14, WIS: 12');
  }
  
  @override
  void equipStartingItems() {
    print('Equipped: Dagger, Leather Armor, Lockpicks');
  }
  
  @override
  void displayCharacter() {
    super.displayCharacter();
    print('Special ability: Stealth');
  }
}

// Demo code
void main() {
  print('=== Template Method Pattern Demo ===\n');
  
  // Example 1: Data Processing
  print('--- Data Processing Example ---');
  
  final csvProcessor = CSVDataProcessor();
  csvProcessor.processData();
  
  final xmlProcessor = XMLDataProcessor();
  xmlProcessor.processData();
  
  // Example 2: Report Generation
  print('\n--- Report Generation Example ---');
  
  final salesReport = SalesReport();
  salesReport.generateReport();
  
  final inventoryReport = InventoryReport();
  inventoryReport.generateReport();
  
  // Example 3: Game Character Creation
  print('\n--- Game Character Creation Example ---');
  
  final warrior = Warrior();
  warrior.createCharacter();
  
  final mage = Mage();
  mage.createCharacter();
  
  final rogue = Rogue();
  rogue.createCharacter();
}
