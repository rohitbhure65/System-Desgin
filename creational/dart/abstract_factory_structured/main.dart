import 'interfaces.dart';
import 'concrete_factories.dart';
import 'client.dart';

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
