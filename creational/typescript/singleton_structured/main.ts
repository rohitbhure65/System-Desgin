import { DatabaseConnection } from './database_connection';
import { Logger } from './logger';
import { ConfigurationManager } from './configuration_manager';
import { AsyncSingleton } from './async_singleton';

async function demoSingleton(): Promise<void> {
  console.log('=== Singleton Pattern Demo ===\n');
  
  console.log('--- DatabaseConnection Example ---');
  const db1 = DatabaseConnection.getInstance();
  db1.executeQuery('SELECT * FROM users');
  
  const db2 = DatabaseConnection.getInstance();
  db2.executeQuery('SELECT * FROM products');
  
  console.log(`Same instance? ${db1 === db2 ? 'Yes' : 'No'}`);
  console.log(`Total queries: ${db1.getQueryCount()}\n`);
  
  console.log('--- Logger Example ---');
  Logger.instance.log('Application started');
  Logger.instance.log('User logged in');
  Logger.instance.log('Processing request');
  console.log(`Total logs: ${Logger.instance.getLogCount()}\n`);
  
  console.log('--- ConfigurationManager Example ---');
  const initialConfig = {
    apiUrl: 'https://api.example.com',
    timeout: '5000'
  };
  const config = ConfigurationManager.getInstance(initialConfig);
  config.displayConfig();
  
  config.set('apiKey', 'abc123');
  config.displayConfig();
  
  const config2 = ConfigurationManager.getInstance();
  console.log(`Same instance? ${config === config2 ? 'Yes' : 'No'}\n`);

  console.log('--- AsyncSingleton Example ---');
  const instances = await Promise.all([
    AsyncSingleton.getInstance(),
    AsyncSingleton.getInstance(),
    AsyncSingleton.getInstance(),
  ]);
  console.log(`All instances are same: ${instances.every(i => i === instances[0])}`);
  
  console.log('\n--- Bypassing Singleton (Conceptual) ---');
  console.log('In TypeScript/JavaScript, singletons can be bypassed via:');
  console.log('1. Module cache clearing: delete require.cache[require.resolve(...)] (Node.js)');
  console.log('2. Multiple realms/iframes (Browser)');
  console.log('3. Worker threads: Each worker gets its own memory space and singleton instance.');
}

demoSingleton();
