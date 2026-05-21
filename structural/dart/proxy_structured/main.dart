import 'virtual_proxy.dart';
import 'protection_proxy.dart';
import 'caching_proxy.dart';
import 'logging_proxy.dart';
import 'remote_proxy.dart';

void main() {
  print('=== Proxy Pattern Demo ===\n');
  
  // Example 1: Virtual Proxy (Lazy Loading)
  print('--- Virtual Proxy (Lazy Loading) Example ---');
  
  var image1 = ProxyImage('photo1.jpg');
  var image2 = ProxyImage('photo2.jpg');
  var image3 = ProxyImage('photo1.jpg');
  
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
