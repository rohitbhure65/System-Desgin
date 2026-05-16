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

// Example 1: Basic Singleton using static property
class DatabaseConnection {
  // Private static property to hold the single instance
  private static instance: DatabaseConnection;
  
  // Private constructor to prevent instantiation from outside
  private constructor(private isConnected: boolean = false) {
    console.log('DatabaseConnection: Initializing connection...');
    this.isConnected = true;
  }
  
  // Static method to get the single instance
  public static getInstance(): DatabaseConnection {
    if (!DatabaseConnection.instance) {
      DatabaseConnection.instance = new DatabaseConnection();
    }
    return DatabaseConnection.instance;
  }
  
  // Business logic methods
  public executeQuery(query: string): void {
    if (this.isConnected) {
      console.log(`Executing query: ${query}`);
    } else {
      console.log('Error: Not connected to database');
    }
  }
  
  public getConnectionStatus(): boolean {
    return this.isConnected;
  }
}

// Example 2: Singleton with lazy initialization using getter
class Logger {
  private static _instance: Logger;
  private logCount: number = 0;
  
  // Private constructor
  private constructor() {
    console.log('Logger: Initializing logger...');
  }
  
  // Static getter for lazy initialization
  public static get instance(): Logger {
    if (!Logger._instance) {
      Logger._instance = new Logger();
    }
    return Logger._instance;
  }
  
  public log(message: string): void {
    this.logCount++;
    console.log(`[LOG #${this.logCount}] ${message}`);
  }
  
  public getLogCount(): number {
    return this.logCount;
  }
}

// Example 3: Singleton with initialization parameters
class ConfigurationManager {
  private static instance: ConfigurationManager;
  private config: Map<string, string>;
  
  // Private constructor with parameters
  private constructor(initialConfig?: Map<string, string>) {
    console.log('ConfigurationManager: Initializing...');
    this.config = initialConfig || new Map();
  }
  
  // Static method with optional initialization parameters
  public static getInstance(initialConfig?: Map<string, string>): ConfigurationManager {
    if (!ConfigurationManager.instance) {
      ConfigurationManager.instance = new ConfigurationManager(initialConfig);
    }
    return ConfigurationManager.instance;
  }
  
  public set(key: string, value: string): void {
    this.config.set(key, value);
  }
  
  public get(key: string): string | undefined {
    return this.config.get(key);
  }
  
  public displayConfig(): void {
    console.log('Current Configuration:');
    this.config.forEach((value, key) => {
      console.log(`  ${key}: ${value}`);
    });
  }
}

// Example 4: Singleton using module pattern (TypeScript-specific)
// This leverages TypeScript's module system to create a singleton
const SingletonService = (() => {
  let instance: any = null;
  
  class Service {
    private data: string[] = [];
    
    private constructor() {
      console.log('Service: Initializing...');
    }
    
    public addData(item: string): void {
      this.data.push(item);
    }
    
    public getData(): string[] {
      return [...this.data];
    }
  }
  
  return {
    getInstance: (): Service => {
      if (!instance) {
        instance = new Service();
      }
      return instance;
    }
  };
})();

// Demo code
function demoSingleton(): void {
  console.log('=== Singleton Pattern Demo ===\n');
  
  // Example 1: Basic Singleton
  console.log('--- DatabaseConnection Example ---');
  const db1 = DatabaseConnection.getInstance();
  db1.executeQuery('SELECT * FROM users');
  
  const db2 = DatabaseConnection.getInstance();
  db2.executeQuery('SELECT * FROM products');
  
  console.log(`Same instance? ${db1 === db2 ? 'Yes' : 'No'}\n`);
  
  // Example 2: Singleton with getter
  console.log('--- Logger Example ---');
  Logger.instance.log('Application started');
  Logger.instance.log('User logged in');
  Logger.instance.log('Processing request');
  console.log(`Total logs: ${Logger.instance.getLogCount()}\n`);
  
  // Example 3: Singleton with initialization parameters
  console.log('--- ConfigurationManager Example ---');
  const initialConfig = new Map<string, string>([
    ['apiUrl', 'https://api.example.com'],
    ['timeout', '5000']
  ]);
  const config = ConfigurationManager.getInstance(initialConfig);
  config.displayConfig();
  
  config.set('apiKey', 'abc123');
  config.displayConfig();
  
  const config2 = ConfigurationManager.getInstance();
  console.log(`Same instance? ${config === config2 ? 'Yes' : 'No'}\n`);
  
  // Example 4: Module pattern singleton
  console.log('--- Module Pattern Singleton ---');
  const service1 = SingletonService.getInstance();
  service1.addData('Item 1');
  service1.addData('Item 2');
  
  const service2 = SingletonService.getInstance();
  service2.addData('Item 3');
  
  console.log('Service data:', service2.getData());
  console.log(`Same instance? ${service1 === service2 ? 'Yes' : 'No'}`);
}

// Run the demo
demoSingleton();
