/*
 * ABSTRACT FACTORY DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Abstract Factory pattern provides an interface for creating families of related or dependent objects without specifying their concrete classes.
 * It's like a factory of factories.
 * 
 * WHY DOES IT EXIST?
 * - When you need to create families of related objects (e.g., UI components for different operating systems)
 * - When you want to ensure that created objects are compatible with each other
 * - When you want to provide a library of products without exposing their implementation details
 * - When you need to support multiple themes or platforms
 * 
 * WHEN TO USE IT?
 * - When a system should be independent of how its products are created, composed, and represented
 * - When a system should be configured with one of multiple families of products
 * - When the family of related product objects is designed to be used together, and you need to enforce this constraint
 * - When you want to provide a class library of products, and you want to reveal just their interfaces, not their implementations
 * - Common use cases: cross-platform UI components, database connectors for different DBMS, game development (different themes)
 * 
 * PROS:
 * - Ensures that products from the same family are compatible
 * - Hides the concrete classes from the client code
 * - Easy to introduce new product families without modifying existing code (Open/Closed Principle)
 * - Promotes consistency among products
 * 
 * CONS:
 * - Can be complex to implement due to many interfaces and classes
 * - Adding new products to existing families requires modifying all factory interfaces
 * - Can lead to excessive abstraction and indirection
 * - May be overkill for simple scenarios
 * 
 * REAL-WORLD ANALOGY:
 * Think of a furniture factory that produces different styles of furniture (Modern, Victorian, Rustic). Each style has its own family of products (chairs, tables, sofas). If you order a Modern chair, you want it to match with a Modern table. The abstract factory ensures that all furniture pieces you order belong to the same style family.
 */

// Abstract Product A: Button interface
interface Button {
  click(): void;
  render(): void;
  getName(): string;
}

// Abstract Product B: Checkbox interface
interface Checkbox {
  check(): void;
  render(): void;
  getName(): string;
}

// Concrete Product A1: Windows Button
class WindowsButton implements Button {
  click(): void {
    console.log('Windows button clicked!');
  }
  
  render(): void {
    console.log('Rendering Windows-style button...');
  }
  
  getName(): string {
    return 'Windows Button';
  }
}

// Concrete Product B1: Windows Checkbox
class WindowsCheckbox implements Checkbox {
  check(): void {
    console.log('Windows checkbox checked!');
  }
  
  render(): void {
    console.log('Rendering Windows-style checkbox...');
  }
  
  getName(): string {
    return 'Windows Checkbox';
  }
}

// Concrete Product A2: Mac Button
class MacButton implements Button {
  click(): void {
    console.log('Mac button clicked!');
  }
  
  render(): void {
    console.log('Rendering Mac-style button...');
  }
  
  getName(): string {
    return 'Mac Button';
  }
}

// Concrete Product B2: Mac Checkbox
class MacCheckbox implements Checkbox {
  check(): void {
    console.log('Mac checkbox checked!');
  }
  
  render(): void {
    console.log('Rendering Mac-style checkbox...');
  }
  
  getName(): string {
    return 'Mac Checkbox';
  }
}

// Abstract Factory interface - declares methods for creating each abstract product
interface GUIFactory {
  createButton(): Button;
  createCheckbox(): Checkbox;
}

// Concrete Factory 1: Windows Factory
// Creates Windows-specific UI components
class WindowsFactory implements GUIFactory {
  createButton(): Button {
    return new WindowsButton();
  }
  
  createCheckbox(): Checkbox {
    return new WindowsCheckbox();
  }
}

// Concrete Factory 2: Mac Factory
// Creates Mac-specific UI components
class MacFactory implements GUIFactory {
  createButton(): Button {
    return new MacButton();
  }
  
  createCheckbox(): Checkbox {
    return new MacCheckbox();
  }
}

// Client class that uses the abstract factory
// The client doesn't know which concrete factory is being used
class GUIApplication {
  private button: Button;
  private checkbox: Checkbox;
  
  constructor(factory: GUIFactory) {
    this.button = factory.createButton();
    this.checkbox = factory.createCheckbox();
  }
  
