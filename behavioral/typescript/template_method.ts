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
  processData(): void {
    console.log('\n=== Starting Data Processing ===');
    this.readData();
    this.validateData();
    this.transformData();
    this.saveData();
    console.log('=== Data Processing Complete ===');
  }
  
  // Primitive operations - to be implemented by subclasses
  protected abstract readData(): void;
  protected abstract validateData(): void;
  protected abstract transformData(): void;
  protected abstract saveData(): void;
  
  // Hook method - optional override point
  protected logProcessing(): void {
    console.log('Processing logged');
  }
}

// Concrete Class 1: CSV Data Processor
class CSVDataProcessor extends DataProcessor {
  private data: string = '';
  
  protected readData(): void {
    console.log('Reading CSV file...');
    this.data = 'name,age,city\nJohn,30,NYC\nJane,25,LA';
  }
  
  protected validateData(): void {
    console.log('Validating CSV format...');
    console.log('CSV format is valid');
  }
  
  protected transformData(): void {
    console.log('Transforming CSV to JSON...');
    // Simulate transformation
    this.data = '[{"name":"John","age":30,"city":"NYC"},{"name":"Jane","age":25,"city":"LA"}]';
  }
  
  protected saveData(): void {
    console.log('Saving JSON file...');
    console.log(`Data saved: ${this.data}`);
  }
}

// Concrete Class 2: XML Data Processor
class XMLDataProcessor extends DataProcessor {
  private data: string = '';
  
  protected readData(): void {
    console.log('Reading XML file...');
    this.data = '<users><user><name>John</name><age>30</age></user></users>';
  }
  
  protected validateData(): void {
    console.log('Validating XML structure...');
    console.log('XML structure is valid');
  }
  
  protected transformData(): void {
    console.log('Transforming XML to CSV...');
    // Simulate transformation
    this.data = 'name,age\nJohn,30';
  }
  
  protected saveData(): void {
    console.log('Saving CSV file...');
    console.log(`Data saved: ${this.data}`);
  }
}

// Example 2: Report Generation
// Shows how Template Method can be used for report generation

abstract class ReportGenerator {
  // Template method
  generateReport(): void {
    console.log('\n=== Generating Report ===');
    this.collectData();
    this.analyzeData();
    this.formatReport();
    this.exportReport();
    console.log('=== Report Generated ===');
  }
  
  protected abstract collectData(): void;
  protected abstract analyzeData(): void;
  protected abstract formatReport(): void;
  protected abstract exportReport(): void;
}

class SalesReport extends ReportGenerator {
  protected collectData(): void {
    console.log('Collecting sales data from database...');
  }
  
  protected analyzeData(): void {
    console.log('Analyzing sales trends...');
    console.log('Sales increased by 15% this quarter');
  }
  
  protected formatReport(): void {
    console.log('Formatting sales report with charts...');
  }
  
  protected exportReport(): void {
    console.log('Exporting to PDF...');
  }
}

class InventoryReport extends ReportGenerator {
  protected collectData(): void {
    console.log('Collecting inventory data...');
  }
  
  protected analyzeData(): void {
    console.log('Analyzing stock levels...');
    console.log('3 items need restocking');
  }
  
  protected formatReport(): void {
    console.log('Formatting inventory report with tables...');
  }
  
  protected exportReport(): void {
    console.log('Exporting to Excel...');
  }
}

// Example 3: Game Character Creation
// Shows how Template Method can be used for character creation

abstract class GameCharacter {
  // Template method
  createCharacter(): void {
    console.log('\n=== Creating Character ===');
    this.chooseName();
    this.selectRace();
    this.selectClass();
    this.assignStats();
    this.equipStartingItems();
    console.log('=== Character Created ===');
  }
  
  protected abstract chooseName(): void;
  protected abstract selectRace(): void;
  protected abstract selectClass(): void;
  protected abstract assignStats(): void;
  protected abstract equipStartingItems(): void;
  
  // Hook method
  protected displayCharacter(): void {
    console.log('Character ready for adventure!');
  }
}

class Warrior extends GameCharacter {
  protected chooseName(): void {
    console.log('Name chosen: Thorin');
  }
  
  protected selectRace(): void {
    console.log('Race selected: Dwarf');
  }
  
  protected selectClass(): void {
    console.log('Class selected: Warrior');
  }
  
  protected assignStats(): void {
    console.log('Stats assigned: STR: 18, DEX: 12, CON: 16, INT: 8, WIS: 10');
  }
  
  protected equipStartingItems(): void {
    console.log('Equipped: Iron Sword, Steel Shield, Chain Mail');
  }
  
  protected displayCharacter(): void {
    super.displayCharacter();
    console.log('Special ability: Battle Rage');
  }
}

class Mage extends GameCharacter {
  protected chooseName(): void {
    console.log('Name chosen: Gandalf');
  }
  
  protected selectRace(): void {
    console.log('Race selected: Human');
  }
  
  protected selectClass(): void {
    console.log('Class selected: Mage');
  }
  
  protected assignStats(): void {
    console.log('Stats assigned: STR: 8, DEX: 14, CON: 10, INT: 18, WIS: 16');
  }
  
  protected equipStartingItems(): void {
    console.log('Equipped: Wooden Staff, Robe, Spellbook');
  }
  
  protected displayCharacter(): void {
    super.displayCharacter();
    console.log('Special ability: Fireball');
  }
}

class Rogue extends GameCharacter {
  protected chooseName(): void {
    console.log('Name chosen: Legolas');
  }
  
  protected selectRace(): void {
    console.log('Race selected: Elf');
  }
  
  protected selectClass(): void {
    console.log('Class selected: Rogue');
  }
  
  protected assignStats(): void {
    console.log('Stats assigned: STR: 12, DEX: 18, CON: 12, INT: 14, WIS: 12');
  }
  
  protected equipStartingItems(): void {
    console.log('Equipped: Dagger, Leather Armor, Lockpicks');
  }
  
  protected displayCharacter(): void {
    super.displayCharacter();
    console.log('Special ability: Stealth');
  }
}

// Demo code
console.log('=== Template Method Pattern Demo ===\n');

// Example 1: Data Processing
console.log('--- Data Processing Example ---');

const csvProcessor = new CSVDataProcessor();
csvProcessor.processData();

const xmlProcessor = new XMLDataProcessor();
xmlProcessor.processData();

// Example 2: Report Generation
console.log('\n--- Report Generation Example ---');

const salesReport = new SalesReport();
salesReport.generateReport();

const inventoryReport = new InventoryReport();
inventoryReport.generateReport();

// Example 3: Game Character Creation
console.log('\n--- Game Character Creation Example ---');

const warrior = new Warrior();
warrior.createCharacter();

const mage = new Mage();
mage.createCharacter();

const rogue = new Rogue();
rogue.createCharacter();
