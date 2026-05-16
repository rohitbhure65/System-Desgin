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

// Example 4: Thread-safe (Synchronized) Singleton
// In Dart, everything runs in a single-threaded event loop, so basic singletons are inherently thread-safe.
// However, when dealing with ASYNC initialization, multiple callers might trigger initialization twice.
class AsyncSingleton {
  static AsyncSingleton? _instance;
  static bool _isInitializing = false;
  
  AsyncSingleton._internal() {
    print('AsyncSingleton: Instance created');
  }

  static Future<AsyncSingleton> getInstance() async {
    // If instance exists, return it
    if (_instance != null) return _instance!;

    // If already initializing, wait and check again (serialized access)
    while (_isInitializing) {
      await Future.delayed(Duration(milliseconds: 10));
      if (_instance != null) return _instance!;
    }

    _isInitializing = true;
    try {
      print('AsyncSingleton: Starting heavy async initialization...');
      await Future.delayed(Duration(milliseconds: 100)); // Simulate delay
      _instance = AsyncSingleton._internal();
    } finally {
      _isInitializing = false;
    }

    return _instance!;
  }
}

// Example 5: Bypassing Singleton
// In Dart, Singletons are scoped to the current ISOLATE. 
// A common "bypass" is when developers expect a singleton to share state across the whole app,
// but it fails when multiple isolates are used (e.g. background workers).
class BypasableSingleton {
  static final BypasableSingleton _instance = BypasableSingleton._internal();
  BypasableSingleton._internal();
  factory BypasableSingleton() => _instance;
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
