import { GUIApplication } from './client';
import { WindowsFactory, MacFactory, MySQLFactory, PostgreSQLFactory } from './concrete_factories';

function demoAbstractFactory(): void {
  console.log('=== Abstract Factory Pattern Demo ===\n');
  
  console.log('--- GUI Components Example ---');
  
  console.log('\nCreating Windows UI:');
  const windowsFactory = new WindowsFactory();
  const windowsApp = new GUIApplication(windowsFactory);
  windowsApp.renderUI();
  windowsApp.interact();
  
  console.log('\nCreating Mac UI:');
  const macFactory = new MacFactory();
  const macApp = new GUIApplication(macFactory);
  macApp.renderUI();
  macApp.interact();
  
  console.log('\n\n--- Database Connections Example ---');
  
  console.log('\nUsing MySQL:');
  const mysqlFactory = new MySQLFactory();
  const mysqlConnection = mysqlFactory.createConnection();
  const mysqlCommand = mysqlFactory.createCommand('CREATE TABLE users (id INT)');
  
  mysqlConnection.connect();
  mysqlConnection.executeQuery('SELECT * FROM users');
  mysqlCommand.execute();
  mysqlConnection.disconnect();
  
  console.log('\nUsing PostgreSQL:');
  const postgresFactory = new PostgreSQLFactory();
  const postgresConnection = postgresFactory.createConnection();
  const postgresCommand = postgresFactory.createCommand('CREATE TABLE products (id INT)');
  
  postgresConnection.connect();
  postgresConnection.executeQuery('SELECT * FROM products');
  postgresCommand.execute();
  postgresConnection.disconnect();
}

demoAbstractFactory();
