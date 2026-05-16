/*
 * PROXY DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Proxy pattern provides a surrogate or placeholder object to control access to another object.
 * It acts as an intermediary between the client and the real object.
 * 
 * WHY DOES IT EXIST?
 * - When you need to control access to an object
 * - When you want to add additional functionality when accessing an object
 * - When you need to defer the creation or initialization of expensive objects
 * 
 * WHEN TO USE IT?
 * - When you want to add a layer of security to access an object
 * - When you need to cache results of expensive operations
 * - When you want to delay object creation until it's actually needed (lazy initialization)
 * - When you need to log or monitor access to an object
 * - Common use cases: remote objects, virtual proxies, protection proxies, smart references
 * 
 * PROS:
 * - Can control access to the real object
 * - Can add additional functionality without changing the real object
 * - Can optimize performance (lazy loading, caching)
 * - Can provide security by controlling access
 * 
 * CONS:
 * - Adds an extra layer of indirection
 * - Can increase response time due to proxy overhead
 * - Can make the code more complex
 * - May introduce bugs if the proxy doesn't perfectly mimic the real object
 * 
 * REAL-WORLD ANALOGY:
 * Think of a credit card. The credit card (proxy) represents your bank account (real object). You don't carry your actual bank account around - you use the card as a proxy. The card controls access to your money, adds security (PIN, chip), and logs transactions, all while giving you access to your funds.
 */

// Subject Interface - defines the common interface for RealSubject and Proxy
interface Image {
  display(): void;
}

// RealSubject - the actual object that the proxy represents
class RealImage implements Image {
  private filename: string;
  
  constructor(filename: string) {
    this.filename = filename;
    this.loadFromDisk();
  }
  
  // Helper method to load the image from disk
  private loadFromDisk(): void {
    console.log(`Loading ${this.filename} from disk...`);
  }
  
  display(): void {
    console.log(`Displaying ${this.filename}`);
  }
}

// Proxy - controls access to the RealSubject
class ProxyImage implements Image {
  private filename: string;
  private realImage?: RealImage;
  
  constructor(filename: string) {
    this.filename = filename;
  }
  
  display(): void {
    // Lazy initialization: only create the real image when needed
    if (!this.realImage) {
      console.log('Creating real image on first access...');
      this.realImage = new RealImage(this.filename);
    }
    this.realImage.display();
  }
}

// Example 2: Protection Proxy
// Shows how Proxy can control access based on permissions

interface Database {
  query(sql: string): void;
}

class RealDatabase implements Database {
  query(sql: string): void {
    console.log(`Executing query: ${sql}`);
  }
}

class DatabaseProxy implements Database {
  private realDatabase?: RealDatabase;
  private currentUser: string;
  private permissions: Map<string, boolean> = new Map();
  
  constructor(user: string) {
    this.currentUser = user;
    // Set up permissions (in real app, this would come from auth system)
    this.permissions.set('admin', true);
    this.permissions.set('user', false);
    this.permissions.set('guest', false);
  }
  
  private hasPermission(): boolean {
    return this.permissions.get(this.currentUser) ?? false;
  }
  
  query(sql: string): void {
    if (this.hasPermission()) {
      if (!this.realDatabase) {
        this.realDatabase = new RealDatabase();
      }
      this.realDatabase.query(sql);
    } else {
      console.log(`Access denied: User '${this.currentUser}' does not have permission to execute queries`);
    }
  }
  
  setUser(user: string): void {
    this.currentUser = user;
  }
}

// Example 3: Caching Proxy
// Shows how Proxy can cache expensive operations

interface Video {
  play(): void;
}

class RealVideo implements Video {
  private filename: string;
  
  constructor(filename: string) {
    this.filename = filename;
    this.loadVideo();
  }
  
  private loadVideo(): void {
    console.log(`Loading video ${this.filename} from server...`);
  }
  
  play(): void {
    console.log(`Playing video: ${this.filename}`);
  }
}

class VideoProxy implements Video {
  private filename: string;
  private realVideo?: RealVideo;
  private isLoaded: boolean = false;
  
