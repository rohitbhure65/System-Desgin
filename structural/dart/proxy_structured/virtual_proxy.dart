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
    if (_realImage == null) {
      print('Creating real image on first access...');
      _realImage = RealImage(filename);
    }
    _realImage!.display();
  }
}
