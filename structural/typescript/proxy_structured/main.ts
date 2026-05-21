import { Image, ProxyImage } from './virtual_proxy';
import { DatabaseProxy } from './protection_proxy';
import { VideoProxy } from './caching_proxy';
import { LoggingProxy } from './logging_proxy';
import { RemoteServerProxy } from './remote_proxy';

function demoProxy(): void {
  console.log('=== Proxy Pattern Demo ===\n');
  
  // Example 1: Virtual Proxy (Lazy Loading)
  console.log('--- Virtual Proxy (Lazy Loading) Example ---');
  
  const image1: Image = new ProxyImage('photo1.jpg');
  const image2: Image = new ProxyImage('photo2.jpg');
  const image3: Image = new ProxyImage('photo1.jpg');
  
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
