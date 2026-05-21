import 'builders.dart';
import 'director.dart';

void main() {
  print('=== Builder Pattern Demo ===\n');
  
  // Example 1: Classic Builder with Director
  print('--- Classic Builder with Director ---');
  
  var director = ConstructionDirector();
  
  // Build a simple house
  print('\nBuilding Simple House:');
  var simpleBuilder = SimpleHouseBuilder();
  director.setBuilder(simpleBuilder);
  director.buildBasicHouse();
  var simpleHouse = simpleBuilder.getResult();
  simpleHouse.display();
  
  // Build a luxury house
  print('\nBuilding Luxury House:');
  var luxuryBuilder = LuxuryHouseBuilder();
  director.setBuilder(luxuryBuilder);
  director.buildFullHouse();
  var luxuryHouse = luxuryBuilder.getResult();
  luxuryHouse.display();
  
  // Build a custom house
  print('\nBuilding Custom House (with garage and garden, no pool):');
  var customBuilder = SimpleHouseBuilder();
  director.setBuilder(customBuilder);
  director.buildCustomHouse(true, true, false);
  var customHouse = customBuilder.getResult();
  customHouse.display();
  
  // Example 2: Fluent Builder (method chaining)
  print('\n--- Fluent Builder (Method Chaining) ---');
  
  print('\nBuilding Gaming Computer:');
  var gamingComputer = ComputerBuilder()
      .setCpu('Intel Core i9-13900K')
      .setGpu('NVIDIA RTX 4090')
      .setRam(32)
      .setStorage(1000)
      .addWifi()
      .addBluetooth()
      .build();
  gamingComputer.display();
  
  print('\nBuilding Office Computer:');
  var officeComputer = ComputerBuilder()
      .setCpu('Intel Core i5-13400')
      .setGpu('Integrated Graphics')
      .setRam(16)
      .setStorage(512)
      .addWifi()
      .build();
  officeComputer.display();
  
  // Example 3: SQL Query Builder
  print('\n--- SQL Query Builder ---');
  
  var query1 = SQLQueryBuilder()
      .select('*')
      .from('users')
      .where('age > 18')
      .orderBy('name', direction: 'ASC')
      .limit(10)
      .build();
  print('Query 1: $query1');
  
  var query2 = SQLQueryBuilder()
      .select('name, email')
      .from('customers')
      .where('active = true')
      .orderBy('created_at', direction: 'DESC')
      .build();
  print('Query 2: $query2');
}
