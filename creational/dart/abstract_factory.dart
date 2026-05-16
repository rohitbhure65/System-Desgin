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
abstract class Button {
  void click();
  void render();
  String get name;
}

// Abstract Product B: Checkbox interface
abstract class Checkbox {
  void check();
  void render();
  String get name;
}

// Concrete Product A1: Windows Button
class WindowsButton extends Button {
  @override
  void click() {
    print('Windows button clicked!');
  }
  
  @override
  void render() {
    print('Rendering Windows-style button...');
  }
  
  @override
  String get name => 'Windows Button';
}

// Concrete Product B1: Windows Checkbox
class WindowsCheckbox extends Checkbox {
  @override
  void check() {
    print('Windows checkbox checked!');
  }
  
  @override
  void render() {
    print('Rendering Windows-style checkbox...');
  }
  
  @override
  String get name => 'Windows Checkbox';
}

// Concrete Product A2: Mac Button
class MacButton extends Button {
  @override
  void click() {
    print('Mac button clicked!');
  }
  
  @override
  void render() {
    print('Rendering Mac-style button...');
  }
  
  @override
  String get name => 'Mac Button';
}

// Concrete Product B2: Mac Checkbox
class MacCheckbox extends Checkbox {
  @override
  void check() {
    print('Mac checkbox checked!');
  }
  
  @override
  void render() {
    print('Rendering Mac-style checkbox...');
  }
  
  @override
  String get name => 'Mac Checkbox';
}

// Abstract Factory interface - declares methods for creating each abstract product
abstract class GUIFactory {
  Button createButton();
  Checkbox createCheckbox();
}

// Concrete Factory 1: Windows Factory
// Creates Windows-specific UI components
class WindowsFactory extends GUIFactory {
  @override
  Button createButton() {
    return WindowsButton();
  }
  
  @override
  Checkbox createCheckbox() {
    return WindowsCheckbox();
  }
}

// Concrete Factory 2: Mac Factory
// Creates Mac-specific UI components
class MacFactory extends GUIFactory {
  @override
  Button createButton() {
    return MacButton();
  }
  
  @override
  Checkbox createCheckbox() {
    return MacCheckbox();
  }
}

// Client class that uses the abstract factory
// The client doesn't know which concrete factory is being used
class GUIApplication {
  final Button _button;
  final Checkbox _checkbox;
  
  GUIApplication(GUIFactory factory)
      : _button = factory.createButton(),
        _checkbox = factory.createCheckbox();
  
  // Business logic that uses the products
  void renderUI() {
    print('Rendering UI components...');
    print('Button: ${_button.name}');
    print('Checkbox: ${_checkbox.name}');
    
    _button.render();
    _checkbox.render();
  }
  
  void interact() {
    print('\nUser interaction...');
    _button.click();
    _checkbox.check();
  }
}

// Example: Database Abstract Factory
// Shows how Abstract Factory can be used for database connections

// Abstract Product: Database Connection
abstract class IDatabaseConnection {
  void connect();
  void disconnect();
  void executeQuery(String query);
}

// Abstract Product: Database Command
abstract class DatabaseCommand {
  void execute();
}

// Concrete Products: MySQL
class MySQLConnection extends IDatabaseConnection {
  @override
  void connect() {
    print('Connecting to MySQL database...');
  }
  
  @override
  void disconnect() {
    print('Disconnecting from MySQL database...');
  }
  
  @override
  void executeQuery(String query) {
    print('Executing MySQL query: $query');
  }
}

class MySQLCommand extends DatabaseCommand {
  final String _command;
  
  MySQLCommand(this._command);
  
  @override
  void execute() {
    print('Executing MySQL command: $_command');
  }
}

// Concrete Products: PostgreSQL
class PostgreSQLConnection extends IDatabaseConnection {
  @override
  void connect() {
    print('Connecting to PostgreSQL database...');
  }
  
  @override
  void disconnect() {
    print('Disconnecting from PostgreSQL database...');
  }
  
  @override
  void executeQuery(String query) {
    print('Executing PostgreSQL query: $query');
  }
}

class PostgreSQLCommand extends DatabaseCommand {
  final String _command;
  
  PostgreSQLCommand(this._command);
  
  @override
  void execute() {
    print('Executing PostgreSQL command: $_command');
  }
}

// Abstract Factory for Database
abstract class DatabaseFactory {
  IDatabaseConnection createConnection();
  DatabaseCommand createCommand(String cmd);
}

// Concrete Factory: MySQL
class MySQLFactory extends DatabaseFactory {
  @override
  IDatabaseConnection createConnection() {
    return MySQLConnection();
  }
  
  @override
  DatabaseCommand createCommand(String cmd) {
    return MySQLCommand(cmd);
  }
}

// Concrete Factory: PostgreSQL
class PostgreSQLFactory extends DatabaseFactory {
  @override
  IDatabaseConnection createConnection() {
    return PostgreSQLConnection();
  }
  
  @override
  DatabaseCommand createCommand(String cmd) {
    return PostgreSQLCommand(cmd);
  }
}

// Demo code
void main() {
  print('=== Abstract Factory Pattern Demo ===\n');
  
  // Example 1: GUI Components
  print('--- GUI Components Example ---');
  
  // Create Windows UI
  print('\nCreating Windows UI:');
  var windowsFactory = WindowsFactory();
  var windowsApp = GUIApplication(windowsFactory);
  windowsApp.renderUI();
  windowsApp.interact();
  
  // Create Mac UI
  print('\nCreating Mac UI:');
  var macFactory = MacFactory();
  var macApp = GUIApplication(macFactory);
  macApp.renderUI();
  macApp.interact();
  
  // Example 2: Database Connections
  print('\n\n--- Database Connections Example ---');
  
  // MySQL
  print('\nUsing MySQL:');
  var mysqlFactory = MySQLFactory();
  var mysqlConnection = mysqlFactory.createConnection();
  var mysqlCommand = mysqlFactory.createCommand('CREATE TABLE users (id INT)');
  
  mysqlConnection.connect();
  mysqlConnection.executeQuery('SELECT * FROM users');
  mysqlCommand.execute();
  mysqlConnection.disconnect();
  
  // PostgreSQL
  print('\nUsing PostgreSQL:');
  var postgresFactory = PostgreSQLFactory();
  var postgresConnection = postgresFactory.createConnection();
  var postgresCommand = postgresFactory.createCommand('CREATE TABLE products (id INT)');
  
  postgresConnection.connect();
  postgresConnection.executeQuery('SELECT * FROM products');
  postgresCommand.execute();
  postgresConnection.disconnect();
}
