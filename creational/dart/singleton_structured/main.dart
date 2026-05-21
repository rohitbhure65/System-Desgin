import 'database_connection.dart';
import 'logger.dart';
import 'configuration_manager.dart';
import 'async_singleton.dart';
// import 'bypasable_singleton.dart';

void main() {
  print('=== Singleton Pattern Demo ===\n');
  
  // Example 1: Basic Singleton
  print('--- DatabaseConnection Example ---');
  var db1 = DatabaseConnection();
  db1.executeQuery('SELECT * FROM users');
  
  var db2 = DatabaseConnection();
  db2.executeQuery('SELECT * FROM products');
  
  print('Same instance? ${identical(db1, db2) ? 'Yes' : 'No'}');
  print('Total queries: ${db1.queryCount}\n');
  
  // Example 2: Singleton with getter
  print('--- Logger Example ---');
  Logger.instance.log('Application started');
  Logger.instance.log('User logged in');
  Logger.instance.log('Processing request');
  print('Total logs: ${Logger.instance.logCount}\n');
  
  // Example 3: Singleton with initialization parameters
  print('--- ConfigurationManager Example ---');
  var initialConfig = <String, String>{
    'apiUrl': 'https://api.example.com',
    'timeout': '5000'
  };
  var config = ConfigurationManager.getInstance(initialConfig: initialConfig);
  config.displayConfig();
  
  config.set('apiKey', 'abc123');
  config.displayConfig();
  
  var config2 = ConfigurationManager.getInstance();
  print('Same instance? ${identical(config, config2) ? 'Yes' : 'No'}\n');

  // Example 4: Thread-safe (Async) Singleton
  print('--- AsyncSingleton Example ---');
  // Simulating multiple concurrent calls
  Future.wait([
    AsyncSingleton.getInstance(),
    AsyncSingleton.getInstance(),
    AsyncSingleton.getInstance(),
  ]).then((instances) {
    print('All instances are same: ${instances.every((i) => identical(i, instances[0]))}');
  });

  // Example 5: Bypassing Singleton (Conceptual)
  print('--- Bypassing Singleton (Conceptual) ---');
  print('In Dart, you can bypass singletons via:');
  print('1. Multiple Isolates: Each isolate gets its own memory and its own Singleton instance.');
  print('   (This is the most common "gotcha" in Flutter background tasks)');
  print('2. Reflection: Using "dart:mirrors" (not available in Flutter/Web).');
  print('3. Dependency Injection: Swapping the singleton for a mock during testing.');
}
