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

// Product class - the complex object being built
class House {
  String _foundation = '';
  String _structure = '';
  String _roof = '';
  String _interior = '';
  bool _hasGarage = false;
  bool _hasGarden = false;
  bool _hasSwimmingPool = false;
  
  // Setter methods for builder to use
  void setFoundation(String f) {
    _foundation = f;
  }
  
  void setStructure(String s) {
    _structure = s;
  }
  
  void setRoof(String r) {
    _roof = r;
  }
  
  void setInterior(String i) {
    _interior = i;
  }
  
  void setGarage(bool g) {
    _hasGarage = g;
  }
  
  void setGarden(bool g) {
    _hasGarden = g;
  }
  
  void setSwimmingPool(bool s) {
    _hasSwimmingPool = s;
  }
  
  // Display the house details
  void display() {
    print('=== House Details ===');
    print('Foundation: $_foundation');
    print('Structure: $_structure');
    print('Roof: $_roof');
    print('Interior: $_interior');
    print('Garage: ${_hasGarage ? 'Yes' : 'No'}');
    print('Garden: ${_hasGarden ? 'Yes' : 'No'}');
    print('Swimming Pool: ${_hasSwimmingPool ? 'Yes' : 'No'}');
    print('====================');
  }
}

// Builder interface - defines the steps to build the product
abstract class HouseBuilder {
  void buildFoundation();
  void buildStructure();
  void buildRoof();
  void buildInterior();
  void buildGarage();
  void buildGarden();
  void buildSwimmingPool();
  House getResult();
}

// Concrete Builder 1: Simple House Builder
class SimpleHouseBuilder extends HouseBuilder {
  final House _house = House();
  
  @override
  void buildFoundation() {
    _house.setFoundation('Concrete foundation');
  }
  
  @override
  void buildStructure() {
    _house.setStructure('Wood frame structure');
  }
  
  @override
  void buildRoof() {
    _house.setRoof('Asphalt shingle roof');
  }
  
  @override
  void buildInterior() {
    _house.setInterior('Basic interior with drywall');
  }
  
  @override
  void buildGarage() {
    _house.setGarage(false);
  }
  
  @override
  void buildGarden() {
    _house.setGarden(false);
  }
  
  @override
  void buildSwimmingPool() {
    _house.setSwimmingPool(false);
  }
  
  @override
  House getResult() {
    return _house;
  }
}

// Concrete Builder 2: Luxury House Builder
class LuxuryHouseBuilder extends HouseBuilder {
  final House _house = House();
  
  @override
  void buildFoundation() {
    _house.setFoundation('Reinforced concrete foundation with basement');
  }
  
  @override
  void buildStructure() {
    _house.setStructure('Steel frame structure with brick exterior');
  }
  
  @override
  void buildRoof() {
    _house.setRoof('Spanish tile roof with solar panels');
  }
  
  @override
  void buildInterior() {
    _house.setInterior('Luxury interior with marble floors and custom cabinetry');
  }
  
  @override
  void buildGarage() {
    _house.setGarage(true);
  }
  
  @override
  void buildGarden() {
    _house.setGarden(true);
  }
  
  @override
  void buildSwimmingPool() {
    _house.setSwimmingPool(true);
  }
  
  @override
  House getResult() {
    return _house;
  }
}

// Director class - orchestrates the construction process
// The director knows the construction algorithm but doesn't know the details
class ConstructionDirector {
  HouseBuilder? _builder;
  
  void setBuilder(HouseBuilder builder) {
    _builder = builder;
  }
  
  // Construct a basic house
  void buildBasicHouse() {
    _builder!.buildFoundation();
    _builder!.buildStructure();
    _builder!.buildRoof();
    _builder!.buildInterior();
  }
  
  // Construct a full-featured house
  void buildFullHouse() {
    _builder!.buildFoundation();
    _builder!.buildStructure();
    _builder!.buildRoof();
    _builder!.buildInterior();
    _builder!.buildGarage();
    _builder!.buildGarden();
    _builder!.buildSwimmingPool();
  }
  
  // Construct a custom house
  void buildCustomHouse(bool withGarage, bool withGarden, bool withPool) {
    _builder!.buildFoundation();
    _builder!.buildStructure();
    _builder!.buildRoof();
    _builder!.buildInterior();
    if (withGarage) _builder!.buildGarage();
    if (withGarden) _builder!.buildGarden();
    if (withPool) _builder!.buildSwimmingPool();
  }
}

// Alternative: Fluent Builder pattern (method chaining)
// This is a common variation where the builder returns itself for chaining
class Computer {
  String _cpu = '';
  String _gpu = '';
  int _ram = 8;
  int _storage = 256;
  bool _hasWifi = false;
  bool _hasBluetooth = false;
  
  void setCpu(String cpu) {
    _cpu = cpu;
  }
  
  void setGpu(String gpu) {
    _gpu = gpu;
  }
  
  void setRam(int ram) {
    _ram = ram;
  }
  
  void setStorage(int storage) {
    _storage = storage;
  }
  
  void setWifi(bool wifi) {
    _hasWifi = wifi;
  }
  
  void setBluetooth(bool bluetooth) {
    _hasBluetooth = bluetooth;
  }
  
  void display() {
    print('=== Computer Specs ===');
    print('CPU: $_cpu');
    print('GPU: $_gpu');
    print('RAM: $_ram GB');
    print('Storage: $_storage GB');
    print('WiFi: ${_hasWifi ? 'Yes' : 'No'}');
    print('Bluetooth: ${_hasBluetooth ? 'Yes' : 'No'}');
    print('=====================');
  }
}

class ComputerBuilder {
  final Computer _computer = Computer();
  
  ComputerBuilder setCpu(String cpu) {
    _computer.setCpu(cpu);
    return this;
  }
  
  ComputerBuilder setGpu(String gpu) {
    _computer.setGpu(gpu);
    return this;
  }
  
  ComputerBuilder setRam(int ram) {
    _computer.setRam(ram);
    return this;
  }
  
  ComputerBuilder setStorage(int storage) {
    _computer.setStorage(storage);
    return this;
  }
  
  ComputerBuilder addWifi() {
    _computer.setWifi(true);
    return this;
  }
  
  ComputerBuilder addBluetooth() {
    _computer.setBluetooth(true);
    return this;
  }
  
  Computer build() {
    return _computer;
  }
}

// Example: SQL Query Builder
class SQLQueryBuilder {
  String _query = '';
  
  SQLQueryBuilder select(String columns) {
    _query = 'SELECT $columns';
    return this;
  }
  
  SQLQueryBuilder from(String table) {
    _query += ' FROM $table';
    return this;
  }
  
  SQLQueryBuilder where(String condition) {
    _query += ' WHERE $condition';
    return this;
  }
  
  SQLQueryBuilder orderBy(String column, {String direction = 'ASC'}) {
    _query += ' ORDER BY $column $direction';
    return this;
  }
  
  SQLQueryBuilder limit(int count) {
    _query += ' LIMIT $count';
    return this;
  }
  
  String build() {
    return '$_query;';
  }
}

// Demo code
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
