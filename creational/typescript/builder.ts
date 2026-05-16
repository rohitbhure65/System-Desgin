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
  private foundation: string = '';
  private structure: string = '';
  private roof: string = '';
  private interior: string = '';
  private hasGarage: boolean = false;
  private hasGarden: boolean = false;
  private hasSwimmingPool: boolean = false;
  
  // Setter methods for builder to use
  public setFoundation(f: string): void {
    this.foundation = f;
  }
  
  public setStructure(s: string): void {
    this.structure = s;
  }
  
  public setRoof(r: string): void {
    this.roof = r;
  }
  
  public setInterior(i: string): void {
    this.interior = i;
  }
  
  public setGarage(g: boolean): void {
    this.hasGarage = g;
  }
  
  public setGarden(g: boolean): void {
    this.hasGarden = g;
  }
  
  public setSwimmingPool(s: boolean): void {
    this.hasSwimmingPool = s;
  }
  
  // Display the house details
  public display(): void {
    console.log('=== House Details ===');
    console.log(`Foundation: ${this.foundation}`);
    console.log(`Structure: ${this.structure}`);
    console.log(`Roof: ${this.roof}`);
    console.log(`Interior: ${this.interior}`);
    console.log(`Garage: ${this.hasGarage ? 'Yes' : 'No'}`);
    console.log(`Garden: ${this.hasGarden ? 'Yes' : 'No'}`);
    console.log(`Swimming Pool: ${this.hasSwimmingPool ? 'Yes' : 'No'}`);
    console.log('====================');
  }
}

// Builder interface - defines the steps to build the product
interface HouseBuilder {
  buildFoundation(): void;
  buildStructure(): void;
  buildRoof(): void;
  buildInterior(): void;
  buildGarage(): void;
  buildGarden(): void;
  buildSwimmingPool(): void;
  getResult(): House;
}

// Concrete Builder 1: Simple House Builder
class SimpleHouseBuilder implements HouseBuilder {
  private house: House = new House();
  
  buildFoundation(): void {
    this.house.setFoundation('Concrete foundation');
  }
  
  buildStructure(): void {
    this.house.setStructure('Wood frame structure');
  }
  
  buildRoof(): void {
    this.house.setRoof('Asphalt shingle roof');
  }
  
  buildInterior(): void {
    this.house.setInterior('Basic interior with drywall');
  }
  
  buildGarage(): void {
    this.house.setGarage(false);
  }
  
  buildGarden(): void {
    this.house.setGarden(false);
  }
  
  buildSwimmingPool(): void {
    this.house.setSwimmingPool(false);
  }
  
  getResult(): House {
    return this.house;
  }
}

// Concrete Builder 2: Luxury House Builder
class LuxuryHouseBuilder implements HouseBuilder {
  private house: House = new House();
  
  buildFoundation(): void {
    this.house.setFoundation('Reinforced concrete foundation with basement');
  }
  
  buildStructure(): void {
    this.house.setStructure('Steel frame structure with brick exterior');
  }
  
  buildRoof(): void {
    this.house.setRoof('Spanish tile roof with solar panels');
  }
  
  buildInterior(): void {
    this.house.setInterior('Luxury interior with marble floors and custom cabinetry');
  }
  
  buildGarage(): void {
    this.house.setGarage(true);
  }
  
  buildGarden(): void {
    this.house.setGarden(true);
  }
  
  buildSwimmingPool(): void {
    this.house.setSwimmingPool(true);
  }
  
  getResult(): House {
    return this.house;
  }
}

// Director class - orchestrates the construction process
// The director knows the construction algorithm but doesn't know the details
class ConstructionDirector {
  private builder!: HouseBuilder;
  
  public setBuilder(builder: HouseBuilder): void {
    this.builder = builder;
  }
  
  // Construct a basic house
  public buildBasicHouse(): void {
    this.builder.buildFoundation();
    this.builder.buildStructure();
    this.builder.buildRoof();
    this.builder.buildInterior();
  }
  
  // Construct a full-featured house
  public buildFullHouse(): void {
    this.builder.buildFoundation();
    this.builder.buildStructure();
    this.builder.buildRoof();
    this.builder.buildInterior();
    this.builder.buildGarage();
    this.builder.buildGarden();
    this.builder.buildSwimmingPool();
  }
  
  // Construct a custom house
  public buildCustomHouse(withGarage: boolean, withGarden: boolean, withPool: boolean): void {
    this.builder.buildFoundation();
    this.builder.buildStructure();
    this.builder.buildRoof();
    this.builder.buildInterior();
    if (withGarage) this.builder.buildGarage();
    if (withGarden) this.builder.buildGarden();
    if (withPool) this.builder.buildSwimmingPool();
  }
}

// Alternative: Fluent Builder pattern (method chaining)
// This is a common variation where the builder returns itself for chaining
class Computer {
  private cpu: string = '';
  private gpu: string = '';
  private ram: number = 8;
  private storage: number = 256;
  private hasWifi: boolean = false;
  private hasBluetooth: boolean = false;
  
