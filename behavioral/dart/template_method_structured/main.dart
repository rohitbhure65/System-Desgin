import 'data_processor.dart';
import 'report_generator.dart';
import 'game_character.dart';

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
