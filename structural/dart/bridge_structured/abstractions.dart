import 'interfaces.dart';

abstract class Shape {
  final DrawingAPI drawingAPI;
  
  Shape(this.drawingAPI);
  
  void draw();
  void resize(double percentage);
}

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

class AdvancedRemoteControl extends RemoteControl {
  AdvancedRemoteControl(Device device) : super(device);
  
  void mute() {
    print('Muting device');
    _device.setVolume(0);
  }
}