  // Business logic that uses the products
  public renderUI(): void {
    console.log('Rendering UI components...');
    console.log(`Button: ${this.button.getName()}`);
    console.log(`Checkbox: ${this.checkbox.getName()}`);
    
    this.button.render();
    this.checkbox.render();
  }
  
  public interact(): void {
    console.log('\nUser interaction...');
    this.button.click();
    this.checkbox.check();
  }
}

// Example: Database Abstract Factory
// Shows how Abstract Factory can be used for database connections

// Abstract Product: Database Connection
interface IDatabaseConnection {
  connect(): void;
  disconnect(): void;
  executeQuery(query: string): void;
}

// Abstract Product: Database Command
interface DatabaseCommand {
  execute(): void;
}

// Concrete Products: MySQL
class MySQLConnection implements IDatabaseConnection {
  connect(): void {
    console.log('Connecting to MySQL database...');
  }
  
  disconnect(): void {
    console.log('Disconnecting from MySQL database...');
  }
  
  executeQuery(query: string): void {
    console.log(`Executing MySQL query: ${query}`);
  }
}

class MySQLCommand implements DatabaseCommand {
  constructor(private command: string) {}
  
  execute(): void {
    console.log(`Executing MySQL command: ${this.command}`);
  }
}

// Concrete Products: PostgreSQL
class PostgreSQLConnection implements IDatabaseConnection {
  connect(): void {
    console.log('Connecting to PostgreSQL database...');
  }
  
  disconnect(): void {
    console.log('Disconnecting from PostgreSQL database...');
  }
  
  executeQuery(query: string): void {
    console.log(`Executing PostgreSQL query: ${query}`);
  }
}

class PostgreSQLCommand implements DatabaseCommand {
  constructor(private command: string) {}
  
  execute(): void {
    console.log(`Executing PostgreSQL command: ${this.command}`);
  }
}

// Abstract Factory for Database
interface DatabaseFactory {
  createConnection(): IDatabaseConnection;
  createCommand(cmd: string): DatabaseCommand;
}

// Concrete Factory: MySQL
class MySQLFactory implements DatabaseFactory {
  createConnection(): IDatabaseConnection {
    return new MySQLConnection();
  }
  
  createCommand(cmd: string): DatabaseCommand {
    return new MySQLCommand(cmd);
  }
}

// Concrete Factory: PostgreSQL
class PostgreSQLFactory implements DatabaseFactory {
  createConnection(): IDatabaseConnection {
    return new PostgreSQLConnection();
  }
  
  createCommand(cmd: string): DatabaseCommand {
    return new PostgreSQLCommand(cmd);
  }
}

// Demo code
function demoAbstractFactory(): void {
  console.log('=== Abstract Factory Pattern Demo ===\n');
  
  // Example 1: GUI Components
  console.log('--- GUI Components Example ---');
  
  // Create Windows UI
  console.log('\nCreating Windows UI:');
  const windowsFactory = new WindowsFactory();
  const windowsApp = new GUIApplication(windowsFactory);
  windowsApp.renderUI();
  windowsApp.interact();
  
  // Create Mac UI
  console.log('\nCreating Mac UI:');
  const macFactory = new MacFactory();
  const macApp = new GUIApplication(macFactory);
  macApp.renderUI();
  macApp.interact();
  
  // Example 2: Database Connections
  console.log('\n\n--- Database Connections Example ---');
  
  // MySQL
  console.log('\nUsing MySQL:');
  const mysqlFactory = new MySQLFactory();
  const mysqlConnection = mysqlFactory.createConnection();
  const mysqlCommand = mysqlFactory.createCommand('CREATE TABLE users (id INT)');
  
  mysqlConnection.connect();
  mysqlConnection.executeQuery('SELECT * FROM users');
  mysqlCommand.execute();
  mysqlConnection.disconnect();
  
  // PostgreSQL
  console.log('\nUsing PostgreSQL:');
  const postgresFactory = new PostgreSQLFactory();
  const postgresConnection = postgresFactory.createConnection();
  const postgresCommand = postgresFactory.createCommand('CREATE TABLE products (id INT)');
  
  postgresConnection.connect();
  postgresConnection.executeQuery('SELECT * FROM products');
  postgresCommand.execute();
  postgresConnection.disconnect();
}

// Run the demo
demoAbstractFactory();
