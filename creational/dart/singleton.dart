/*
 * SINGLETON DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Singleton pattern ensures a class has only one instance and provides a global point of access to that instance.
 * 
 * WHY DOES IT EXIST?
 * - Some resources should only exist once (database connections, logging services, configuration managers)
 * - Prevents multiple instances from causing conflicts or inconsistent state
 * - Provides controlled access to the sole instance
 * 
 * WHEN TO USE IT?
 * - When exactly one instance of a class is needed to coordinate actions across the system
 * - When the sole instance should be extensible by subclassing, and clients should be able to use an extended instance without modifying their code
 * - Common use cases: database connection pools, logging services, configuration managers, thread pools, caches
 * 
 * PROS:
 * - Controlled access to the sole instance
 * - Reduced namespace pollution (compared to global variables)
 * - Can be subclassed
 * - Can be lazy-loaded (created only when first needed)
 * 
 * CONS:
 * - Violates Single Responsibility Principle (handles both its business logic and instance creation)
 * - Can hide dependencies (making code harder to test)
 * - Global state can lead to unexpected behavior in multi-threaded environments
 * - Difficult to unit test due to global state
 * 
 * REAL-WORLD ANALOGY:
 * Think of a government - there's only one president or prime minister at a time. Everyone who needs to interact with the head of state goes through the same single instance. You can't have two presidents simultaneously making conflicting decisions.
 */

// Example 1: Basic Singleton using factory constructor
class DatabaseConnection {
  // Private static variable to hold the single instance
  static DatabaseConnection? _instance;
  
  // Private named constructor
  DatabaseConnection._internal() {
    print('DatabaseConnection: Initializing connection...');
    _isConnected = true;
  }
  
  // Factory constructor that returns the single instance
  factory DatabaseConnection() {
    _instance ??= DatabaseConnection._internal();
    return _instance!;
  }
  
  bool _isConnected = false;
  int _queryCount = 0;
  
  // Business logic methods
  void executeQuery(String query) {
    if (_isConnected) {
      _queryCount++;
      print('Executing query #$_queryCount: $query');
    } else {
      print('Error: Not connected to database');
    }
  }
  
  int get queryCount => _queryCount;
  
  bool get connectionStatus => _isConnected;
}

// Example 2: Singleton using static getter with lazy initialization
class Logger {
  static Logger? _instance;
  
  // Private constructor
  Logger._() {
    print('Logger: Initializing logger...');
  }
  
  // Static getter for lazy initialization
  static Logger get instance {
    _instance ??= Logger._();
    return _instance!;
  }
  
  int _logCount = 0;
  
  void log(String message) {
    _logCount++;
    print('[LOG #$_logCount] $message');
  }
  
  int get logCount => _logCount;
}

// Example 3: Singleton with initialization parameters
class ConfigurationManager {
  static ConfigurationManager? _instance;
  
  final Map<String, String> _config = {};
  
  // Private constructor with optional parameters
  ConfigurationManager._({Map<String, String>? initialConfig}) {
    print('ConfigurationManager: Initializing...');
    if (initialConfig != null) {
      _config.addAll(initialConfig);
    }
  }
  
  // Static method with optional initialization parameters
  static ConfigurationManager getInstance({Map<String, String>? initialConfig}) {
    _instance ??= ConfigurationManager._(initialConfig: initialConfig);
    return _instance!;
  }
  
  void set(String key, String value) {
    _config[key] = value;
  }
  
  String? get(String key) {
    return _config[key];
  }
  
  void displayConfig() {
    print('Current Configuration:');
    _config.forEach((key, value) {
      print('  $key: $value');
    });
  }
}

// Demo code
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
  print('Same instance? ${identical(config, config2) ? 'Yes' : 'No'}');
}