  public setCpu(cpu: string): void {
    this.cpu = cpu;
  }
  
  public setGpu(gpu: string): void {
    this.gpu = gpu;
  }
  
  public setRam(ram: number): void {
    this.ram = ram;
  }
  
  public setStorage(storage: number): void {
    this.storage = storage;
  }
  
  public setWifi(wifi: boolean): void {
    this.hasWifi = wifi;
  }
  
  public setBluetooth(bluetooth: boolean): void {
    this.hasBluetooth = bluetooth;
  }
  
  public display(): void {
    console.log('=== Computer Specs ===');
    console.log(`CPU: ${this.cpu}`);
    console.log(`GPU: ${this.gpu}`);
    console.log(`RAM: ${this.ram} GB`);
    console.log(`Storage: ${this.storage} GB`);
    console.log(`WiFi: ${this.hasWifi ? 'Yes' : 'No'}`);
    console.log(`Bluetooth: ${this.hasBluetooth ? 'Yes' : 'No'}`);
    console.log('=====================');
  }
}

class ComputerBuilder {
  private computer: Computer = new Computer();
  
  public setCpu(cpu: string): this {
    this.computer.setCpu(cpu);
    return this;
  }
  
  public setGpu(gpu: string): this {
    this.computer.setGpu(gpu);
    return this;
  }
  
  public setRam(ram: number): this {
    this.computer.setRam(ram);
    return this;
  }
  
  public setStorage(storage: number): this {
    this.computer.setStorage(storage);
    return this;
  }
  
  public addWifi(): this {
    this.computer.setWifi(true);
    return this;
  }
  
  public addBluetooth(): this {
    this.computer.setBluetooth(true);
    return this;
  }
  
  public build(): Computer {
    return this.computer;
  }
}

// Example: SQL Query Builder
class SQLQueryBuilder {
  private query: string = '';
  
  public select(columns: string): this {
    this.query = `SELECT ${columns}`;
    return this;
  }
  
  public from(table: string): this {
    this.query += ` FROM ${table}`;
    return this;
  }
  
  public where(condition: string): this {
    this.query += ` WHERE ${condition}`;
    return this;
  }
  
  public orderBy(column: string, direction: 'ASC' | 'DESC' = 'ASC'): this {
    this.query += ` ORDER BY ${column} ${direction}`;
    return this;
  }
  
  public limit(count: number): this {
    this.query += ` LIMIT ${count}`;
    return this;
  }
  
  public build(): string {
    return this.query + ';';
  }
}

// Demo code
function demoBuilder(): void {
  console.log('=== Builder Pattern Demo ===\n');
  
  // Example 1: Classic Builder with Director
  console.log('--- Classic Builder with Director ---');
  
  const director = new ConstructionDirector();
  
  // Build a simple house
  console.log('\nBuilding Simple House:');
  const simpleBuilder = new SimpleHouseBuilder();
  director.setBuilder(simpleBuilder);
  director.buildBasicHouse();
  const simpleHouse = simpleBuilder.getResult();
  simpleHouse.display();
  
  // Build a luxury house
  console.log('\nBuilding Luxury House:');
  const luxuryBuilder = new LuxuryHouseBuilder();
  director.setBuilder(luxuryBuilder);
  director.buildFullHouse();
  const luxuryHouse = luxuryBuilder.getResult();
  luxuryHouse.display();
  
  // Build a custom house
  console.log('\nBuilding Custom House (with garage and garden, no pool):');
  const customBuilder = new SimpleHouseBuilder();
  director.setBuilder(customBuilder);
  director.buildCustomHouse(true, true, false);
  const customHouse = customBuilder.getResult();
  customHouse.display();
  
  // Example 2: Fluent Builder (method chaining)
  console.log('\n--- Fluent Builder (Method Chaining) ---');
  
  console.log('\nBuilding Gaming Computer:');
  const gamingComputer = new ComputerBuilder()
    .setCpu('Intel Core i9-13900K')
    .setGpu('NVIDIA RTX 4090')
    .setRam(32)
    .setStorage(1000)
    .addWifi()
    .addBluetooth()
    .build();
  gamingComputer.display();
  
  console.log('\nBuilding Office Computer:');
  const officeComputer = new ComputerBuilder()
    .setCpu('Intel Core i5-13400')
    .setGpu('Integrated Graphics')
    .setRam(16)
    .setStorage(512)
    .addWifi()
    .build();
  officeComputer.display();
  
  // Example 3: SQL Query Builder
  console.log('\n--- SQL Query Builder ---');
  
  const query1 = new SQLQueryBuilder()
    .select('*')
    .from('users')
    .where('age > 18')
    .orderBy('name', 'ASC')
    .limit(10)
    .build();
  console.log('Query 1:', query1);
  
  const query2 = new SQLQueryBuilder()
    .select('name, email')
    .from('customers')
    .where('active = true')
    .orderBy('created_at', 'DESC')
    .build();
  console.log('Query 2:', query2);
}

// Run the demo
demoBuilder();
