import { CSVDataProcessor, XMLDataProcessor } from './data_processor';
import { SalesReport, InventoryReport } from './report_generator';
import { Warrior, Mage, Rogue } from './game_character';

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
