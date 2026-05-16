/*
 * BRIDGE DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Bridge pattern separates abstraction from implementation so that both can vary independently.
 * It uses composition instead of inheritance to decouple the abstraction from its implementation.
 * 
 * WHY DOES IT EXIST?
 * - When you want to avoid a permanent binding between an abstraction and its implementation
 * - When both the abstraction and the implementation should be extensible by subclassing
 * - When changes in the implementation should not affect clients
 * - When you have a class hierarchy that explodes due to combining multiple dimensions
 * 
 * WHEN TO USE IT?
 * - When you want to split a monolithic class that has several variants of some functionality
 * - When you need to extend a class in several independent dimensions
 * - When you want to be able to switch implementations at runtime
 * - Common use cases: UI frameworks (different controls on different platforms), shape rendering, device drivers
 * 
 * PROS:
 * - Separates abstraction from implementation
 * - Improves extensibility (can extend abstractions and implementations independently)
 * - Hides implementation details from clients
 * - Reduces the number of subclasses needed (avoids combinatorial explosion)
 * 
 * CONS:
 * - Increases code complexity
 * - May require additional indirection
 * - Can make the code harder to understand initially
 * - Might be overkill for simple scenarios
 * 
 * REAL-WORLD ANALOGY:
 * Think of a TV remote control (abstraction) and the TV itself (implementation). The remote control doesn't need to know the internal workings of the TV. You can use the same remote with different TV brands, and different remotes with the same TV. The remote (abstraction) is bridged to the TV (implementation) through a standard interface (infrared signals).
 */

// Implementation Interface - defines the operations for all concrete implementations
abstract class DrawingAPI {
  void drawCircle(double x, double y, double radius);
  void drawRectangle(double x, double y, double width, double height);
}

// Concrete Implementation 1: Red Circle API
class RedCircleAPI implements DrawingAPI {
  @override
  void drawCircle(double x, double y, double radius) {
    print('Drawing Circle [color: red, center: ($x, $y), radius: $radius]');
  }
  
  @override
  void drawRectangle(double x, double y, double width, double height) {
    print('Drawing Rectangle [color: red, top-left: ($x, $y), width: $width, height: $height]');
  }
}

// Concrete Implementation 2: Green Circle API
class GreenCircleAPI implements DrawingAPI {
  @override
  void drawCircle(double x, double y, double radius) {
    print('Drawing Circle [color: green, center: ($x, $y), radius: $radius]');
  }
  
  @override
  void drawRectangle(double x, double y, double width, double height) {
    print('Drawing Rectangle [color: green, top-left: ($x, $y), width: $width, height: $height]');
  }
}

// Abstraction - defines the abstraction's interface and maintains a reference to an implementation
abstract class Shape {
  final DrawingAPI drawingAPI;
  
  Shape(this.drawingAPI);
  
  void draw();
  void resize(double percentage);
}

// Refined Abstraction 1: Circle
class Circle extends Shape {
  double _x, _y, _radius;
  
  Circle(this._x, this._y, this._radius, DrawingAPI api) : super(api);
  
  @override
  void draw() {
    drawingAPI.drawCircle(_x, _y, _radius);
  }
  
  @override
  void resize(double percentage) {
    _radius *= percentage / 100;
    print('Resizing circle to $_radius radius');
  }
}

// Refined Abstraction 2: Rectangle
class Rectangle extends Shape {
  double _x, _y, _width, _height;
  
  Rectangle(this._x, this._y, this._width, this._height, DrawingAPI api) : super(api);
  
  @override
  void draw() {
    drawingAPI.drawRectangle(_x, _y, _width, _height);
  }
  
  @override
  void resize(double percentage) {
    _width *= percentage / 100;
    _height *= percentage / 100;
    print('Resizing rectangle to ${_width}x$_height');
  }
}

// Example 2: Device and Remote Control Bridge
// This shows how the Bridge pattern can be used for device control

// Implementation Interface
abstract class Device {
  void turnOn();
  void turnOff();
  void setVolume(int volume);
  int getVolume();
}

// Concrete Implementation 1: TV
class Television implements Device {
  bool _on = false;
  int _volume = 10;
  
  @override
  void turnOn() {
    _on = true;
    print('TV is now ON');
  }
  
  @override
  void turnOff() {
    _on = false;
    print('TV is now OFF');
  }
  
  @override
  void setVolume(int volume) {
    if (_on) {
      _volume = volume;
      print('TV volume set to $volume');
    } else {
      print('Cannot set volume: TV is OFF');
    }
  }
  
  @override
  int getVolume() {
    return _volume;
  }
}

// Concrete Implementation 2: Radio
class Radio implements Device {
  bool _on = false;
  int _volume = 5;
  
  @override
  void turnOn() {
    _on = true;
    print('Radio is now ON');
  }
  
  @override
  void turnOff() {
    _on = false;
    print('Radio is now OFF');
  }
  
  @override
  void setVolume(int volume) {
    if (_on) {
      _volume = volume;
      print('Radio volume set to $volume');
    } else {
      print('Cannot set volume: Radio is OFF');
    }
  }
  
  @override
  int getVolume() {
    return _volume;
  }
}

// Abstraction: Remote Control
class RemoteControl {
  final Device _device;
  
  RemoteControl(this._device);
  
  void togglePower() {
    if (_device.getVolume() >= 0) {
      _device.turnOff();
    } else {
      _device.turnOn();
    }
  }
  
  void volumeUp() {
    int currentVolume = _device.getVolume();
    _device.setVolume(currentVolume + 1);
  }
  
  void volumeDown() {
    int currentVolume = _device.getVolume();
    _device.setVolume(currentVolume - 1);
  }
}

// Refined Abstraction: Advanced Remote Control
class AdvancedRemoteControl extends RemoteControl {
  AdvancedRemoteControl(Device device) : super(device);
  
  void mute() {
    print('Muting device');
    _device.setVolume(0);
  }
}

// Demo code
void main() {
  print('=== Bridge Pattern Demo ===\n');
  
  // Example 1: Shape Drawing Bridge
  print('--- Shape Drawing Bridge ---');
  
  var redCircle = Circle(100, 100, 10, RedCircleAPI());
  var greenCircle = Circle(100, 100, 10, GreenCircleAPI());
  
  redCircle.draw();
  greenCircle.draw();
  
  var redRectangle = Rectangle(50, 50, 20, 30, RedCircleAPI());
  var greenRectangle = Rectangle(50, 50, 20, 30, GreenCircleAPI());
  
  redRectangle.draw();
  greenRectangle.draw();
  
  print('\nResizing shapes:');
  redCircle.resize(150);
  redCircle.draw();
  
  print('');
  
  // Example 2: Device and Remote Control Bridge
  print('--- Device and Remote Control Bridge ---');
  
  var tv = Television();
  var tvRemote = RemoteControl(tv);
  
  print('\nControlling TV with basic remote:');
  tvRemote.togglePower();
  tvRemote.volumeUp();
  tvRemote.volumeUp();
  tvRemote.volumeDown();
  tvRemote.togglePower();
  
  var radio = Radio();
  var advancedRemote = AdvancedRemoteControl(radio);
  
  print('\nControlling Radio with advanced remote:');
  advancedRemote.togglePower();
  advancedRemote.volumeUp();
  advancedRemote.mute();
  advancedRemote.togglePower();
}
