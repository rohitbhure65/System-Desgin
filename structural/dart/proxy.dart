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
abstract class Image {
  void display();
}

// RealSubject - the actual object that the proxy represents
class RealImage extends Image {
  final String filename;
  
  RealImage(this.filename) {
    _loadFromDisk();
  }
  
  // Helper method to load the image from disk
  void _loadFromDisk() {
    print('Loading $filename from disk...');
  }
  
  @override
  void display() {
    print('Displaying $filename');
  }
}

// Proxy - controls access to the RealSubject
class ProxyImage extends Image {
  final String filename;
  RealImage? _realImage;
  
  ProxyImage(this.filename);
  
  @override
  void display() {
    // Lazy initialization: only create the real image when needed
    if (_realImage == null) {
      print('Creating real image on first access...');
      _realImage = RealImage(filename);
    }
    _realImage!.display();
  }
}

// Example 2: Protection Proxy
// Shows how Proxy can control access based on permissions

abstract class Database {
  void query(String sql);
}

class RealDatabase extends Database {
  @override
  void query(String sql) {
    print('Executing query: $sql');
  }
}

class DatabaseProxy extends Database {
  RealDatabase? _realDatabase;
  String _currentUser;
  final Map<String, bool> _permissions = {};
  
  DatabaseProxy(this._currentUser) {
    // Set up permissions (in real app, this would come from auth system)
    _permissions['admin'] = true;
    _permissions['user'] = false;
    _permissions['guest'] = false;
  }
  
  bool _hasPermission() {
    return _permissions[_currentUser] ?? false;
  }
  
  @override
  void query(String sql) {
    if (_hasPermission()) {
      _realDatabase ??= RealDatabase();
      _realDatabase!.query(sql);
    } else {
      print('Access denied: User \'$_currentUser\' does not have permission to execute queries');
    }
  }
  
  void setUser(String user) {
    _currentUser = user;
  }
}

// Example 3: Caching Proxy
// Shows how Proxy can cache expensive operations

abstract class Video {
  void play();
}

class RealVideo extends Video {
  final String filename;
  
  RealVideo(this.filename) {
    _loadVideo();
  }
  
  void _loadVideo() {
    print('Loading video $filename from server...');
  }
  
  @override
  void play() {
    print('Playing video: $filename');
  }
}

class VideoProxy extends Video {
  final String filename;
  RealVideo? _realVideo;
  bool _isLoaded = false;
  
  VideoProxy(this.filename);
  
  @override
  void play() {
    if (!_isLoaded) {
      print('Loading video on first play...');
      _realVideo = RealVideo(filename);
      _isLoaded = true;
    } else {
      print('Using cached video...');
    }
    _realVideo!.play();
  }
}

// Example 4: Logging Proxy
// Shows how Proxy can add logging functionality

abstract class Service {
  void doWork();
}

class RealService extends Service {
  @override
  void doWork() {
    print('Service: Performing work...');
  }
}

class LoggingProxy extends Service {
  final RealService _realService = RealService();
  
  void _log(String message) {
    print('[LOG] $message');
  }
  
  @override
  void doWork() {
    _log('Before doWork');
    _realService.doWork();
    _log('After doWork');
  }
}

// Example 5: Remote Proxy (simulated)
// Shows how Proxy can represent remote objects

abstract class RemoteServer {
  void request(String data);
}

class RealRemoteServer extends RemoteServer {
  @override
  void request(String data) {
    print('Remote server processing request: $data');
  }
}

class RemoteServerProxy extends RemoteServer {
  RealRemoteServer? _remoteServer;
  final String serverAddress;
  
  RemoteServerProxy(this.serverAddress);
  
  void _connectToServer() {
    print('Connecting to remote server at $serverAddress...');
  }
  
  @override
  void request(String data) {
    if (_remoteServer == null) {
      _connectToServer();
      _remoteServer = RealRemoteServer();
    }
    print('Proxy forwarding request to remote server...');
    _remoteServer!.request(data);
  }
}

// Demo code
void main() {
  print('=== Proxy Pattern Demo ===\n');
  
  // Example 1: Virtual Proxy (Lazy Loading)
  print('--- Virtual Proxy (Lazy Loading) Example ---');
  
  var image1 = ProxyImage('photo1.jpg');
  var image2 = ProxyImage('photo2.jpg');
  var image3 = ProxyImage('photo1.jpg');  // Same as image1
  
  print('\nFirst display of image1:');
  image1.display();
  
  print('\nSecond display of image1 (should use cached):');
  image1.display();
  
  print('\nDisplay of image2:');
  image2.display();
  
  print('\nDisplay of image3 (same as image1, should use cached):');
  image3.display();
  
  print('');
  
  // Example 2: Protection Proxy
  print('--- Protection Proxy Example ---');
  
  var db = DatabaseProxy('guest');
  print('\nGuest trying to execute query:');
  db.query('SELECT * FROM users');
  
  print('\nSwitching to admin user:');
  db.setUser('admin');
  db.query('SELECT * FROM users');
  
  print('\nSwitching back to regular user:');
  db.setUser('user');
  db.query('SELECT * FROM users');
  
  print('');
  
  // Example 3: Caching Proxy
  print('--- Caching Proxy Example ---');
  
  var video = VideoProxy('movie.mp4');
  
  print('\nFirst play (will load):');
  video.play();
  
  print('\nSecond play (will use cache):');
  video.play();
  
  print('\nThird play (will use cache):');
  video.play();
  
  print('');
  
  // Example 4: Logging Proxy
  print('--- Logging Proxy Example ---');
  
  var loggingService = LoggingProxy();
  loggingService.doWork();
  
  print('');
  
  // Example 5: Remote Proxy
  print('--- Remote Proxy Example ---');
  
  var remoteProxy = RemoteServerProxy('192.168.1.100');
  
  print('\nFirst request (will connect):');
  remoteProxy.request('GET /api/data');
  
  print('\nSecond request (already connected):');
  remoteProxy.request('POST /api/data');
}