  constructor(filename: string) {
    this.filename = filename;
  }
  
  play(): void {
    if (!this.isLoaded) {
      console.log('Loading video on first play...');
      this.realVideo = new RealVideo(this.filename);
      this.isLoaded = true;
    } else {
      console.log('Using cached video...');
    }
    this.realVideo!.play();
  }
}

// Example 4: Logging Proxy
// Shows how Proxy can add logging functionality

interface Service {
  doWork(): void;
}

class RealService implements Service {
  doWork(): void {
    console.log('Service: Performing work...');
  }
}

class LoggingProxy implements Service {
  private realService: RealService;
  
  constructor() {
    this.realService = new RealService();
  }
  
  private log(message: string): void {
    console.log(`[LOG] ${message}`);
  }
  
  doWork(): void {
    this.log('Before doWork');
    this.realService.doWork();
    this.log('After doWork');
  }
}

// Example 5: Remote Proxy (simulated)
// Shows how Proxy can represent remote objects

interface RemoteServer {
  request(data: string): void;
}

class RealRemoteServer implements RemoteServer {
  request(data: string): void {
    console.log(`Remote server processing request: ${data}`);
  }
}

class RemoteServerProxy implements RemoteServer {
  private remoteServer?: RealRemoteServer;
  private serverAddress: string;
  
  constructor(address: string) {
    this.serverAddress = address;
  }
  
  private connectToServer(): void {
    console.log(`Connecting to remote server at ${this.serverAddress}...`);
  }
  
  request(data: string): void {
    if (!this.remoteServer) {
      this.connectToServer();
      this.remoteServer = new RealRemoteServer();
    }
    console.log('Proxy forwarding request to remote server...');
    this.remoteServer.request(data);
  }
}

// Demo code
function demoProxy(): void {
  console.log('=== Proxy Pattern Demo ===\n');
  
  // Example 1: Virtual Proxy (Lazy Loading)
  console.log('--- Virtual Proxy (Lazy Loading) Example ---');
  
  const image1: Image = new ProxyImage('photo1.jpg');
  const image2: Image = new ProxyImage('photo2.jpg');
  const image3: Image = new ProxyImage('photo1.jpg');  // Same as image1
  
  console.log('\nFirst display of image1:');
  image1.display();
  
  console.log('\nSecond display of image1 (should use cached):');
  image1.display();
  
  console.log('\nDisplay of image2:');
  image2.display();
  
  console.log('\nDisplay of image3 (same as image1, should use cached):');
  image3.display();
  
  console.log();
  
  // Example 2: Protection Proxy
  console.log('--- Protection Proxy Example ---');
  
  const db = new DatabaseProxy('guest');
  console.log('\nGuest trying to execute query:');
  db.query('SELECT * FROM users');
  
  console.log('\nSwitching to admin user:');
  db.setUser('admin');
  db.query('SELECT * FROM users');
  
  console.log('\nSwitching back to regular user:');
  db.setUser('user');
  db.query('SELECT * FROM users');
  
  console.log();
  
  // Example 3: Caching Proxy
  console.log('--- Caching Proxy Example ---');
  
  const video = new VideoProxy('movie.mp4');
  
  console.log('\nFirst play (will load):');
  video.play();
  
  console.log('\nSecond play (will use cache):');
  video.play();
  
  console.log('\nThird play (will use cache):');
  video.play();
  
  console.log();
  
  // Example 4: Logging Proxy
  console.log('--- Logging Proxy Example ---');
  
  const loggingService = new LoggingProxy();
  loggingService.doWork();
  
  console.log();
  
  // Example 5: Remote Proxy
  console.log('--- Remote Proxy Example ---');
  
  const remoteProxy = new RemoteServerProxy('192.168.1.100');
  
  console.log('\nFirst request (will connect):');
  remoteProxy.request('GET /api/data');
  
  console.log('\nSecond request (already connected):');
  remoteProxy.request('POST /api/data');
}

// Run the demo
demoProxy();
