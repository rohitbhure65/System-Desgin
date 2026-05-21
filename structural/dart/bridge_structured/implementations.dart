import 'interfaces.dart';

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
